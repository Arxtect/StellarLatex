#include "control_utils.hpp"
#include <bibtex/bibtex.h>
#include <cbiber.h>
#include <chrono>
#include <fstream>
#include <iostream>
#include <makeindexk/makeindex.h>
#include <setjmp.h>
#include <tree/tree.h>

namespace fs = std::filesystem;
cppstr main_entry_file;
cppstr main_entry_dir;
size_t compile_times		  = 666;
size_t at_least_compile_times = 0;
size_t at_most_compile_times  = 0;
bool   bbl_required			  = false;
// this variable is as /output/<entry_file_base>
cppstr			   entry_file_base;
extern "C" int	   prepareExecutionContext_js();
extern const char* bootstrapcmd;
extern "C" int	   _compile();
// for xetex, convert xdv to pdf at final
#ifdef XETEXWASM
extern jmp_buf jmpenv;
extern "C" int convertXDVPDF(const char* xdv, const char* pdf);
#endif
// func
int compileBibLatexRoutine() {
	auto hasBibData = [](const std::string& auxFilePath) -> bool {
		std::ifstream auxStream(auxFilePath.c_str());
		if (auxStream.is_open()) {
			std::string line;
			while (std::getline(auxStream, line)) {
				if (line.find("\\bibdata{") != std::string::npos) {
					auxStream.close();
					return true;
				}
			}
			auxStream.close();
		}
		return false;
	};

	// 检查文件扩展名长度
	cppstr output_main = main_entry_file;
	if (main_entry_file.find('/') != std::string::npos) {
		output_main = main_entry_file.substr(main_entry_file.find_last_of('/') + 1);
	}
	if (main_entry_file.length() < 4) { return -1; }
	output_main = "/output/" + output_main.substr(0, output_main.length() - 4);
	const cppstr main_aux_file = output_main + ".aux";
	const cppstr main_bcf_file = output_main + ".bcf";
	const cppstr main_bbl_file = output_main + ".bbl";

	// 检查.bbl文件是否存在且非空
	// std::error_code ec;
	// auto			file_status = fs::status(main_bbl_file, ec);
	// if (!ec && fs::exists(file_status) && fs::file_size(main_bbl_file) != 0) { return
	// 0; }

	int biblatex_res = 0;

	if (hasBibData(main_aux_file)) {
		// 如果aux文件中有\bibdata行，运行bibtex作为biblatex
		biblatex_res = bibtex_main(main_aux_file.c_str());
		// 增加代码：输出 main_bbl_file 的内容到 std::cerr
		std::ifstream bbl_stream(main_bbl_file.c_str());
		if (bbl_stream.is_open()) {
			std::string content(
				(std::istreambuf_iterator<char>(bbl_stream)),
				std::istreambuf_iterator<char>());
			bbl_stream.close();
			bool isEmpty = content.empty();
			bool isDefaultBib =
				(content.find("\\begin{thebibliography}{}") != std::string::npos &&
				 content.find("\\end{thebibliography}") != std::string::npos &&
				 content.find("\\bibitem") == std::string::npos);
			if (isEmpty || isDefaultBib) {
				// 删除文件
				fs::remove(main_bbl_file);
				std::cerr << "[WASM ENGINE] Removed empty or default \"" << main_bbl_file
						  << "\" file." << std::endl;
			}
		}
		else {
			std::cerr << "[WASM ENGINE] Warning: Cannot open \"" << main_bbl_file
					  << "\" for reading." << std::endl;
		}
	}
	return biblatex_res;
}
int compileLaTeXRoutine() {
	std::cout << "[WASM ENGINE] compileLaTeXRoutine \"" << main_entry_file
			  << "\" for times: " << compile_times << std::endl;
	if (main_entry_file.empty()) { return -1; }
	fs::path current_path = fs::current_path();
	fs::path entry_path(main_entry_file);
	fs::path dir		= entry_path.parent_path();
	fs::path entry_file = entry_path.filename();
	if (dir.empty() == false) {
		fs::current_path(dir);
		main_entry_dir = dir.string();
	}
	else { main_entry_dir = "/work"; }
	const cppstr entry_file_str = entry_file;
	if (entry_file_str.size() <= 4) {
		std::cerr << "Error: Invalid entry file name: \"" << entry_file_str << "\""
				  << std::endl;
	}
	const cppstr entry_file_base = entry_file_str.substr(0, entry_file_str.length() - 4);
	// delete old pdf and xdv
	const cppstr pdf = "/output/" + entry_file_base + ".pdf";
	if (fs::exists(pdf)) { fs::remove(pdf); }
#ifdef XETEXWASM
	const cppstr xdv = "/output/" + entry_file_base + ".xdv";
	if (fs::exists(xdv)) { fs::remove(xdv); }
#endif
	bootstrapcmd = strdup(entry_file_str.c_str());
	int ret = _compile();
	if (dir.empty() == false) fs::current_path(current_path);
#ifdef XETEXWASM
	if (ret == 0 && fs::exists(xdv) == false)
#else
	if (ret == 0 && fs::exists(pdf) == false)
#endif
	{
		// this should not happen
		std::cerr << "Error: Failed to compile \"" << pdf << "\", but return 0"
				  << std::endl;
		return 1;
	}
	std::cout << "[WASM ENGINE] compileLaTeXRoutine \"" << main_entry_file
			  << "\" for times: " << compile_times << " finished with status " << ret
			  << std::endl;
	return ret;
}

int compileFormatRoutine() {
#ifdef XETEXWASM
	bootstrapcmd = "*xelatex.ini";
#else
	bootstrapcmd = "*pdflatex.ini";
#endif
	return _compile();
}
int makeindexRoutine(const cppstr& aux_file) {
	if (aux_file.empty()) return 0;
	cppstr fileNoExt = aux_file.substr(0, aux_file.find_last_of("."));
	// if log file is seen, stop
	if (fs::exists(fileNoExt + ".log")) { fs::remove(fileNoExt + ".log"); }
	// makeindex main.aux
	if (fs::exists(aux_file)) {
		const char* _argv[] = {"makeindex", aux_file.c_str()};
		return makeindex_main(sizeof(_argv) / sizeof(_argv[0]), _argv);
	}
	// makeindex main.idx
	if (cppstr idx = fileNoExt + ".idx"; fs::exists(idx)) {
		const char* _argv[] = {"makeindex", idx.c_str()};
		return makeindex_main(sizeof(_argv) / sizeof(_argv[0]), _argv);
	}
	// makeindex main.glo
	if (cppstr glo = fileNoExt + ".glo"; fs::exists(glo)) {
		const char* _argv[] = {"makeindex", glo.c_str()};
		return makeindex_main(sizeof(_argv) / sizeof(_argv[0]), _argv);
	}
	// makeindex main.nlo
	if (cppstr nlo = fileNoExt + ".nlo"; fs::exists(nlo)) {
		cppstr		nls		= fileNoExt + ".nls";
		const char* _argv[] = {"makeindex",	  nlo.c_str(), "-s",
							   "nomencl.ist", "-o",		   nls.c_str()};
		return makeindex_main(sizeof(_argv) / sizeof(_argv[0]), _argv);
	}
	std::cerr << "[WASM ENGINE] Error: makeindex called with no valid file format."
			  << std::endl;
	return 1;
}

static void loadStatus() {
	if (fs::exists("/tmp/mainfile.txt")) {
		char c_main_entry_file[1024];
		std::ifstream("/tmp/mainfile.txt").getline(c_main_entry_file, 1024);
		main_entry_file = c_main_entry_file;
	}
	auto main_entry_dir_path = fs::path(main_entry_file).parent_path();
	if (main_entry_dir_path.empty()) { main_entry_dir = "/work"; }
	else { main_entry_dir = main_entry_dir_path.string(); }
	entry_file_base = fs::path(main_entry_file).filename();
	entry_file_base = entry_file_base.substr(0, entry_file_base.find_last_of("."));
	entry_file_base = "/output/" + entry_file_base;
	if (fs::exists("/tmp/compile_times")) {
		std::ifstream("/tmp/compile_times") >> compile_times;
		compile_times++;
	}
	else { compile_times = 1; }
	std::ofstream("/tmp/compile_times") << compile_times;
	if (fs::exists("/tmp/at_least_compile_times")) {
		std::ifstream("/tmp/at_least_compile_times") >> at_least_compile_times;
	}
	if (fs::exists("/tmp/at_most_compile_times")) {
		std::ifstream("/tmp/at_most_compile_times") >> at_most_compile_times;
	}
}

static uint32_t detectParagraphsInFile(const std::string& filename) {
	// 读取整个文件内容
	std::ifstream file(filename);
	if (!file.is_open()) { return 0; }

	std::string content(
		(std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();

	std::uint32_t result = 0;

	// 定义5种警告模式，使用\n连接需要连续出现的行
	static const std::vector<std::string> patterns = {
		{// 警告1：bibtex (2行必须连续)
		 "Package natbib Warning: Citation(s) may have changed.\n"
		 "(natbib)                Rerun to get citations correct."},
		{// 警告2：labels
		 "LaTeX Warning: Label(s) may have changed. Rerun to get cross-references "
		 "right."},
		{// 警告3：biber第一种 (2行必须连续)
		 "(rerunfilecheck)                Rerun to get outlines right\n"
		 "(rerunfilecheck)                or use package `bookmark'."},
		{// 警告4：biber第二种
		 "Package biblatex Warning: Please (re)run Biber on the file:"},
		{// 警告5：biber第三种
		 "Package biblatex Warning: Please rerun LaTeX."},
	};

	// 检查每种警告模式
	for (size_t i = 0; i < patterns.size(); ++i) {
		if (!patterns[i].empty() && content.find(patterns[i]) != cppstr::npos) {
			result |= (1 << i);
			cppstr pattern = patterns[i];
			cppstr prefix  = "[WASM ENGINE] found warning " + std::to_string(i) + ": ";

			size_t pos		  = 0;
			size_t line_start = 0;
			while ((pos = pattern.find('\n', line_start)) != cppstr::npos) {
				cppstr line = pattern.substr(line_start, pos - line_start);
				if (!line.empty()) {
					std::cerr << prefix << "\"" << line << "\"" << std::endl;
				}
				line_start = pos + 1;
			}
			// 处理最后一行（或唯一一行）
			cppstr last_line = pattern.substr(line_start);
			if (!last_line.empty()) {
				std::cerr << prefix << "\"" << last_line << "\"" << std::endl;
			}
		}
	}
	// DEBUG
	if (result != 0)
		std::cerr << "[WASM ENGINE] found warning number: 0x" << std::hex << result
				  << std::dec << std::endl;
	else
		std::cerr << "[WASM ENGINE] no conrtoller's warning found." << std::endl;
	return result;
}
void setCompileTimes(int least, int most) {
	at_least_compile_times = least;
	at_most_compile_times  = most;
	std::ofstream("/tmp/at_least_compile_times") << least;
	std::ofstream("/tmp/at_most_compile_times") << most;
	return;
}
static int makeRoutine(bool force_bibtex, int least, int most) {
	std::cerr << "[WASM ENGINE] makeRoutine(force_bibtex="
			  << (force_bibtex ? "true" : "false") << ", least=" << least
			  << ", most=" << most << ") called." << std::endl;
	if (most == 0) return 0;
	setCompileTimes(least, most);
	int			   res			   = 0;
	bool		   finished		   = false;
	const cppstr   main_idx_name   = entry_file_base + ".idx";
	const uint32_t idx_hash_before = simpleHash(entry_file_base + ".idx");
	res							   = compileLaTeXRoutine();
	uint32_t	   compile_warn	   = detectParagraphsInFile(entry_file_base + ".log");
	const uint32_t idx_hash_after  = simpleHash(entry_file_base + ".idx");
	if (idx_hash_before != idx_hash_after) {
		std::cerr << "[WASM ENGINE] file \"" << entry_file_base << ".idx\" changed."
				  << std::endl;
		std::cerr << "[WASM ENGINE] makeindex(\"" << (entry_file_base + ".idx")
				  << "\") called." << std::endl;
		int res = makeindexRoutine((entry_file_base + ".idx").c_str());
		std::cerr << "[WASM ENGINE] makeindex(\"" << (entry_file_base + ".idx")
				  << "\") return " << res << std::endl;
		prepareExecutionContext_js();
		loadStatus();
		res			 = compileLaTeXRoutine();
		compile_warn = detectParagraphsInFile(entry_file_base + ".log");
	}
	if (force_bibtex || bbl_required || compile_warn & 0b00001000) {
		bbl_required = false;
		compileBibLatexRoutine();
	}
	if (force_bibtex == false && compile_warn == 0 &&
		compile_times >= at_least_compile_times) {
		std::cerr << "[WASM ENGINE] compile times: " << compile_times << ", return "
				  << res << std::endl;
	}
	else {
		while (compile_times < at_most_compile_times) {
			prepareExecutionContext_js();
			loadStatus();
			res			 = compileLaTeXRoutine();
			compile_warn = detectParagraphsInFile(entry_file_base + ".log");
			if (compile_warn & 0b00001000 || bbl_required) {
				bbl_required = false;
				if (std::filesystem::exists("/tmp/compiled_bib") == false) {
					compileBibLatexRoutine();
					std::ofstream("/tmp/compiled_bib");
					if (compile_times < at_most_compile_times) continue;
				}
			}
			if ((compile_warn & 0b11110111) == 0 &&
				compile_times >= at_least_compile_times) {
				std::cerr << "[WASM ENGINE] compile times: " << compile_times
						  << ", return " << res << std::endl;
				break;
			}
		}
	}
	if (std::filesystem::exists("/tmp/compiled_bib"))
		std::filesystem::remove("/tmp/compiled_bib");
#ifdef XETEXWASM
	const cppstr pdf = entry_file_base + ".pdf";
	const cppstr xdv = entry_file_base + ".xdv";
	if (fs::exists(xdv)) {
		if (setjmp(jmpenv) == 0) {
			std::cerr << "[WASM ENGINE] convertXDVPDF(\"" << xdv << "\", \"" << pdf
					  << "\") called." << std::endl;
			int _res = convertXDVPDF(xdv.c_str(), pdf.c_str());
			std::cerr << "[WASM ENGINE] convertXDVPDF(\"" << xdv << "\", \"" << pdf
					  << "\") return " << _res << "." << std::endl;
			if (_res != 0) {
				std::cerr << "! Error: XeTeX wasm: convertXDVPDF(\"" << xdv << "\", \""
						  << pdf << "\") returned " << _res << "." << std::endl;
				if (_res == 0) res = 68; /* 随便写的 */
			}
			longjmp(jmpenv, 10);
		}
	}
	else {
		std::cerr << "! Error: XeTeX wasm: file \"" << xdv << "\" do not exist"
				  << std::endl;
		if (res == 0) res = 68; /* 随便写的 */
	}
#endif
	std::cerr << "[WASM ENGINE] makeRoutine(force_bibtex="
			  << (force_bibtex ? "true" : "false") << ", least=" << least
			  << ", most=" << most << ") return " << res << "." << std::endl;
	return res;
}

static int AnalyzeRoutine(bool& force_bibtex, int& least, int& most) {
	HashDB db_old;
	HashDB db_new;
	db_old.loadDB();
	db_new.buildDB();
	db_new.saveDB();
	HashDB::hashDiffer differ = db_new - db_old;
	loadStatus();
#ifdef XETEXWASM
	if (main_entry_file == "*xelatex.ini") return compileFormatRoutine();
#elif defined(PDFTEXWASM)
	if (main_entry_file == "*pdflatex.ini") return compileFormatRoutine();
#else
#	error "Unknown compiler"
#endif
	// 检查tex是否变更
	vecstr tex_files	   = getAllTexFiles(main_entry_file);
	bool   containsDynamic = containsDynamicCommandsInProject(tex_files);
	if (containsDynamic == false) {
		cppstr main_aux_file = entry_file_base + ".aux";
		// 检查 main_aux_file 最后的修改日期是否和当前日期相同
		if (fs::exists(main_aux_file)) {
			std::error_code ec;
			auto			last_write_time = fs::last_write_time(main_aux_file, ec);
			if (!ec) {
				// 将文件时间转换为time_t
				auto sec = std::chrono::duration_cast<std::chrono::seconds>(
							   last_write_time.time_since_epoch())
							   .count();
				std::time_t last_write_tt = static_cast<std::time_t>(sec);
				// 获取当前时间
				std::time_t now_tt = std::time(nullptr);
				// 转换为本地时间结构
				std::tm* last_write_tm = std::localtime(&last_write_tt);
				std::tm* now_tm		   = std::localtime(&now_tt);
				// 比较是否同一天（年月日相同）
				if (last_write_tm->tm_year != now_tm->tm_year ||
					last_write_tm->tm_mon != now_tm->tm_mon ||
					last_write_tm->tm_mday != now_tm->tm_mday) {
					containsDynamic = containsDateCommandsInProject(tex_files);
				}
			}
		}
	}
	if (fs::exists(entry_file_base + ".aux")) {
		// 存在 aux
		bool tex_changed = false;
		bool bib_changed = false;
		if (differ.is_any_changed() == false) {
			int same_times = 0;
			if (fs::exists("/tmp/same_times")) {
				std::ifstream("/tmp/same_times") >> same_times;
			}
			same_times++;
			std::ofstream("/tmp/same_times") << same_times;
			std::cerr << "[WASM ENGINE] Warning: Same as the last time for " << same_times
					  << " times" << std::endl;
			if (same_times >= 3) {
				// 删除 /output 和 /tmp 下的所有文件
				fs::rename("/tmp/mainfile.txt", "/home/web_user/mainfile.txt");
				fs::remove_all("/output");
				fs::remove_all("/tmp");
				fs::create_directory("/output");
				fs::create_directory("/tmp");
				fs::rename("/home/web_user/mainfile.txt", "/tmp/mainfile.txt");
				std::ofstream("/tmp/compile_times") << 1;
				force_bibtex = true;
				least		 = 3;
				most		 = 5;
				return 0;
			}
			if (containsDynamic == false) {
				// 规则0，退出
				force_bibtex = false;
				least		 = 0;
				most		 = 0;
				std::ofstream("/tmp/no_compile");
				return 0;
			}
		}
		else {
			if (fs::exists("/tmp/same_times")) fs::remove("/tmp/same_times");
		}
		if (containsDynamic) {
			// tex发生变更
			tex_changed = true;
		}
		if (differ.is_bib_changed()) {
			// bib 发生变更
			bib_changed = true;
		}
		std::cerr << "[WASM ENGINE] tex_changed=" << (tex_changed ? "true" : "false")
				  << ", bib_changed=" << (bib_changed ? "true" : "false") << std::endl;
		// 规则2：若main_file.aux存在，.tex和.bib都不变更，存在其他文件变更，则compile->根据log运行compile
		if (tex_changed == false && bib_changed == false) {
			force_bibtex = false;
			least		 = 1;
			most		 = 3;
		}
		else if (tex_changed == false && bib_changed == true) {
			compileBibLatexRoutine();
			force_bibtex = false;
			least		 = 1;
			most		 = 3;
		}
		else if (tex_changed == true && bib_changed == false) {
			force_bibtex = false;
			least		 = 1;
			most		 = 3;
		}
		else if (tex_changed == true && bib_changed == true) {
			force_bibtex = true;
			least		 = 2;
			most		 = 5;
		}
	}
	else {
		// 删除 /output 和 /tmp 下的所有文件
		fs::rename("/tmp/mainfile.txt", "/home/web_user/mainfile.txt");
		fs::remove_all("/output");
		fs::remove_all("/tmp");
		fs::create_directory("/output");
		fs::create_directory("/tmp");
		fs::rename("/home/web_user/mainfile.txt", "/tmp/mainfile.txt");
		std::ofstream("/tmp/compile_times") << 1;
		db_new.saveDB();
		force_bibtex = false;
		least		 = 2;
		most		 = 5;
	}
	return 0;
}

extern "C" int compileLaTeX() {
	bool force_bibtex = false;
	int	 least		  = 0;
	int	 most		  = 0;
	AnalyzeRoutine(force_bibtex, least, most);
	int ret = makeRoutine(force_bibtex, least, most);
	if (fs::exists("/tmp/mainfile.txt")) fs::remove("/tmp/mainfile.txt");
	if (fs::exists("/tmp/compile_times")) fs::remove("/tmp/compile_times");
	if (fs::exists("/tmp/at_least_compile_times"))
		fs::remove("/tmp/at_least_compile_times");
	if (fs::exists("/tmp/at_most_compile_times"))
		fs::remove("/tmp/at_most_compile_times");
	// tree_dir("/", stderr);
	return ret;
}
