#pragma once
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <kpathsea/type.h>

class CTANFileManager {
public:
	CTANFileManager() = delete;
	/**
	 * @brief build a new CTANFileManager from texlive.tlpdb
	 *
	 * @param content file content of texlive.tlpdb
	 */
	CTANFileManager(std::string_view content);
	friend std::ostream& operator<<(std::ostream& os, const CTANFileManager& m);
	/**
	 * @brief find where the query file is
	 *
	 * @param request_name query file name
	 * @param type query file type
	 * @param exist_in_fs whether the file exist in local file system
	 * @return catagory name & catagory path & relative path, catagory name "" for fail
	 */
	std::vector<std::string>
	query_file(const std::string& request_name, const kpse_file_format_type type, bool& exist_in_fs) const;
	/**
	 * @brief Get file, no matter from network or local cache
	 *
	 * @param request_name query file name
	 * @param type query file type
	 * @return null for failed else file path
	 */
	char*
	get_file(const std::string& request_name, const kpse_file_format_type type) const;
	friend std::ostream& operator<<(std::ostream& os, const CTANFileManager& manager);

private:
	/**
	 * @brief one tlpobj node contains one module information
	 *
	 */
	class tlpobjNode {
	public:
		enum class KeyType { None, Name, Depend, Docfiles, Runfiles, Srcfiles };
		std::string name;
		std::string catalogue_ctan;
		tlpobjNode() = default;
	};
	/**
	 * @brief give a correct format of the query file
	 *
	 * @param name file name, may be changed
	 * @param type file type
	 * @return nullptr for no more handle, else the suffix list
	 */
	bool handle_kpse_format(std::string& name, const kpse_file_format_type type) const;
	/**
	 * @brief create a new node from a chunk given
	 *
	 * @param chunk
	 * @return tlpobjNode
	 */
	tlpobjNode				createNode(std::string_view chunk);
	std::vector<tlpobjNode> nodes;
	// filename, pair<type@fullname, tlpobjNodeIndex>
	std::map<std::string, std::pair<std::string, size_t>>			 name_to_index;
	static std::map<kpse_file_format_type, std::vector<const char*>> format_to_suffix;
};

/**
 * @brief call js function to download a package from ctan server
 *
 * @param urlsuffix url after 'https://mirror_domain/CTAN/'
 * @param download_location location related to '/tex/pkg'
 * @return int 0 for success
 */
extern "C" int ctan_download_pkg_js(const char* urlsuffix, const char* download_location);
extern "C" char*
kpse_find_file_js(const char* name, kpse_file_format_type format, int must_exist);
