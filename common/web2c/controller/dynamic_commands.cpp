#include "control_utils.hpp"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

// 初始化动态命令集合
const std::set<cppstr> LatexDynamicDetector::dynamicCommands = {
	"\\time",
	"\\DTMnow",
	"\\DTMcurrenttime",
	"\\currenthour",
	"\\currentminute",
	"\\currentsecond",
	"\\thistime",
	"\\pgfmathrandominteger",
	"\\pgfmathrandomfloat",
	"\\rand",
	"\\chgrandparent"};
const std::set<cppstr> LatexDynamicDetector::dateCommands = {
	"\\today",
	"\\year",
	"\\month",
	"\\day",
	"\\DTMtoday"};

static cppstr removeComments(const cppstr& line) {
	size_t commentPos = line.find('%');
	if (commentPos != cppstr::npos) { return line.substr(0, commentPos); }
	return line;
}
static vecstr extractIncludedFiles(const cppstr& filePath) {
	vecstr		  includedFiles;
	std::ifstream file(filePath);

	if (!file.is_open()) { return includedFiles; }

	cppstr line;
	// 修改正则表达式以更好地处理各种空格情况
	std::regex	includePattern(R"(\\(?:include|input)(?:\s*)\{([^}]+)\})");
	std::smatch matches;

	// 获取当前文件的绝对路径和父目录
	std::filesystem::path absoluteFilePath = std::filesystem::absolute(filePath);
	std::filesystem::path parentDir		   = absoluteFilePath.parent_path();

	while (std::getline(file, line)) {
		line = removeComments(line);
		if (std::regex_search(line, matches, includePattern)) {
			if (matches.size() > 1) {
				cppstr fileName = matches[1].str();
				fileName.erase(0, fileName.find_first_not_of(" \t"));
				fileName.erase(fileName.find_last_not_of(" \t") + 1);
				if (fileName.find(".tex") == cppstr::npos) { fileName += ".tex"; }
				std::filesystem::path fullPath = parentDir / fileName;
				if (std::filesystem::exists(fullPath)) {
					// 转换为绝对路径
					std::filesystem::path absolutePath =
						std::filesystem::absolute(fullPath);
					includedFiles.push_back(absolutePath.string());
				}
			}
		}
	}

	file.close();
	return includedFiles;
}

vecstr getAllTexFiles(const cppstr& mainFile) {
	vecstr			 files;
	std::set<cppstr> visited;

	// 将主文件路径转换为绝对路径
	std::filesystem::path absoluteMainFile = std::filesystem::absolute(mainFile);
	// 使用栈结构实现深度优先搜索
	vecstr stack = {absoluteMainFile.string()};

	while (!stack.empty()) {
		cppstr currentFile = stack.back();	// 从栈顶取出元素
		stack.pop_back();					// 删除栈顶元素

		if (visited.find(currentFile) != visited.end()) { continue; }

		visited.insert(currentFile);
		files.push_back(currentFile);

		// 获取当前文件包含的其他文件
		vecstr includedFiles = extractIncludedFiles(currentFile);
		// 将新发现的文件压入栈顶
		stack.insert(stack.end(), includedFiles.begin(), includedFiles.end());
	}

	return files;
}

bool LatexDynamicDetector::containsDynamicCommands(const cppstr& filePath) {
	std::ifstream file(filePath);

	if (!file.is_open()) { return false; }

	cppstr line;
	while (std::getline(file, line)) {
		// 移除注释
		line = removeComments(line);

		// 检查行中是否包含动态命令
		if (checkLineForDynamicCommands(line)) {
			file.close();
			return true;
		}
	}

	file.close();
	return false;
}
bool LatexDynamicDetector::containsDateCommands(const cppstr& filePath) {
	std::ifstream file(filePath);

	if (!file.is_open()) { return false; }

	cppstr line;
	while (std::getline(file, line)) {
		// 移除注释
		line = removeComments(line);

		// 检查行中是否包含动态命令
		if (checkLineForDateCommands(line)) {
			file.close();
			return true;
		}
	}

	file.close();
	return false;
}

bool LatexDynamicDetector::checkLineForDynamicCommands(const cppstr& line) {
	// 对每个动态命令进行检查
	for (const cppstr& command : dynamicCommands) {
		size_t pos = line.find(command);
		while (pos != cppstr::npos) {
			// 检查命令后面是否跟着字母或数字，如果是，则可能是其他命令的一部分
			size_t endPos = pos + command.length();
			if (endPos < line.length()) {
				char nextChar = line[endPos];
				// 如果下一个字符是字母或数字，则这不是我们要找的命令
				if (std::isalnum(nextChar)) {
					pos = line.find(command, endPos);
					continue;
				}
			}

			// 检查命令前面是否是合法的命令分隔符
			if (pos > 0) {
				char prevChar = line[pos - 1];
				if (std::isalnum(prevChar)) {
					pos = line.find(command, endPos);
					continue;
				}
			}

			return true;
		}
	}

	return false;
}
bool LatexDynamicDetector::checkLineForDateCommands(const cppstr& line) {
	// 对每个动态命令进行检查
	for (const cppstr& command : dateCommands) {
		size_t pos = line.find(command);
		while (pos != cppstr::npos) {
			// 检查命令后面是否跟着字母或数字，如果是，则可能是其他命令的一部分
			size_t endPos = pos + command.length();
			if (endPos < line.length()) {
				char nextChar = line[endPos];
				// 如果下一个字符是字母或数字，则这不是我们要找的命令
				if (std::isalnum(nextChar)) {
					pos = line.find(command, endPos);
					continue;
				}
			}

			// 检查命令前面是否是合法的命令分隔符
			if (pos > 0) {
				char prevChar = line[pos - 1];
				if (std::isalnum(prevChar)) {
					pos = line.find(command, endPos);
					continue;
				}
			}

			return true;
		}
	}

	return false;
}
bool containsDynamicCommandsInProject(const cppstr& mainFile) {
	vecstr files = getAllTexFiles(mainFile);
	return std::any_of(files.begin(), files.end(), [](const cppstr& file) {
		return LatexDynamicDetector::containsDynamicCommands(file);
	});
}
bool containsDateCommandsInProject(const cppstr& mainFile) {
	vecstr files = getAllTexFiles(mainFile);
	return std::any_of(files.begin(), files.end(), [](const cppstr& file) {
		return LatexDynamicDetector::containsDateCommands(file);
	});
}

bool containsDynamicCommandsInProject(const vecstr& files) {
	return std::any_of(files.begin(), files.end(), [](const cppstr& file) {
		return LatexDynamicDetector::containsDynamicCommands(file);
	});
}
bool containsDateCommandsInProject(const vecstr& files) {
	return std::any_of(files.begin(), files.end(), [](const cppstr& file) {
		return LatexDynamicDetector::containsDateCommands(file);
	});
}
