#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

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

	tlpobjNode(const std::string& configContent) {
		std::istringstream stream(configContent);
		std::string		   line;
		KeyType			   currentKey = KeyType::None;	// Track current parsing context

		while (std::getline(stream, line)) {
			if (line.empty()) continue;

			size_t spacePos = line.find(' ');  // Find key-value separator
			if (spacePos == std::string::npos) continue;

			std::string key	  = line.substr(0, spacePos);
			std::string value = line.substr(spacePos + 1);

			if (key == "name") { name = value; }  // Store project name
			else if (key == "catalogue-ctan") {
				catalogue_ctan = value;
			}  // Store project name
			else if (key == "depend") {
				depend.push_back(value);
			}  // Add dependency entry
			else if (key == "docfiles") { currentKey = KeyType::Docfiles; }
			else if (key == "runfiles") { currentKey = KeyType::Runfiles; }
			else if (key == "srcfiles") { currentKey = KeyType::Srcfiles; }
			else if (key == "binfiles") { currentKey = KeyType::Binfiles; }
			else if (currentKey != KeyType::None && line[0] == ' ') {  // Process indented
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

	tlpobjNode(std::string_view configContent) {
		size_t line_start = 0;

		// get next line from configContent
		auto next_line = [&]() -> std::string_view {
			size_t end = configContent.find('\n', line_start);
			if (end == std::string_view::npos) end = configContent.size();

			std::string_view line = configContent.substr(line_start, end - line_start);
			line_start			  = (end == configContent.size()) ? end : end + 1;
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
			else if (currentKey != KeyType::None && line[0] == ' ') {  // Process indented
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
	KeyType FindFile(const std::string& filename) const {  // Find file's category
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
};

// Custom output formatting
std::ostream& operator<<(std::ostream& os, const tlpobjNode& config) {
	os << "Name: " << config.name << "\n";	// Project name
	os << "Catalogue CTAN: " << config.catalogue_ctan << "\n";
	os << "Depend (" << config.depend.size() << "):";  // Dependencies list
	for (const auto& dep : config.depend) { os << " " << dep; }
	os << "\n";
	os << "Docfiles (" << config.docfiles.size() << "):";  // Documentation files list
	for (const auto& file : config.docfiles) { os << " " << file; }
	os << "\n";
	os << "Runfiles (" << config.runfiles.size() << "):";  // Runtime files list
	for (const auto& file : config.runfiles) { os << " " << file; }
	os << "\n";
	os << "Srcfiles (" << config.srcfiles.size() << "):";  // Source files list
	for (const auto& file : config.srcfiles) { os << " " << file; }
	os << "\n";
	os << "Binfiles (" << config.binfiles.size() << "):";  // Binary files list
	for (const auto& file : config.binfiles) { os << " " << file; }
	os << "\n";
	return os;
}

const std::vector<tlpobjNode> parseTexliveTlpdb(const std::string& filename) {
	std::vector<tlpobjNode> nodes;
	std::ifstream			file(filename);
	std::string				current_block;
	std::string				line;

	// reserve enough space
	nodes.reserve(5120);  // we have 4846 tlpobj files when commit

	while (std::getline(file, line)) {
		if (line.empty()) {
			if (!current_block.empty()) {
				nodes.emplace_back(std::move(current_block));
				current_block.clear();
			}
		}
		else {
			current_block += line;
			current_block += "\n";
		}
	}

	if (!current_block.empty()) { nodes.emplace_back(std::move(current_block)); }
	nodes.reserve(nodes.size());
	return nodes;
}

const std::vector<tlpobjNode> parseTexliveTlpdb(std::string_view content) {
	std::vector<tlpobjNode> nodes;
	nodes.reserve(5120);  // we have 4846 tlpobj files when commit

	size_t chunk_start = 0;
	while (chunk_start < content.size()) {
		size_t chunk_end = content.find("\n\n", chunk_start);
		if (chunk_end == std::string_view::npos) chunk_end = content.size();
		std::string_view chunk = content.substr(chunk_start, chunk_end - chunk_start);
		if (!chunk.empty()) {
			nodes.emplace_back(std::move(tlpobjNode(chunk)));  // 传递string_view
		}
		chunk_start = (chunk_end == content.size()) ? chunk_end : chunk_end + 2;
	}
	return nodes;
}

// const std::vector<tlpobjNode> parseTexliveTlpdb(const std::string& filename) {
// 	std::vector<tlpobjNode> nodes;
// 	std::ifstream			file(filename, std::ios::binary);
// 	constexpr size_t		BUFFER_SIZE = 20 * (1 << 20);  // 1MB缓冲区
// 	char					buffer[BUFFER_SIZE];

// 	std::string leftover;  // 保存跨缓冲区未处理的数据
// 	nodes.reserve(5120);

// 	while (file) {
// 		file.read(buffer, BUFFER_SIZE);
// 		const size_t	 bytes_read = file.gcount();
// 		std::string_view chunk(buffer, bytes_read);

// 		// 合并遗留数据和当前块
// 		std::string combined = std::move(leftover);
// 		combined.append(chunk);

// 		size_t start_pos = 0;
// 		while (true) {
// 			size_t end_pos = combined.find("\n\n", start_pos);
// 			if (end_pos == std::string::npos) break;

// 			// 提取有效块（不包含结尾的\n\n）
// 			std::string block = combined.substr(start_pos, end_pos - start_pos);
// 			nodes.emplace_back(std::move(block));

// 			start_pos = end_pos + 2;  // 跳过两个换行符
// 		}

// 		// 保存未处理完的数据
// 		leftover = combined.substr(start_pos);
// 	}

// 	// 处理最后一个块（无结尾\n\n的情况）
// 	if (!leftover.empty()) { nodes.emplace_back(std::move(leftover)); }

// 	return nodes;
// }

int main(int argc, char* argv[]) {
	std::ifstream file(argv[1]);
	if (!file.is_open()) {
		std::cerr << "Failed to open config file!" << std::endl;
		return 1;
	}
	std::string fileContent(
		(std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	auto texlive_tlpdb = parseTexliveTlpdb(std::string_view(fileContent));
	for (auto& node : texlive_tlpdb) std::cout << node << std::endl;
	return 0;
}
