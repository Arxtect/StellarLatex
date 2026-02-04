#include "control_utils.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include "kpathsea/filequery.hpp"
namespace fs = std::filesystem;

bool HashDB::hashDiffer::is_any_changed() const {
	return !added.empty() || !removed.empty();
}
bool HashDB::hashDiffer::is_tex_changed() const {
	return hasFileWithExt(added, ".tex") || hasFileWithExt(removed, ".tex");
}
bool HashDB::hashDiffer::is_bib_changed() const {
	return hasFileWithExt(added, ".bib") || hasFileWithExt(removed, ".bib");
}
bool HashDB::hashDiffer::is_idx_changed() const {
	return hasFileWithExt(added, ".idx") || hasFileWithExt(removed, ".idx");
}
bool HashDB::hashDiffer::is_this_changed(const vecstr& fileList) const {
	for (const auto& file : fileList) {
		if (added.find(file) != added.end() || removed.find(file) != removed.end()) {
			return true;
		}
	}
	return false;
}
std::ostream& operator<<(std::ostream& os, const HashDB::hashDiffer& data) {
	for (auto& [first, second] : data.added) {
		os << "> \"" << first << "\"=0x" << std::hex << second << std::oct << "\n";
	}
	for (auto& [first, second] : data.removed) {
		os << "< \"" << first << "\"=0x" << std::hex << second << std::oct << "\n";
	}
	return os;
}
bool HashDB::hashDiffer::hasFileWithExt(const hashList& list, const char* extension)
	const {
	const size_t extLen = strlen(extension);
	for (const auto& pair : list) {
		const std::string& filename = pair.first;
		if (filename.length() >= extLen &&
			filename.substr(filename.length() - extLen) == extension) {
			return true;
		}
	}
	return false;
}
void HashDB::buildDB() {
	db.clear();
	try {
		for (const auto& entry : fs::recursive_directory_iterator("/work")) {
			if (entry.is_regular_file()) {
				std::string absolutePath = fs::absolute(entry.path()).string();
				db[absolutePath]		 = simpleHash(absolutePath);
			}
		}
	}
	catch (...) {
	}
}

void HashDB::loadDB() {
	std::ifstream file("/tmp/hash.db", std::ios::binary);
	if (!file.is_open()) return;
	db.clear();
	uint32_t size;
	file.read(reinterpret_cast<char*>(&size), sizeof(size));
	for (uint32_t i = 0; i < size; ++i) {
		uint32_t pathLength;
		file.read(reinterpret_cast<char*>(&pathLength), sizeof(pathLength));

		std::string path(pathLength, '\0');
		file.read(&path[0], pathLength);

		uint32_t hashValue;
		file.read(reinterpret_cast<char*>(&hashValue), sizeof(hashValue));

		db[path] = hashValue;
	}
}

void HashDB::saveDB() {
	if (db.empty()) return;
	std::ofstream file("/tmp/hash.db", std::ios::binary);
	if (!file.is_open()) return;

	uint32_t size = db.size();
	file.write(reinterpret_cast<const char*>(&size), sizeof(size));

	for (const auto& pair : db) {
		uint32_t pathLength = pair.first.size();
		file.write(reinterpret_cast<const char*>(&pathLength), sizeof(pathLength));
		file.write(pair.first.c_str(), pathLength);
		file.write(reinterpret_cast<const char*>(&pair.second), sizeof(pair.second));
	}
}

extern std::set<cppstr> changed_files;
cppstr getFileNameFromPath(const cppstr& path);
HashDB::hashDiffer HashDB::operator-(const HashDB& rhs) {
	hashDiffer result;
	for (const auto& pair : db) {
		auto it = rhs.db.find(pair.first);
		if (it == rhs.db.end() || it->second != pair.second) {
			result.added[pair.first] = pair.second;
		}
		if (it == db.end()) {
			changed_files.insert(getFileNameFromPath(pair.first));
		}
	}
	for (const auto& pair : rhs.db) {
		auto it = db.find(pair.first);
		if (it == db.end() || it->second != pair.second) {
			result.removed[pair.first] = pair.second;
		}
		if (it == db.end()) {
			changed_files.insert(getFileNameFromPath(pair.first));
		}
	}
	return result;
}

std::ostream& operator<<(std::ostream& os, const HashDB& data) {
	for (const auto& pair : data.db) {
		os << "\"" << pair.first << "\"=0x" << std::hex << pair.second << std::oct
		   << "\n";
	}
	return os;
}

uint32_t simpleHash(const std::string& filePath) {
	std::ifstream file(filePath, std::ios::binary);
	if (!file.is_open()) return 0;
	uint32_t	   hash = 0;
	const uint32_t seed = 131;
	char		   byte;
	while (file.get(byte)) { hash = (hash * seed) + static_cast<uint8_t>(byte); }
	return hash;
}
