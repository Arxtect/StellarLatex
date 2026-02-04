#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

using cppstr  = std::string;
namespace fs  = std::filesystem;
using vecstr  = std::vector<cppstr>;
using vecpstr = std::vector<std::pair<cppstr, cppstr>>;
class FileQueryCache {
public:
	FileQueryCache(const cppstr& work_dir = "/work");
	cppstr query(const cppstr& input) const;
	void   listCache() const;
	void   buildCache();
	void   loadCache();
	void   saveCache();
	bool   empty() const;

private:
	cppstr									work_dir_;
	std::unordered_multimap<cppstr, cppstr> file_index_;
	cppstr									_query(cppstr input) const;
};
class LatexmkrcParser {
private:
	cppstr												config_file_path;
	cppstr												config_dir_path;
	std::map<cppstr, std::map<cppstr, FileQueryCache*>> paths_map;
	bool   contains_ensure_path(const cppstr& line);
	bool   parse_ensure_path_line(const cppstr& line, cppstr& var_name, cppstr& path);
	vecstr split_paths(const cppstr& path_str);
	std::pair<cppstr, bool> process_path(const cppstr& raw_path);
	cppstr					to_absolute_path(const cppstr& path) const;
	bool					directory_exists(const cppstr& path) const;

public:
	LatexmkrcParser(const cppstr& file_path);
	bool	parse();
	vecpstr query(const cppstr& input, const cppstr& var_name = "") const;
	void	print_results() const;
	// data
	const std::map<cppstr, std::map<cppstr, FileQueryCache*>>& get_results() const;
};
class SearchCache {
public:
	SearchCache();
	void  loadCache();
	void  saveCache();
	char* addCache(const cppstr& searchKey, const char* s);
	char* addCache(const cppstr& searchKey, const cppstr& s);
	std::map<cppstr, const char*>::iterator find(const cppstr& key);
	std::map<cppstr, const char*>::iterator end();

private:
	std::map<cppstr, const char*> _searchCache;
};
