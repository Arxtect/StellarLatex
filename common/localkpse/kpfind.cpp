#include "type.h"
#include <algorithm>
#include <cctype>
#include <cstring>
#include <ctan/ctanInterface.h>
#include <ctan/extractFile.hpp>
#include <dirent.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <unistd.h>
using cppstr = std::string;
namespace fs = std::filesystem;
extern "C" char* kpse_find_pk_js(const char* passed_fontname, unsigned int dpi);
class FileQueryCache {
public:
	explicit FileQueryCache(const cppstr& work_dir = "/work")
		: work_dir_(fs::path(work_dir).lexically_normal().string()) {
		buildCache();
		// listCache();
	}
	cppstr query(const cppstr& input) const {
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
	void listCache() {
		for (const auto& entry : file_index_) {
			std::cerr << entry.first << " -> " << entry.second << std::endl;
		}
	}
	void buildCache() {
		file_index_.clear();
		for (const auto& entry : fs::recursive_directory_iterator(work_dir_)) {
			if (entry.is_regular_file()) {
				cppstr		 abs_path = entry.path().lexically_normal().string();
				const cppstr filename = entry.path().filename().string();
				file_index_.emplace(filename, std::move(abs_path));
			}
		}
	}

private:
	cppstr									work_dir_;
	std::unordered_multimap<cppstr, cppstr> file_index_;
};
static std::pair<cppstr, bool>
fixExtension(const cppstr& filename, kpse_file_format_type format) {
	// TODO: multi fixext required
	auto fixExt = [&filename](const char* ext) -> std::pair<cppstr, bool> {
		size_t suffixLen = strlen(ext);
		if (strcasecmp(filename.c_str() + filename.size() - suffixLen, ext) == 0)
			return {cppstr(), false};
		return {filename + ext, true};
	};
	switch (format) {
		case kpse_gf_format: return fixExt(".gf");
		case kpse_pk_format: return fixExt(".pk");
		case kpse_tfm_format: return fixExt(".tfm");
		case kpse_afm_format: return fixExt(".afm");
		case kpse_base_format: return fixExt(".base");
		case kpse_bib_format: return fixExt(".bib");
		case kpse_bst_format: return fixExt(".bst");
		case kpse_fontmap_format: return fixExt(".map");
		case kpse_mem_format: return fixExt(".mem");
		case kpse_mf_format: return fixExt(".mf");
		case kpse_mft_format: return fixExt(".mft");
		case kpse_mfpool_format: return fixExt(".pool");
		case kpse_mp_format: return fixExt(".mp");
		case kpse_mppool_format: return fixExt(".pool");
		case kpse_ocp_format: return fixExt(".ocp");
		case kpse_ofm_format: return fixExt(".ofm");
		case kpse_opl_format: return fixExt(".opl");
		case kpse_otp_format: return fixExt(".otp");
		case kpse_ovf_format: return fixExt(".ovf");
		case kpse_ovp_format: return fixExt(".ovp");
		case kpse_pict_format: return fixExt(".esp");
		case kpse_tex_format: return fixExt(".tex");
		case kpse_texpool_format: return fixExt(".pool");
		case kpse_texsource_format: return fixExt(".dtx");
		case kpse_type1_format: return fixExt(".pfa");
		case kpse_vf_format: return fixExt(".vf");
		case kpse_ist_format: return fixExt(".ist");
		case kpse_truetype_format: return fixExt(".ttf");
		case kpse_type42_format: return fixExt(".t42");
		case kpse_miscfonts_format: return {cppstr(), false};
		case kpse_enc_format: return fixExt(".enc");
		case kpse_cmap_format: return fixExt("cmap");
		case kpse_sfd_format: return fixExt(".sfd");
		case kpse_opentype_format: return fixExt(".otf");
		case kpse_pdftex_config_format: return fixExt(".cfg");
		case kpse_lig_format: return fixExt(".lig");
		case kpse_texmfscripts_format: return {cppstr(), false};
		case kpse_fea_format: return fixExt(".fea");
		case kpse_cid_format: return fixExt(".cid");
		case kpse_mlbib_format: return fixExt(".mlbib");
		case kpse_mlbst_format: return fixExt(".mlbst");
		case kpse_ris_format: return fixExt(".ris");
		case kpse_bltxml_format: return fixExt(".bltxml");
		case kpse_fmt_format: return fixExt(".fmt");
		default: return {cppstr(), false};
	}
}
extern char	  main_entry_file[512];
static cppstr caseExists(const cppstr& filename) {
	if (filename.empty()) { return {}; }
	if (std::filesystem::exists(filename)) return filename;
	if (std::filesystem::exists("/tex/" + filename)) return "/tex/" + filename;
	static auto	  mainWorkDir	 = fs::absolute(fs::path(main_entry_file)).parent_path();
	static cppstr mainWorkDirStr = mainWorkDir.string();
	static bool	  mainIsCur		 = (mainWorkDir == fs::current_path());
	size_t		  last_slash	 = filename.find_last_of('/');
	cppstr		  dir_path, base_name;
	if (last_slash == cppstr::npos) {
		dir_path  = ".";
		base_name = filename;
	}
	else {
		dir_path  = filename.substr(0, last_slash);
		base_name = filename.substr(last_slash + 1);
		if (base_name.empty()) { return {}; }
	}
	if (DIR* dir = opendir(dir_path.c_str()); dir != nullptr) {
		struct dirent* entry;
		while ((entry = readdir(dir)) != nullptr) {
			if (strcasecmp(entry->d_name, base_name.c_str()) == 0)
				return dir_path + '/' + entry->d_name;
		}
		closedir(dir);
	}
	if (dir_path == ".") {
		if (DIR* dir = opendir("/tex"); dir != nullptr) {
			struct dirent* entry;
			while ((entry = readdir(dir)) != nullptr) {
				if (strcasecmp(entry->d_name, base_name.c_str()) == 0)
					return cppstr("/tex/") + entry->d_name;
			}
			closedir(dir);
		}
		if (mainIsCur) return {};
		if (DIR* dir = opendir(mainWorkDirStr.c_str()); dir != nullptr) {
			struct dirent* entry;
			while ((entry = readdir(dir)) != nullptr) {
				if (strcasecmp(entry->d_name, base_name.c_str()) == 0)
					return mainWorkDirStr + '/' + entry->d_name;
			}
			closedir(dir);
		}
	}
	return {};
}
extern "C" char*
kpse_find_file(const char* _name, kpse_file_format_type format, bool must_exist) {
	static FileQueryCache				 workCache;
	static std::map<cppstr, const char*> searchCache;
	if (_name == nullptr) return nullptr;
	cppstr name(_name);
	if (name.empty()) return nullptr;
	const cppstr searchKey = name + '+' + std::to_string(format);
	// make return value and make cache
	auto makestr = [&searchKey](const char* value) -> char* {
		if (value == nullptr) {
			searchCache[searchKey] = nullptr;
			return nullptr;
		}
		if (auto it = searchCache.find(searchKey);
			it != searchCache.end() && it->second != nullptr) {
			free(const_cast<char*>(it->second));
		}
		searchCache[searchKey] = strdup(value);
		return strdup(value);
	};
	if (auto it = searchCache.find(searchKey); it != searchCache.end()) {
		if (it->second != nullptr) return strdup(it->second);
		// nullptr, check if exists in main working path
		if (name.find('/') != cppstr::npos) return nullptr;
		if (auto path = caseExists(name); path.size() != 0) return makestr(path.c_str());
		return nullptr;
	}
	cppstr no_suffix_path;
	// check if there is a suffix
	auto has_dot_in_filename = [](const cppstr& path) {
		if (path.empty()) return false;
		size_t last_slash = path.find_last_of('/');
		size_t start	  = (last_slash == cppstr::npos) ? 0 : last_slash + 1;
		return path.find('.', start) != cppstr::npos;
	};
	// try with name
	if (auto ci_match = caseExists(name); !ci_match.empty()) {
		if (has_dot_in_filename(ci_match)) return makestr(ci_match.c_str());
		if (no_suffix_path.empty()) no_suffix_path = std::move(ci_match);
	}
	// try to add suffix
	const auto [nameFixExt, extChanged] = fixExtension(name, format);
	if (extChanged)
		if (auto ci_match = caseExists(nameFixExt); !ci_match.empty()) {
			if (has_dot_in_filename(ci_match)) return makestr(ci_match.c_str());
			if (no_suffix_path.empty()) no_suffix_path = std::move(ci_match);
		}
	// try to find in remote
	if (char* remote = ctan_get_file(name.c_str(), format); remote != nullptr)
		return makestr(remote);
	// try to find in local project(not root)
	if (const cppstr workQuert1 = workCache.query(name); workQuert1.size() != 0) {
		if (has_dot_in_filename(workQuert1)) return makestr(workQuert1.c_str());
		if (no_suffix_path.empty()) no_suffix_path = std::move(workQuert1);
	}
	// try to find in local project with more than(not root)
	if (extChanged)
		if (const cppstr workQuert2 = workCache.query(nameFixExt);
			workQuert2.size() != 0) {
			if (has_dot_in_filename(workQuert2)) return makestr(workQuert2.c_str());
			if (no_suffix_path.empty()) no_suffix_path = std::move(workQuert2);
		}
	// finally, we use no suffix result
	if (no_suffix_path.size() != 0) return makestr(no_suffix_path.c_str());
	return makestr(nullptr);
}

// extern "C" char*
// kpse_find_file(const char* _name, kpse_file_format_type format, bool must_exist) {
// 	char* res = kpse_find_file_warp(_name, format, must_exist);
// 	if (res == nullptr)
// 		std::cerr << "[DEBUG] kpse_find_file(name=\"" << _name << "\", format=" << format
// 				  << ") = nullptr" << std::endl;
// 	else
// 		std::cerr << "[DEBUG] kpse_find_file(name=\"" << _name << "\", format=" << format
// 				  << ") = " << res << std::endl;
// 	return res;
// }
extern "C" char* kpse_find_pk(const char* fontname, unsigned int dpi) {
	if (fontname == nullptr) return nullptr;
	cppstr base_name(fontname);
	base_name += ".";
	base_name += std::to_string(dpi);
	base_name += ".pk";
	if (auto ci_match = caseExists(base_name); !ci_match.empty())
		return strdup(ci_match.c_str());
	// net search
	return kpse_find_pk_js(fontname, dpi);
}
