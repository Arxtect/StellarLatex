#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

// TO BE FINISHED:
// optimise: AST Tree
// how .sty file is built
// optimize depend to number
// in addition of texlive tlcontrib

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
					for (int index = 6; index< nodeContent.size(); ++index) {
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
		for (auto& node : m.nodes) { node.print_output(os, m.nodes); os << '\n'; }
		return os;
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
	std::vector<tlpobjNode> nodes;
};

int main(int argc, char* argv[]) {
	std::ifstream file(argv[1]);
	if (!file.is_open()) {
		std::cerr << "Failed to open config file!" << std::endl;
		return 1;
	}
	std::string fileContent(
		(std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	CTANFileManager texlive_tlpdb{std::string_view(fileContent)};
	std::cout << texlive_tlpdb;
	return 0;
}
