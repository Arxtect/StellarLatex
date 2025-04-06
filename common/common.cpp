#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string_view>
#include <vector>

#include "common.hpp"

// TO BE FINISHED:
// optimise: AST Tree
// how .sty file is built
// optimize depend to number
// in addition of texlive tlcontrib

inline bool end_up_with(const std::string& str, const char* suffix) {
	const size_t str_length	   = str.size();
	const size_t suffix_length = strlen(suffix);
	return str_length >= suffix_length &&
		   str.compare(str_length - suffix_length, suffix_length, suffix) == 0;
}
inline bool end_up_with(const std::string& str, const std::string& suffix) {
	if (str.size() < suffix.size()) return false;
	return str.substr(str.size() - suffix.size()) == suffix;
}

class CTANFileManager {
public:
	CTANFileManager() = delete;
	/**
	 * @brief build a new CTANFileManager from texlive.tlpdb
	 *
	 * @param content file content of texlive.tlpdb
	 */
	CTANFileManager(std::string_view content) {
		std::vector<std::vector<std::string>> temp_dependencies;
		nodes.reserve(5120);  // we have 4846 tlpobj files when commit
		temp_dependencies.reserve(5120);
		size_t chunk_start = 0;
		// separate tlpobj content
		while (chunk_start < content.size()) {
			size_t chunk_end = content.find("\n\n", chunk_start);
			if (chunk_end == std::string_view::npos) chunk_end = content.size();
			std::string_view chunk = content.substr(chunk_start, chunk_end - chunk_start);
			if (!chunk.empty()) {
				// this can be optimized
				// filter invalid name. Now is: name begin with 'scheme-', or
				// 'collection-', or with dot in it, do false
				auto check_valid_name = [](std::string_view nodeContent) {
					if (nodeContent.substr(5, 7) == "scheme-") { return false; }
					if (nodeContent.substr(5, 11) == "collection-") { return false; }
					for (int index = 6; index < nodeContent.size(); ++index) {
						if (nodeContent[index] == '\n') return true;
						if (nodeContent[index] == '.') return false;
					}
					return true;
				};
				if (check_valid_name(chunk) == true)
					nodes.emplace_back(std::move(tlpobjNode(chunk, temp_dependencies)));
			}
			chunk_start = (chunk_end == content.size()) ? chunk_end : chunk_end + 2;
		}
		// build dependency
		std::vector<std::string_view> name_index;
		name_index.reserve(nodes.size());
		for (const auto& node : nodes) { name_index.push_back(node.name); }
		for (size_t i = 0; i < nodes.size(); ++i) {
			for (const auto& dep_name : temp_dependencies[i]) {
				auto it =
					std::lower_bound(name_index.begin(), name_index.end(), dep_name);
				if (it != name_index.end() && *it == dep_name) {
					nodes[i].depend.push_back(
						static_cast<int>(std::distance(name_index.begin(), it)));
				}
			}
		}
	}
	friend std::ostream& operator<<(std::ostream& os, const CTANFileManager& m) {
		for (auto& node : m.nodes) {
			node.print_output(os, m.nodes);
			os << '\n';
		}
		return os;
	}
	/**
	 * @brief find where the query file is
	 *
	 * @param request_name query file name
	 * @param type query file type
	 * @return catagory name & relative path, catagory name "" for fail
	 */
	std::pair<std::string, std::string>
	query_file(const std::string& request_name, const kpse_file_format_type type) {
		std::string query_name	= '/' + request_name;
		const auto	suffix_list = handle_kpse_format(query_name, type);
		// get result of one filename
		auto traverse_file = [&](const std::string& filename) {
			std::string query_result;
			for (auto node : nodes) {
				if (node.query_file(filename, query_result))
					return std::pair<std::string, std::string>(node.name, query_result);
			}
			return std::pair<std::string, std::string>("", "");
		};
		if (suffix_list.size() == 0) { return traverse_file(query_name); }
		else {
			for (const auto& suffix: suffix_list) {
				std::string query_name_for_suffix = query_name + suffix;
				auto		query_result		  = traverse_file(query_name_for_suffix);
				if (query_result.first != "") return query_result;
			}
			return std::pair<std::string, std::string>("", "");
		}
	}

private:
	/**
	 * @brief one tlpobj node contains one module information
	 *
	 */
	class tlpobjNode {
	public:
		enum class KeyType { None, Name, Depend, Runfiles, Srcfiles };
		std::string				  name;
		std::string				  catalogue_ctan;
		std::vector<unsigned int> depend;
		std::vector<std::string>  runfiles;
		std::vector<std::string>  srcfiles;
		/**
		 * @brief build node from content
		 *
		 * @param configContent content of one node
		 */
		tlpobjNode(
			std::string_view					   configContent,
			std::vector<std::vector<std::string>>& temp_dependencies) {
			size_t					 line_start = 0;
			std::vector<std::string> local_depend;

			// get next line from configContent
			auto next_line = [&]() -> std::string_view {
				size_t end = configContent.find('\n', line_start);
				if (end == std::string_view::npos) end = configContent.size();

				std::string_view line =
					configContent.substr(line_start, end - line_start);
				line_start = (end == configContent.size()) ? end : end + 1;
				return line;
			};

			KeyType currentKey = KeyType::None;
			while (line_start < configContent.size()) {
				std::string_view line = next_line();
				if (line.empty()) continue;

				size_t spacePos = line.find(' ');  // Find key-value separator
				if (spacePos == std::string_view::npos) continue;

				std::string_view key   = line.substr(0, spacePos);
				std::string		 value = std::string(line.substr(spacePos + 1));

				if (key == "name") { name = value; }
				else if (key == "depend") { local_depend.push_back(value); }
				else if (key == "catalogue-ctan") { catalogue_ctan = value; }
				else if (key == "runfiles") { currentKey = KeyType::Runfiles; }
				else if (key == "srcfiles") { currentKey = KeyType::Srcfiles; }
				else if (currentKey != KeyType::None && line[0] == ' ') {
					// Process indented lines
					// Check for optional details parameter
					size_t detailsPos = value.find(" details=");
					if (detailsPos != std::string::npos) {
						value = value.substr(0, detailsPos);  // Strip details part
					}
					// Append to corresponding vector
					switch (currentKey) {
						case KeyType::Runfiles: runfiles.push_back(value); break;
						case KeyType::Srcfiles: srcfiles.push_back(value); break;
						default: break;
					}
				}
				else { currentKey = KeyType::None; }  // Reset context if invalid format
			}
			temp_dependencies.push_back(std::move(local_depend));
		}
		/**
		 * @brief get query of file in which category
		 *
		 * @param filename
		 * @return KeyType
		 */
		KeyType FindFile(const std::string& filename) const {
			// Lambda to extract filename from path
			auto match = [&filename](const std::string& path) {
				size_t		lastSlash = path.find_last_of('/');
				std::string fileInPath =
					(lastSlash == std::string::npos) ? path : path.substr(lastSlash + 1);
				return fileInPath == filename;
			};

			for (const auto& file : runfiles) {
				if (match(file)) return KeyType::Runfiles;
			}
			for (const auto& file : srcfiles) {
				if (match(file)) return KeyType::Srcfiles;
			}
			return KeyType::None;
		}
		bool query_file(const std::string& filename, std::string& query_result) const {
			for (const auto& file : srcfiles) {
				if (end_up_with(file, filename)) {
					query_result = file;
					return true;
				}
			}
			for (const auto& file : runfiles) {
				if (end_up_with(file, filename)) {
					query_result = file;
					return true;
				}
			}
			return false;
		}
		friend std::ostream& operator<<(std::ostream& os, const tlpobjNode& node) {
			os << "Name: " << node.name << "\n";  // Project name
			os << "Catalogue CTAN: " << node.catalogue_ctan << "\n";
			os << "Depend (" << node.depend.size() << "):";	 // Dependencies list
			for (const auto& dep : node.depend) { os << " " << dep; }
			os << "\n";
			os << "Runfiles (" << node.runfiles.size() << "):";	 // Runtime files list
			for (const auto& file : node.runfiles) { os << " " << file; }
			os << "\n";
			os << "Srcfiles (" << node.srcfiles.size() << "):";	 // Source files list
			for (const auto& file : node.srcfiles) { os << " " << file; }
			os << "\n";
			return os;
		}
		void print_output(std::ostream& os, const std::vector<tlpobjNode>& nodes) const {
			os << "Name: " << name << "\n";	 // Project name
			os << "Catalogue CTAN: " << catalogue_ctan << "\n";
			os << "Depend (" << depend.size() << "):";	// Dependencies list
			for (const auto& dep : depend) { os << " " << nodes[dep].name; }
			os << "\n";
			os << "Runfiles (" << runfiles.size() << "):";	// Runtime files list
			for (const auto& file : runfiles) { os << " " << file; }
			os << "\n";
			os << "Srcfiles (" << srcfiles.size() << "):";	// Source files list
			for (const auto& file : srcfiles) { os << " " << file; }
			os << "\n";
		}
	};
	/**
	 * @brief give a correct format of the query file
	 *
	 * @param name file name, may be changed
	 * @param type file type
	 * @return nullptr for no more handle, else the suffix list
	 */
	std::vector<const char*> handle_kpse_format(std::string& name, const kpse_file_format_type type) {
		const size_t name_length = name.length();
		// retur suffix result
		// if name end with one of suffix list, return; if suffix list contains only one,
		// add it and return; else return suffix list
		auto handle_suffixes = [&name,
								&name_length](std::vector<const char*> suffix_list) -> std::vector<const char*> {
			for (auto s:suffix_list) {
				if (end_up_with(name, s)) return std::vector<const char*>{};
			}
			if (suffix_list.size() == 1) {
				name += suffix_list[0];
				return std::vector<const char*>{};
			}
			return suffix_list;
		};
		switch (type) {
			case kpse_gf_format: {
				std::vector<const char*> suffix_list = {"gf"};
				return handle_suffixes(suffix_list);
			}
			case kpse_pk_format: {
				std::vector<const char*> suffix_list = {"pk"};
				return handle_suffixes(suffix_list);
			}
			case kpse_any_glyph_format: {  // TODO: not completed yet
				return std::vector<const char*>{};
			}
			case kpse_tfm_format: {
				std::vector<const char*> suffix_list = {".tfm"};
				return handle_suffixes(suffix_list);
			}
			case kpse_afm_format: {
				std::vector<const char*> suffix_list = {".afm"};
				return handle_suffixes(suffix_list);
			}
			case kpse_base_format: {
				std::vector<const char*> suffix_list = {".base"};
				return handle_suffixes(suffix_list);
			}
			case kpse_bib_format: {
				std::vector<const char*> suffix_list = {".bib"};
				return handle_suffixes(suffix_list);
			}
			case kpse_bst_format: {
				std::vector<const char*> suffix_list = {".bst"};
				return handle_suffixes(suffix_list);
			}
			case kpse_cnf_format: {
				std::vector<const char*> suffix_list = {".cnf"};
				return handle_suffixes(suffix_list);
			}
			case kpse_db_format: {
				std::vector<const char*> suffix_list = {"ls-R", "ls-r"};
				return handle_suffixes(suffix_list);
			}
			case kpse_fmt_format: {
				std::vector<const char*> suffix_list = {".fmt"};
				return handle_suffixes(suffix_list);
			}
			case kpse_fontmap_format: {
				std::vector<const char*> suffix_list = {".map"};
				return handle_suffixes(suffix_list);
			}
			case kpse_mem_format: {
				std::vector<const char*> suffix_list = {".mem"};
				return handle_suffixes(suffix_list);
			}
			case kpse_mf_format: {
				std::vector<const char*> suffix_list = {".mf"};
				return handle_suffixes(suffix_list);
			}
			case kpse_mft_format: {
				std::vector<const char*> suffix_list = {".mft"};
				return handle_suffixes(suffix_list);
			}
			case kpse_mfpool_format: {
				std::vector<const char*> suffix_list = {".pool"};
				return handle_suffixes(suffix_list);
			}
			case kpse_mp_format: {
				std::vector<const char*> suffix_list = {".mp"};
				return handle_suffixes(suffix_list);
			}
			case kpse_mppool_format: {
				std::vector<const char*> suffix_list = {".pool"};
				return handle_suffixes(suffix_list);
			}
			case kpse_mpsupport_format: {  // TODO: not completed yet
				return std::vector<const char*>{};
			}
			case kpse_ocp_format: {
				std::vector<const char*> suffix_list = {".ocp"};
				return handle_suffixes(suffix_list);
			}
			case kpse_ofm_format: {
				std::vector<const char*> suffix_list = {".ofm"};
				return handle_suffixes(suffix_list);
			}
			case kpse_opl_format: {
				std::vector<const char*> suffix_list = {".opl"};
				return handle_suffixes(suffix_list);
			}
			case kpse_otp_format: {
				std::vector<const char*> suffix_list = {".otp"};
				return handle_suffixes(suffix_list);
			}
			case kpse_ovf_format: {
				std::vector<const char*> suffix_list = {".ovf", ".vf"};
				return handle_suffixes(suffix_list);
			}
			case kpse_ovp_format: {
				std::vector<const char*> suffix_list = {".ovp", ".vpl"};
				return handle_suffixes(suffix_list);
			}
			case kpse_pict_format: {
				std::vector<const char*> suffix_list = {".eps", ".epsi"};
				return handle_suffixes(suffix_list);
			}
			case kpse_tex_format: {
				// std::vector<const char*> suffix_list = {".tex", ".sty", ".cls", ".fd",	 ".aux",
				// 							 ".bbl", ".def", ".clo", ".ldf"};
				std::vector<const char*> suffix_list = {".tex", ".sty", ".cls", ".fd",	 ".aux",
											 ".bbl", ".def", ".clo", ".ldf"};
				return handle_suffixes(suffix_list);
			}
			case kpse_tex_ps_header_format: {
				std::vector<const char*> suffix_list = {".pro"};
				return handle_suffixes(suffix_list);
			}
			case kpse_texdoc_format: {	// TODO: not completed yet, see tex-file.c
				return std::vector<const char*>{};
			}
			case kpse_texpool_format: {
				std::vector<const char*> suffix_list = {".pool"};
				return handle_suffixes(suffix_list);
			}
			case kpse_texsource_format: {
				std::vector<const char*> suffix_list = {".dtx", ".ins"};
				return handle_suffixes(suffix_list);
			}
			case kpse_troff_font_format: {	// TODO: not completed yet, see tex-file.c
				return std::vector<const char*>{};
			}
			case kpse_type1_format: {
				std::vector<const char*> suffix_list = {".pfa", ".pfb"};
				return handle_suffixes(suffix_list);
			}
			case kpse_vf_format: {
				std::vector<const char*> suffix_list = {".vf"};
				return handle_suffixes(suffix_list);
			}
			case kpse_dvips_config_format: {
				return std::vector<const char*>{};
			}
			case kpse_ist_format: {
				std::vector<const char*> suffix_list = {".ist"};
				return handle_suffixes(suffix_list);
			}
			case kpse_truetype_format: {
				std::vector<const char*> suffix_list = {".ttf", ".ttc",   ".TTF",
											 ".TTC", ".dfont"};
				return handle_suffixes(suffix_list);
			}
			case kpse_type42_format: {
				std::vector<const char*> suffix_list = {".t42", ".T42"};
				return handle_suffixes(suffix_list);
			}
			case kpse_web2c_format: {
				return std::vector<const char*>{};
			}
			case kpse_program_text_format: {  // we don't need it
				return std::vector<const char*>{};
			}
			case kpse_program_binary_format: {	// we don't need it
				return std::vector<const char*>{};
			}
			case kpse_miscfonts_format: {
				return std::vector<const char*>{};
			}
			case kpse_web_format: {
				std::vector<const char*> suffix_list = {".web", ".ch"};
				return handle_suffixes(suffix_list);
			}
			case kpse_cweb_format: {
				std::vector<const char*> suffix_list = {".w", ".web", ".ch"};
				return handle_suffixes(suffix_list);
			}
			case kpse_enc_format: {
				std::vector<const char*> suffix_list = {".enc"};
				return handle_suffixes(suffix_list);
			}
			case kpse_cmap_format: {
				return std::vector<const char*>{};
			}
			case kpse_sfd_format: {
				std::vector<const char*> suffix_list = {".sfd"};
				return handle_suffixes(suffix_list);
			}
			case kpse_opentype_format: {
				std::vector<const char*> suffix_list = {".otf", ".OTF"};
				return handle_suffixes(suffix_list);
			}
			case kpse_pdftex_config_format: {
				return std::vector<const char*>{};
			}
			case kpse_lig_format: {
				std::vector<const char*> suffix_list = {".lig"};
				return handle_suffixes(suffix_list);
			}
			case kpse_texmfscripts_format: {
				return std::vector<const char*>{};
			}
			case kpse_lua_format: {
				std::vector<const char*> suffix_list = {".lua",	".luatex", ".luc", ".luctex",
											 ".texlua", ".texluc", ".tlu"};
				return handle_suffixes(suffix_list);
			}
			case kpse_fea_format: {
				std::vector<const char*> suffix_list = {".fea"};
				return handle_suffixes(suffix_list);
			}
			case kpse_cid_format: {
				std::vector<const char*> suffix_list = {".cid", ".cidmap"};
				return handle_suffixes(suffix_list);
			}
			case kpse_mlbib_format: {
				std::vector<const char*> suffix_list = {".mlbib", ".bib"};
				return handle_suffixes(suffix_list);
			}
			case kpse_mlbst_format: {
				std::vector<const char*> suffix_list = {".mlbst", ".bst"};
				return handle_suffixes(suffix_list);
			}
			case kpse_clua_format: {
				std::vector<const char*> suffix_list = {".dll", ".so"};
				return handle_suffixes(suffix_list);
			}
			case kpse_ris_format: {
				std::vector<const char*> suffix_list = {".ris"};
				return handle_suffixes(suffix_list);
			}
			case kpse_bltxml_format: {
				std::vector<const char*> suffix_list = {".bltxml"};
				return handle_suffixes(suffix_list);
			}
			default: return std::vector<const char*>{};
		}
		return std::vector<const char*>{};
	}

	std::vector<tlpobjNode> nodes;
};

int main(int argc, char* argv[]) {
	std::ifstream file("/home/kali/desktop/demo/texlive.tlpdb");
	if (!file.is_open()) {
		std::cerr << "Failed to open config file!" << std::endl;
		return 1;
	}
	std::string fileContent(
		(std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	CTANFileManager texlive_tlpdb{std::string_view(fileContent)};
	file.close();
	while (std::cin.good()) {
		std::string filename;
		int			format_number;
		std::cin >> filename >> format_number;
		if (std::cin.eof()) return 0;
		auto query_result =
			texlive_tlpdb.query_file(filename, kpse_file_format_type(format_number));
		std::cout << query_result.first << "," << query_result.second << "." << std::endl;
	}
	return 0;
}
