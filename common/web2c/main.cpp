#include <bibtex/bibtex.h>
#include <cbiber.h>
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <filesystem>
#include <iostream>
#include <libgen.h>
#include <makeindexk/makeindex.h>
#include <md5/md5.h>
#include <string>
#include <synctex_parser.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/un.h>
#include <time.h>
#include <tree/tree.h>
#include <unistd.h>

extern const char* bootstrapcmd;
extern "C" int	   _compile();

std::string	   main_entry_file;
extern "C" int compileLaTeX() {
	if (main_entry_file.empty()) { return -1; }
	std::filesystem::path current_path = std::filesystem::current_path();
	std::filesystem::path entry_path(main_entry_file);
	std::filesystem::path dir		 = entry_path.parent_path();
	std::filesystem::path entry_file = entry_path.filename();
	if (dir.empty() == false) std::filesystem::current_path(dir);
	std::string entry_file_str = entry_file;
	if (entry_file_str.find(' ') != std::string::npos) {
		entry_file_str = '\"' + entry_file_str + '\"';
	}
	bootstrapcmd = strdup(entry_file_str.c_str());
	int ret		 = _compile();
	if (dir.empty() == false) std::filesystem::current_path(current_path);
	return ret;
}

extern "C" int compileFormat() {
#ifdef XETEXWASM
	bootstrapcmd = "*xelatex.ini";
#else
	bootstrapcmd = "*pdflatex.ini";
#endif
	return _compile();
}

extern "C" int compileBibLatex() {
	// 检查文件扩展名长度
	if (main_entry_file.length() < 4) { return -1; }
	const std::string main_entry_without_ext =
		main_entry_file.substr(0, main_entry_file.length() - 4);
	const std::string main_aux_file = main_entry_without_ext + ".aux";
	const std::string main_bcf_file = main_entry_without_ext + ".bcf";
	const std::string main_bbl_file = main_entry_without_ext + ".bbl";

	// 检查.bbl文件是否存在且非空
	std::error_code ec;
	auto			file_status = std::filesystem::status(main_bbl_file, ec);
	if (!ec && std::filesystem::exists(file_status) &&
		std::filesystem::file_size(main_bbl_file) != 0) {
		return 0;
	}

	int biblatex_res = 0;

	// 根据存在文件决定使用biber还是bibtex
	if (std::filesystem::exists(main_bcf_file)) {
		// 如果.bcf文件存在，运行biber作为biblatex
		biblatex_res = biber_main(main_bcf_file.c_str());
	}
	else {
		// 如果.bcf文件不存在，运行bibtex作为biblatex
		biblatex_res = bibtex_main(main_aux_file.c_str());
	}

	makeindex_main(main_aux_file.c_str());
	// tree_dir("/", stderr);

	return biblatex_res;
}

extern "C" int setMainEntry(const char* p) {
	main_entry_file = p;
	return 0;
}
extern "C" char*
synctex_view(const char* pdf_path, const char* tex_path, int line, int column) {
	if (tex_path == NULL) return NULL;

	// 使用std::string重写路径处理逻辑
	std::string synctex_tex_path;
	std::string input_path(tex_path);

	if (input_path[0] == '.') { synctex_tex_path = "/work" + input_path; }
	else if (input_path[0] == '/') {
		if (input_path.substr(0, 6) == "/work/" &&
			input_path.substr(0, 8) != "/work/./") {
			synctex_tex_path = "/work/./" + input_path.substr(6);
		}
		else { synctex_tex_path = input_path; }
	}
	else { synctex_tex_path = "/work/./" + input_path; }

	synctex_scanner_p scanner = synctex_scanner_new_with_output_file(pdf_path, NULL, 1);
	if (!scanner) return NULL;

	int status =
		synctex_display_query(scanner, synctex_tex_path.c_str(), line, column, 0);
	if (status <= 0) {
		synctex_scanner_free(scanner);
		return NULL;
	}

	synctex_node_p node;
	if ((node = synctex_scanner_next_result(scanner)) == NULL) return NULL;

	char  buffer[512];
	int	  page = synctex_node_page(node);
	float x	   = synctex_node_visible_h(node);
	float y	   = synctex_node_visible_v(node);
	float h	   = synctex_node_box_visible_h(node);
	float v	   = synctex_node_box_visible_v(node) + synctex_node_box_visible_depth(node);
	float W	   = synctex_node_box_visible_width(node);
	float H =
		synctex_node_box_visible_height(node) + synctex_node_box_visible_depth(node);
	snprintf(
		buffer, sizeof(buffer), "%d\x1F%.2f\x1F%.2f\x1F%.2f\x1F%.2f\x1F%.2f\x1F%.2f",
		page, x, y, h, v, W, H);
	synctex_scanner_free(scanner);
	return strdup(buffer);
}

extern "C" char* synctex_edit(const char* pdf_path, int page, float x, float y) {
	synctex_scanner_p scanner = synctex_scanner_new_with_output_file(pdf_path, NULL, 1);
	if (!scanner) return NULL;

	int status = synctex_edit_query(scanner, page, x, y);
	if (status <= 0) {
		synctex_scanner_free(scanner);
		return NULL;
	}

	synctex_node_p node;
	if ((node = synctex_scanner_next_result(scanner)) == NULL) return NULL;

	// now we only use the first one
	char		buffer[256];
	const char* name = synctex_scanner_get_name(scanner, synctex_node_tag(node));
	int			line = synctex_node_line(node);
	int			col	 = synctex_node_column(node);
	snprintf(buffer, sizeof(buffer), "%s\x1F%d\x1F%d", name, line, col);
	synctex_scanner_free(scanner);
	return strdup(buffer);
}

int main(int argc, char** argv) {
	printf("SwiftLaTeX Engine Loaded\n");
}
