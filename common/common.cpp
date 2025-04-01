#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

class CTANFileManager {
public:
	CTANFileManager() = delete;
	/**
	 * @brief build a new CTANFileManager from texlive.tlpdb
	 * 
	 * @param content file content of texlive.tlpdb
	 */
	CTANFileManager(std::string_view content) {
		nodes.reserve(5120);  // we have 4846 tlpobj files when commit
		size_t chunk_start = 0;
		// separate tlpobj content
		while (chunk_start < content.size()) {
			size_t chunk_end = content.find("\n\n", chunk_start);
			if (chunk_end == std::string_view::npos) chunk_end = content.size();
			std::string_view chunk = content.substr(chunk_start, chunk_end - chunk_start);
			if (!chunk.empty()) {
				nodes.emplace_back(std::move(tlpobjNode(chunk)));  // 传递string_view
			}
			chunk_start = (chunk_end == content.size()) ? chunk_end : chunk_end + 2;
		}
	}
	friend std::ostream& operator<<(std::ostream& os, const CTANFileManager& m) {
		for (auto& node : m.nodes) { os << node << std::endl; }
		return os;
	}

private:
	/**
	 * @brief one tlpobj node contains one module information
	 * 
	 */
	class tlpobjNode {
	public:
		enum class KeyType { None, Name, Depend, Docfiles, Runfiles, Srcfiles, Binfiles };
		std::string				 name;
		std::string				 catalogue_ctan;
		std::vector<std::string> depend;
		std::vector<std::string> docfiles;
		std::vector<std::string> runfiles;
		std::vector<std::string> srcfiles;
		std::vector<std::string> binfiles;
		/**
		 * @brief build node from content
		 * 
		 * @param configContent content of one node
		 */
		tlpobjNode(std::string_view configContent) {
			size_t line_start = 0;

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
				else if (key == "depend") { depend.push_back(value); }
				else if (key == "catalogue-ctan") { catalogue_ctan = value; }
				else if (key == "docfiles") { currentKey = KeyType::Docfiles; }
				else if (key == "runfiles") { currentKey = KeyType::Runfiles; }
				else if (key == "srcfiles") { currentKey = KeyType::Srcfiles; }
				else if (key == "binfiles") { currentKey = KeyType::Binfiles; }
				else if (currentKey != KeyType::None && line[0] == ' ') {  // Process
																		   // indented
																		   // lines
					// Check for optional details parameter
					size_t detailsPos = value.find(" details=");
					if (detailsPos != std::string::npos) {
						value = value.substr(0, detailsPos);  // Strip details part
					}
					// Append to corresponding vector
					switch (currentKey) {
						case KeyType::Docfiles: docfiles.push_back(value); break;
						case KeyType::Runfiles: runfiles.push_back(value); break;
						case KeyType::Srcfiles: srcfiles.push_back(value); break;
						case KeyType::Binfiles: binfiles.push_back(value); break;
						default: break;
					}
				}
				else { currentKey = KeyType::None; }  // Reset context if invalid format
			}
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

			for (const auto& file : docfiles) {
				if (match(file)) return KeyType::Docfiles;
			}
			for (const auto& file : runfiles) {
				if (match(file)) return KeyType::Runfiles;
			}
			for (const auto& file : srcfiles) {
				if (match(file)) return KeyType::Srcfiles;
			}
			for (const auto& file : binfiles) {
				if (match(file)) return KeyType::Binfiles;
			}
			return KeyType::None;
		}
		friend std::ostream& operator<<(std::ostream& os, const tlpobjNode& node) {
			os << "Name: " << node.name << "\n";  // Project name
			os << "Catalogue CTAN: " << node.catalogue_ctan << "\n";
			os << "Depend (" << node.depend.size() << "):";	 // Dependencies list
			for (const auto& dep : node.depend) { os << " " << dep; }
			os << "\n";
			os << "Docfiles (" << node.docfiles.size()
			   << "):";	 // Documentation files list
			for (const auto& file : node.docfiles) { os << " " << file; }
			os << "\n";
			os << "Runfiles (" << node.runfiles.size() << "):";	 // Runtime files list
			for (const auto& file : node.runfiles) { os << " " << file; }
			os << "\n";
			os << "Srcfiles (" << node.srcfiles.size() << "):";	 // Source files list
			for (const auto& file : node.srcfiles) { os << " " << file; }
			os << "\n";
			os << "Binfiles (" << node.binfiles.size() << "):";	 // Binary files list
			for (const auto& file : node.binfiles) { os << " " << file; }
			os << "\n";
			return os;
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
