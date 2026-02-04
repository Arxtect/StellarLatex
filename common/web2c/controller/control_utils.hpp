#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

using cppstr = std::string;
using vecstr = std::vector<cppstr>;
vecstr getAllTexFiles(const cppstr& mainFile);
bool   containsDynamicCommandsInProject(const cppstr& mainFile);
bool   containsDynamicCommandsInProject(const vecstr& mainFile);
bool   containsDateCommandsInProject(const cppstr& mainFile);
bool   containsDateCommandsInProject(const vecstr& mainFile);

class LatexDynamicDetector {
public:
	static bool containsDynamicCommands(const cppstr& filePath);
	static bool containsDateCommands(const cppstr& filePath);

private:
	static bool					  checkLineForDynamicCommands(const cppstr& line);
	static bool					  checkLineForDateCommands(const cppstr& line);
	static const std::set<cppstr> dynamicCommands, dateCommands;
};

class HashDB {
public:
	using hashList = std::map<cppstr, uint32_t>;
	class hashDiffer {
	public:
		hashList added;
		hashList removed;
		static std::set<cppstr> fileName;
		// check if file changed
		bool is_any_changed() const;
		bool is_tex_changed() const;
		bool is_bib_changed() const;
		bool is_idx_changed() const;
		bool is_this_changed(const vecstr& fileList) const;
		friend std::ostream& operator<<(std::ostream& os, const hashDiffer& data);
	private:
		bool hasFileWithExt(const hashList& list, const char* extension) const;
	};
	void	   buildDB();
	void	   loadDB();
	void	   saveDB();
	hashDiffer operator-(const HashDB& rhs);
	friend std::ostream& operator<<(std::ostream& os, const HashDB& data);

private:
	hashList db;
};
uint32_t simpleHash(const std::string& filePath);
