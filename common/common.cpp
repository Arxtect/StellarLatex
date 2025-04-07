#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string_view>
#include <vector>

#include "common.hpp"
using std::ostream;
using std::pair;
using std::string;
using std::string_view;
using std::vector;
using cstr = const char*;

// TO BE FINISHED:
// optimise: AST Tree
// how .sty file is built
// optimize depend to number
// in addition of texlive tlcontrib

inline bool end_up_with(const string& str, cstr suffix) {
	const size_t str_length	   = str.size();
	const size_t suffix_length = strlen(suffix);
	return str_length >= suffix_length &&
		   str.compare(str_length - suffix_length, suffix_length, suffix) == 0;
}
inline bool end_up_with(const string& str, const string& suffix) {
	if (str.size() < suffix.size()) return false;
	return str.substr(str.size() - suffix.size()) == suffix;
}

std::map<kpse_file_format_type, vector<cstr>> CTANFileManager::format_to_suffix = {
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
	  ".mlo", ".cfg", ".ltx", ".mkii"}},  // why more suffix?
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
	 {".lua", ".luatex", ".luc", ".luctex", ".texlua", ".texluc", ".tlu"}},
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
				if (nodeContent.substr(5, 7) == "scheme-") { return false; }
				if (nodeContent.substr(5, 11) == "collection-") { return false; }
				if (nodeContent.substr(5, 2) == "00") { return true; }
				for (size_t index = 6; index < nodeContent.size(); ++index) {
					if (nodeContent[index] == '\n') return true;
					if (nodeContent[index] == '.') return false;
				}
				return true;
			};
			if (check_valid_name(chunk) == true) { nodes.push_back(createNode(chunk)); }
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
		string		value = string(line.substr(spacePos + 1));
		if (key == "name") { new_node.name = value; }
		else if (key == "catalogue-ctan") { new_node.catalogue_ctan = value; }
		else if (key == "runfiles") { currentKey = tlpobjNode::KeyType::Runfiles; }
		else if (key == "srcfiles") { currentKey = tlpobjNode::KeyType::Srcfiles; }
		else if (currentKey != tlpobjNode::KeyType::None && line[0] == ' ') {
			// Process indented lines
			// Check for optional details parameter
			size_t detailsPos = value.find(" details=");
			if (detailsPos != string::npos) {
				value = value.substr(0, detailsPos);  // Strip details part
			}
			// Append to corresponding vector
			if (currentKey == tlpobjNode::KeyType::Runfiles ||
				currentKey == tlpobjNode::KeyType::Srcfiles) {
				size_t pos		= value.find_last_of('/');
				string filename = (pos != string::npos) ? value.substr(pos + 1) : value;
				name_to_index.insert({filename, pair(value, nodes.size())});
			}
		}
		else {
			currentKey = tlpobjNode::KeyType::None;
		}  // Reset context if invalid format
	}
	return new_node;
}
ostream& operator<<(ostream& os, const CTANFileManager& m) {
	return os;
}
pair<string, string> CTANFileManager::query_file(
	const string&				request_name,
	const kpse_file_format_type type) {
	string	   query_name	   = request_name;
	const auto only_one_suffix = handle_kpse_format(query_name, type);
	// get result of one filename
	auto traverse_file = [&](const string& filename) {
		auto it = name_to_index.find(filename);
		if (it != name_to_index.end()) {
			auto& node = nodes[it->second.second];
			return pair<string, string>(node.name, it->second.first);
		}
		else
			return pair<string, string>("", "");
	};
	if (only_one_suffix) { return traverse_file(query_name); }
	else {
		for (const auto& suffix : format_to_suffix[type]) {
			string query_name_for_suffix = query_name + suffix;
			auto   query_result			 = traverse_file(query_name_for_suffix);
			if (query_result.first != "") return query_result;
		}
		return pair<string, string>("", "");
	}
}

bool CTANFileManager::handle_kpse_format(string& name, const kpse_file_format_type type) {
	// return suffix result
	// if name end with one of suffix list, return; if suffix list contains only one,
	// add it and return; else return suffix list
	if (format_to_suffix.find(type) != format_to_suffix.end()) {
		const auto& suffix_list = format_to_suffix[type];
		for (auto s : suffix_list) {
			if (end_up_with(name, s)) return true;
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
