#include "filequery.hpp"
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <string>
#include <vector>
#include <w2c/config.h>

// filequerycache
FileQueryCache::FileQueryCache(const cppstr& work_dir)
	: work_dir_(fs::path(work_dir).lexically_normal().string()) {
	buildCache();
}
cppstr FileQueryCache::query(const cppstr& input) const {
	return _query(input);
}
void FileQueryCache::listCache() const {
	for (const auto& entry : file_index_) {
		std::cerr << "[WASM ENGINE] file \"" << entry.first << "\" -> \"" << entry.second
				  << "\"" << std::endl;
	}
}
void FileQueryCache::buildCache() {
	file_index_.clear();
	for (const auto& entry : fs::recursive_directory_iterator(work_dir_)) {
		if (entry.is_regular_file()) {
			cppstr		 abs_path = entry.path().lexically_normal().string();
			const cppstr filename = entry.path().filename().string();
			file_index_.emplace(filename, std::move(abs_path));
		}
	}
	for (const auto& entry : fs::recursive_directory_iterator("/output")) {
		if (entry.is_regular_file()) {
			cppstr		 abs_path = entry.path().lexically_normal().string();
			const cppstr filename = entry.path().filename().string();
			file_index_.emplace(filename, std::move(abs_path));
		}
	}
}
void FileQueryCache::loadCache() {}
void FileQueryCache::saveCache() {}
bool FileQueryCache::empty() const {
	return file_index_.empty();
}
cppstr FileQueryCache::_query(cppstr input) const {
	while (input.size() > 0 && input[0] == '/') input = input.substr(1);
	if (input.empty()) return {};
	if (input.find('/') == cppstr::npos) {
		// relative path
		auto it = file_index_.find(input);
		if (it != file_index_.end())
			return it->second;
		else
			return {};
	}
	// absolute path
	const size_t last_slash = input.rfind('/');
	const cppstr filename	= input.substr(last_slash + 1);

	const auto range = file_index_.equal_range(filename);
	for (auto it = range.first; it != range.second; ++it) {
		const cppstr& abs_path = it->second;
		if (input.size() > abs_path.size()) return {};
		size_t suffix_start = abs_path.size() - input.size();
		if ((suffix_start == 0 || abs_path[suffix_start - 1] == '/') &&
			abs_path.substr(suffix_start) == input)
			return abs_path;
	}
	// finally try it with case ignore.
	for (auto it = range.first; it != range.second; ++it) {
		const cppstr& abs_path = it->second;
		if (input.size() > abs_path.size()) return {};
		size_t suffix_start = abs_path.size() - input.size();
		if ((suffix_start == 0 || abs_path[suffix_start - 1] == '/') &&
			strcasecmp(abs_path.c_str() + suffix_start, input.c_str()) == 0)
			return abs_path;
	}
	return {};
}

// latexmkrc
bool LatexmkrcParser::contains_ensure_path(const cppstr& line) {
	// 查找注释位置
	size_t comment_pos = line.find('#');
	cppstr content = (comment_pos != cppstr::npos) ? line.substr(0, comment_pos) : line;

	// 查找 ensure_path
	return content.find("ensure_path") != cppstr::npos;
}

// 解析 ensure_path 行中的参数
bool LatexmkrcParser::parse_ensure_path_line(
	const cppstr& line,
	cppstr&		  var_name,
	cppstr&		  path) {
	if (!contains_ensure_path(line)) { return false; }
	size_t start_pos = line.find('(');
	if (start_pos == cppstr::npos) { return false; }
	size_t end_pos = line.rfind(')');
	if (end_pos == cppstr::npos || end_pos <= start_pos) { return false; }
	cppstr content			 = line.substr(start_pos + 1, end_pos - start_pos - 1);
	size_t first_quote_start = content.find_first_of("'\"");
	if (first_quote_start == cppstr::npos) { return false; }
	char   quote_char	   = content[first_quote_start];
	size_t first_quote_end = content.find(quote_char, first_quote_start + 1);
	if (first_quote_end == cppstr::npos) { return false; }
	var_name =
		content.substr(first_quote_start + 1, first_quote_end - first_quote_start - 1);
	size_t second_quote_start = content.find_first_of("'\"", first_quote_end + 1);
	if (second_quote_start == cppstr::npos) { return false; }
	quote_char				= content[second_quote_start];
	size_t second_quote_end = content.find(quote_char, second_quote_start + 1);
	if (second_quote_end == cppstr::npos) { return false; }
	path =
		content.substr(second_quote_start + 1, second_quote_end - second_quote_start - 1);

	return true;
}

// 分割路径字符串，处理包含多个路径的情况
vecstr LatexmkrcParser::split_paths(const cppstr& path_str) {
	vecstr paths;

	// 按 : 分割路径
	size_t start = 0;
	size_t pos	 = 0;
	while ((pos = path_str.find(':', start)) != cppstr::npos) {
		paths.push_back(path_str.substr(start, pos - start));
		start = pos + 1;
	}
	// 添加最后一个路径
	paths.push_back(path_str.substr(start));

	return paths;
}

// 判断路径是否递归并清理路径
std::pair<cppstr, bool> LatexmkrcParser::process_path(const cppstr& raw_path) {
	cppstr path		 = raw_path;
	bool   recursive = false;

	// 检查是否以 // 结尾（递归）
	if (path.length() >= 2 && path.substr(path.length() - 2) == "//") {
		recursive = true;
		path	  = path.substr(0, path.length() - 2);
	}
	// 检查是否以单个 / 结尾
	else if (path.length() >= 1 && path.back() == '/') {
		path = path.substr(0, path.length() - 1);
	}

	// 忽略纯 / 或 // 路径
	if (path.empty()) { return std::make_pair("", false); }

	return std::make_pair(path, recursive);
}

// 将相对路径转换为绝对路径
cppstr LatexmkrcParser::to_absolute_path(const cppstr& path) const {
	// 如果已经是绝对路径，直接返回
	if (path.length() > 0 && path[0] == '/') { return path; }

	// 拼接配置文件所在目录和相对路径
	cppstr absolute_path = config_dir_path;
	if (absolute_path.back() != '/') { absolute_path += "/"; }
	absolute_path += path;
	return absolute_path;
}

// 检查目录是否存在
bool LatexmkrcParser::directory_exists(const cppstr& path) const {
	return fs::exists(path) && fs::is_directory(path);
}
LatexmkrcParser::LatexmkrcParser(const cppstr& file_path) : config_file_path(file_path) {
	if (fs::exists(file_path) == false) return;
	// 获取配置文件所在目录的绝对路径
	fs::path absolute_path = fs::absolute(file_path);
	config_dir_path		   = absolute_path.parent_path().string();
	// 确保目录路径以 / 结尾
	if (config_dir_path.back() != '/') { config_dir_path += "/"; }
	parse();
}

// 解析配置文件
bool LatexmkrcParser::parse() {
	std::ifstream file(config_file_path);
	if (!file.is_open()) {
		std::cerr << "无法打开配置文件: " << config_file_path << std::endl;
		return false;
	}

	cppstr line;
	while (std::getline(file, line)) {
		cppstr var_name, raw_path;

		// 解析 ensure_path 行
		if (parse_ensure_path_line(line, var_name, raw_path)) {
			// 处理可能包含多个路径的字符串
			vecstr path_list = split_paths(raw_path);

			for (const cppstr& single_path : path_list) {
				auto processed = process_path(single_path);
				if (!processed.first.empty()) {	 // 忽略空路径
					cppstr absolute_path = to_absolute_path(processed.first);
					// 只有目录存在时才存储
					if (directory_exists(absolute_path)) {
						if (processed.second == true) {
							paths_map[var_name][absolute_path] =
								new FileQueryCache(absolute_path);
						}
						else { paths_map[var_name][absolute_path] = nullptr; }
					}
				}
			}
		}
	}

	file.close();
	return true;
}
vecpstr LatexmkrcParser::query(const cppstr& input, const cppstr& var_name) const {
	vecpstr results;
	for (auto& [_var_name, vdb] : paths_map) {
		if (!var_name.empty() && var_name != _var_name) { continue; }
		for (auto& [path, cache] : vdb) {
			if (cache != nullptr) {
				cppstr query_result = cache->query(input);
				if (!query_result.empty()) {
					results.push_back({var_name, query_result});
				}
			}
			else {
				if (fs::exists(path) && fs::is_directory(path)) {
					cppstr query_result = path;
					if (query_result.back() != '/') { query_result += "/"; }
					query_result += input;
					if (fs::exists(query_result))
						results.push_back({var_name, query_result});
				}
			}
		}
	}
	return results;
}
// 打印结果
void LatexmkrcParser::print_results() const {
	std::cout << "路径配置解析结果:" << std::endl;
	std::cout << "========================" << std::endl;

	for (const auto& entry : paths_map) {
		std::cout << "变量 '" << entry.first << "':" << std::endl;

		// 分别显示递归和非递归路径
		vecstr recursive_paths;
		vecstr non_recursive_paths;

		for (const auto& path_info : entry.second) {
			if (path_info.second) { recursive_paths.push_back(path_info.first); }
			else { non_recursive_paths.push_back(path_info.first); }
		}

		if (!recursive_paths.empty()) {
			std::cout << "  递归路径 (包含所有子目录):" << std::endl;
			for (const auto& path : recursive_paths) {
				std::cout << "    ├── " << path << std::endl;
			}
		}

		if (!non_recursive_paths.empty()) {
			std::cout << "  非递归路径 (仅当前目录):" << std::endl;
			for (const auto& path : non_recursive_paths) {
				std::cout << "    ├── " << path << std::endl;
			}
		}

		std::cout << "------------------------" << std::endl;
	}
}

const std::map<cppstr, std::map<cppstr, FileQueryCache*>>&
LatexmkrcParser::get_results() const {
	return paths_map;
}
// searchCache

SearchCache::SearchCache() {
	loadCache();
}
void SearchCache::loadCache() {
	std::ifstream file("/tmp/cache.db");
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			// 解析行格式: key\x1Fvalue
			size_t pos = line.find('\x1F');
			if (pos != std::string::npos) {
				std::string key	  = line.substr(0, pos);
				std::string value = line.substr(pos + 1);
				// 处理空值情况
				if (value.empty()) { _searchCache[key] = nullptr; }
				else { _searchCache[key] = strdup(value.c_str()); }
			}
		}
		file.close();
	}
}
void SearchCache::saveCache() {
	std::ofstream file("/tmp/cache.db");
	if (file.is_open()) {
		for (const auto& entry : _searchCache) {
			// 只保存非/work和/output开头的值，nullptr值也保存
			if (entry.second == nullptr) { file << entry.first << '\x1F' << '\n'; }
			else if (
				strncmp(entry.second, "/work", 5) != 0 &&
				strncmp(entry.second, "/output", 7) != 0) {
				file << entry.first << '\x1F' << entry.second << '\n';
			}
		}
		file.close();
	}
}
char* SearchCache::addCache(const cppstr& searchKey, const char* s) {
	if (s == nullptr) {
		_searchCache[searchKey] = nullptr;
		saveCache();
		return nullptr;
	}
	if (auto it = _searchCache.find(searchKey);
		it != _searchCache.end() && it->second != nullptr) {
		free(const_cast<char*>(it->second));
	}
	_searchCache[searchKey] = strdup(s);

	// 如果值不是以/work或/output开头，则保存缓存
	if (strncmp(s, "/work", 5) != 0 && strncmp(s, "/output", 7) != 0) { saveCache(); }

	return strdup(s);
}
char* SearchCache::addCache(const cppstr& searchKey, const cppstr& s) {
	return addCache(searchKey, s.c_str());
}
std::map<cppstr, const char*>::iterator SearchCache::find(const cppstr& key) {
	return _searchCache.find(key);
}
std::map<cppstr, const char*>::iterator SearchCache::end() {
	return _searchCache.end();
}
