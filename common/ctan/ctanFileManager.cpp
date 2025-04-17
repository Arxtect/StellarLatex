#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string_view>
#include <vector>

#include "ctanFileManager.hpp"
#include "extractFile.hpp"
using std::map;
using std::ostream;
using std::pair;
using cppstr = std::string;
using std::string_view;
using std::vector;
using cstr = const char*;

CTANFileManager* globalManager = nullptr;

static bool end_up_with(const cppstr& str, cstr suffix) {
	const size_t str_length	   = str.size();
	const size_t suffix_length = strlen(suffix);
	return str_length >= suffix_length &&
		   str.compare(str_length - suffix_length, suffix_length, suffix) == 0;
}
static bool end_up_with(const cppstr& str, const cppstr& suffix) {
	if (str.size() < suffix.size()) return false;
	return str.substr(str.size() - suffix.size()) == suffix;
}

extern "C" char* ctan_get_file(cstr request_name, kpse_file_format_type type) {
	// THIS FUNCTION INVOLVES MANY HARDCODE
	if (globalManager == nullptr) {
		if (std::filesystem::exists("/tex/pkg/texlive.tlpdb") == false) {
			auto ret = ctan_download_pkg_js(
				"systems/texlive/tlnet/tlpkg/texlive.tlpdb", "texlive.tlpdb");
			if (ret != 0) {
				std::cerr << "Failed to download texlive.tlpdb!" << std::endl;
				return nullptr;
			}
		}
		std::ifstream file("/tex/pkg/texlive.tlpdb");
		if (!file.is_open()) {
			std::cerr << "Failed to open texlive.tlpdb!" << std::endl;
			return nullptr;
		}
		std::string fileContent(
			(std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		globalManager = new CTANFileManager(string_view(fileContent));
		file.close();
		fileContent.clear();
	}
	// remove '/tex/' header
	if (memcmp(request_name, "/tex/", 5) == 0) { request_name += 5; }
	// if request_name have '/', stop
	if (strchr(request_name, '/') != nullptr) {
		fprintf(stderr, "ctan_get_file: %d/%s failed\n", int(type), request_name);
		return nullptr;
	}
	char* ret = nullptr;
	// for frequently asked file, go to old server
	if (memcmp(request_name, "swiftlatex", 10) == 0 ||
		strcmp(request_name, "pdftex.map") == 0 ||
		strcmp(request_name, "kanjix.map") == 0 ||
		strcmp(request_name, "xetexfontlist.txt") == 0) {
		ret = kpse_find_file_js(request_name, type, false);
	}
	// if meet .fmt file, go to old server
	else if (end_up_with(request_name, ".fmt") == true) {
		ret = kpse_find_file_js(request_name, type, false);
	}
	else {
		ret = globalManager->get_file(request_name, type);
		if (ret == nullptr) {
			// send unmeet request to old server
			// ret = kpse_find_file_js(request_name, type, false);
		}
	}
	if (ret == nullptr) {
		fprintf(stderr, "ctan_get_file: %d/%s failed\n", int(type), request_name);
	}
	else {
		fprintf(stderr, "ctan_get_file: %d/%s into %s\n", int(type), request_name, ret);
	}
	return ret;
}

// TO BE FINISHED:
// optimise: AST Tree
// how .sty file is built
// optimize depend to number
// in addition of texlive tlcontrib

map<kpse_file_format_type, vector<cstr>> CTANFileManager::format_to_suffix = {
	{kpse_gf_format, {"gf"}},
	{kpse_pk_format, {"pk"}},
	{kpse_tfm_format, {".tfm"}},
	{kpse_afm_format, {".afm"}},
	{kpse_base_format, {".base"}},
	{kpse_bib_format, {".bib"}},
	{kpse_bst_format, {".bst"}},
	{kpse_cnf_format, {".cnf"}},
	{kpse_db_format, {"ls-R", "ls-r"}},
	{kpse_fmt_format, {".fmt"}},
	{kpse_fontmap_format, {".map", ".txt"}},
	{kpse_mem_format, {".mem"}},
	{kpse_mf_format, {".mf"}},
	{kpse_mft_format, {".mft"}},
	{kpse_mfpool_format, {".pool"}},
	{kpse_mp_format, {".mp"}},
	{kpse_mppool_format, {".pool"}},
	{kpse_ocp_format, {".ocp"}},
	{kpse_ofm_format, {".ofm"}},
	{kpse_opl_format, {".opl"}},
	{kpse_otp_format, {".otp"}},
	{kpse_ovf_format, {".ovf", ".vf"}},
	{kpse_ovp_format, {".ovp", ".vpl"}},
	{kpse_pict_format, {".eps", ".epsi"}},
	{kpse_tex_format,
	 {".tex", ".sty", ".cls", ".fd", ".aux", ".bbl", ".def", ".clo", ".ldf", ".mld",
	  ".mlo", ".cfg", ".ltx", ".mkii", ""}},  // why more suffix?
	{kpse_tex_ps_header_format, {".pro"}},
	{kpse_texpool_format, {".pool"}},
	{kpse_texsource_format, {".dtx", ".ins"}},
	{kpse_type1_format, {".pfa", ".pfb"}},
	{kpse_vf_format, {".vf"}},
	{kpse_ist_format, {".ist"}},
	{kpse_truetype_format, {".ttf", ".ttc", ".TTF", ".TTC", ".dfont"}},
	{kpse_type42_format, {".t42", ".T42"}},
	{kpse_web_format, {".web", ".ch"}},
	{kpse_cweb_format, {".w", ".web", ".ch"}},
	{kpse_enc_format, {".enc"}},
	{kpse_sfd_format, {".sfd"}},
	{kpse_opentype_format, {".otf", ".OTF"}},
	{kpse_lig_format, {".lig"}},
	{kpse_lua_format,
	 {".lua", ".luatex", ".luc", ".luctex", ".texlua", ".texluc", ".tlu", ""}},
	{kpse_fea_format, {".fea"}},
	{kpse_cid_format, {".cid", ".cidmap"}},
	{kpse_mlbib_format, {".mlbib", ".bib"}},
	{kpse_mlbst_format, {".mlbst", ".bst"}},
	{kpse_clua_format, {".dll", ".so"}},
	{kpse_ris_format, {".ris"}},
	{kpse_bltxml_format, {".bltxml"}}};

CTANFileManager::CTANFileManager(string_view content) {
	nodes.reserve(5120);  // we have 4846 tlpobj files when commit
	size_t chunk_start = 0;
	// separate tlpobj content
	while (chunk_start < content.size()) {
		size_t chunk_end = content.find("\n\n", chunk_start);
		if (chunk_end == string_view::npos) chunk_end = content.size();
		string_view chunk = content.substr(chunk_start, chunk_end - chunk_start);
		if (!chunk.empty()) {
			auto check_valid_name = [](string_view nodeContent) {
				// HARDCODE
				if (nodeContent.find("srcfiles") == string_view::npos &&
					nodeContent.find("runfiles") == string_view::npos)
					return false;
				if (nodeContent.substr(5, 7) == "scheme-") { return false; }
				if (nodeContent.substr(5, 11) == "collection-") { return false; }
				if (nodeContent.substr(5, 2) == "00") { return true; }
				for (size_t index = 6; index < nodeContent.size(); ++index) {
					if (nodeContent[index] == '\n') return true;
					if (nodeContent[index] == '.') return false;
				}
				return true;
			};
			if (check_valid_name(chunk) == true) nodes.push_back(createNode(chunk));
		}
		chunk_start = (chunk_end == content.size()) ? chunk_end : chunk_end + 2;
	}
}

CTANFileManager::tlpobjNode CTANFileManager::createNode(string_view chunk) {
	// create a new node
	tlpobjNode new_node;
	size_t	   line_start = 0;

	// get next line from trunk
	auto next_line = [&]() -> string_view {
		size_t end = chunk.find('\n', line_start);
		if (end == string_view::npos) end = chunk.size();
		string_view line = chunk.substr(line_start, end - line_start);
		line_start		 = (end == chunk.size()) ? end : end + 1;
		return line;
	};

	tlpobjNode::KeyType currentKey = tlpobjNode::KeyType::None;
	while (line_start < chunk.size()) {
		string_view line = next_line();
		if (line.empty()) continue;
		size_t spacePos = line.find(' ');  // Find key-value separator
		if (spacePos == string_view::npos) continue;
		string_view key	  = line.substr(0, spacePos);
		cppstr		value = cppstr(line.substr(spacePos + 1));
		// HARDCODE
		if (key == "name") { new_node.name = value; }
		else if (key == "catalogue-ctan") { new_node.catalogue_ctan = value; }
		else if (key == "runfiles") { currentKey = tlpobjNode::KeyType::Runfiles; }
		else if (key == "srcfiles") { currentKey = tlpobjNode::KeyType::Srcfiles; }
		else if (currentKey != tlpobjNode::KeyType::None && line[0] == ' ') {
			// Process indented lines
			// Check for optional details parameter
			size_t detailsPos = value.find(" details=");
			if (detailsPos != cppstr::npos) {
				value = value.substr(0, detailsPos);  // Strip details part
			}
			// HARDCODE
			if (value.substr(0, 6) == "RELOC/") {
				value = value.substr(6);  // remove "RELOC/" header
			}
			// Append to corresponding vector
			if (currentKey == tlpobjNode::KeyType::Runfiles) {
				size_t pos		= value.find_last_of('/');
				cppstr filename = (pos != cppstr::npos) ? value.substr(pos + 1) : value;
				name_to_index.insert({filename, pair(("r@" + value), nodes.size())});
			}
			if (currentKey == tlpobjNode::KeyType::Srcfiles) {
				size_t pos		= value.find_last_of('/');
				cppstr filename = (pos != cppstr::npos) ? value.substr(pos + 1) : value;
				name_to_index.insert({filename, pair(("s@" + value), nodes.size())});
			}
		}
		else {
			currentKey = tlpobjNode::KeyType::None;
		}  // Reset context if invalid format
	}
	return new_node;
}
vector<cppstr> CTANFileManager::query_file(
	const cppstr&				request_name,
	const kpse_file_format_type type) const {
	// get result of one filename
	auto traverse_file = [&](const cppstr& filename) -> vector<cppstr> {
		auto it = name_to_index.find(filename);
		if (it != name_to_index.end()) {
			auto& node = nodes[it->second.second];
			return {node.name, node.catalogue_ctan, it->second.first};
		}
		else
			return {};
	};
	cppstr	   query_name	   = request_name;
	const auto only_one_suffix = handle_kpse_format(query_name, type);
	if (only_one_suffix) {
		auto one_suffix_check = traverse_file(query_name);
		if (one_suffix_check.size() != 0) return one_suffix_check;
	}
	else {
		for (const auto& suffix : format_to_suffix[type]) {
			cppstr query_name_for_suffix = query_name + suffix;
			auto   one_of_suffix_check	 = traverse_file(query_name_for_suffix);
			if (one_of_suffix_check.size() != 0) return one_of_suffix_check;
		}
	}
	auto no_suffix_check = traverse_file(request_name);
	if (no_suffix_check.size() != 0) return no_suffix_check;
	// finally we find none
	return {};
}
char* CTANFileManager::get_file(
	const cppstr&				request_name,
	const kpse_file_format_type type) const {
	auto query_result = query_file(request_name, type);
	if (query_result.size() == 0) return nullptr;
	if (query_result[0].substr(0, 2) == "00") {
		// for installer-only files, go to see our file server.
		return kpse_find_file_js(request_name.c_str(), type, false);
	}
	auto fileField	   = query_result[2][0] == 's' ? tlpobjNode::KeyType::Srcfiles :
													 tlpobjNode::KeyType::Runfiles;
	auto relative_path = query_result[2].substr(2);
	auto pos		   = relative_path.find_last_of('/');
	auto filename	   = (pos != cppstr::npos) ? relative_path.substr(pos + 1) :
												 relative_path;	 // alter should not happen
	// HARDCODE
	auto file_path = "/tex/" + filename;
	// copy to cstr
	char* file_path_cstr = static_cast<char*>(malloc(file_path.size() + 1));
	memcpy(file_path_cstr, file_path.c_str(), file_path.size());
	file_path_cstr[file_path.size()] = '\0';
	// check file exist
	if (std::filesystem::exists(file_path) == true)	 // have already got it
		return file_path_cstr;
	// check package file exist, true to extract, else fetch it from website
	// HARDCODE
	auto package_name =
		query_result[0] +
		(fileField == tlpobjNode::KeyType::Srcfiles ? ".source.tar.xz" : ".tar.xz");
	// HARDCODE
	auto package_path = "/tex/pkg/" + package_name;
	if (std::filesystem::exists(package_path) == true) {
		if (extractor::tar_xz(
				package_path.c_str(), relative_path.c_str(), file_path.c_str()) == true)
			return file_path_cstr;
		else
			return nullptr;
	}
	// fetch file content from website
	// HARDCODE
	const auto urlsuffix = "systems/texlive/tlnet/archive/" + package_name;
	ctan_download_pkg_js(urlsuffix.c_str(), package_name.c_str());
	// maybe: 1. got exactly the file; 2. got the package; 3. got nothing
	if (std::filesystem::exists(file_path) == true) {
		// result 1: got exactly the file
		return file_path_cstr;
	}
	// check result 2 or 3
	if (std::filesystem::exists(package_path) == true) {
		// result 2: got the package, then we can directly extract that
		if (extractor::tar_xz(
				package_path.c_str(), relative_path.c_str(), file_path.c_str()) == true)
			return file_path_cstr;
		else
			return nullptr;
	}
	else {
		// result 3: got nothing
		return nullptr;
	}
}

bool CTANFileManager::handle_kpse_format(cppstr& name, const kpse_file_format_type type)
	const {
	// if name end with one of suffix list, return; if suffix list contains only one,
	// add it and return; else return suffix list
	if (format_to_suffix.find(type) != format_to_suffix.end()) {
		const auto& suffix_list = format_to_suffix[type];
		for (auto s : suffix_list) {
			if (strlen(s) != 0 && end_up_with(name, s)) return true;
		}
		if (suffix_list.size() == 1) {
			name += suffix_list[0];
			return true;
		}
		// there are many suffixes for choose
		return false;
	}
	else
		return true;
}

ostream& operator<<(ostream& os, const CTANFileManager& message) {
	for (const auto& fileQuery : message.name_to_index) {
		const auto& node = message.nodes[fileQuery.second.second];
		os << fileQuery.first << " " << fileQuery.second.first << " " << node.name << " "
		   << node.catalogue_ctan << std::endl;
	}
	// for (const auto& node : message.nodes) {
	// 	if (node.catalogue_ctan.size() == 0) std::cout << node.name << std::endl;
	// }
	return os;
}
