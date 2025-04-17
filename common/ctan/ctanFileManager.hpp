#pragma once
#include <cstring>
#include <map>
#include <string>
#include <vector>

typedef enum {
	kpse_gf_format,
	kpse_pk_format,
	kpse_any_glyph_format, /* ``any'' meaning gf or pk */
	kpse_tfm_format,
	kpse_afm_format,
	kpse_base_format,
	kpse_bib_format,
	kpse_bst_format,
	kpse_cnf_format,
	kpse_db_format,
	kpse_fmt_format,
	kpse_fontmap_format,
	kpse_mem_format,
	kpse_mf_format,
	kpse_mfpool_format,
	kpse_mft_format,
	kpse_mp_format,
	kpse_mppool_format,
	kpse_mpsupport_format,
	kpse_ocp_format,
	kpse_ofm_format,
	kpse_opl_format,
	kpse_otp_format,
	kpse_ovf_format,
	kpse_ovp_format,
	kpse_pict_format,
	kpse_tex_format,
	kpse_texdoc_format,
	kpse_texpool_format,
	kpse_texsource_format,
	kpse_tex_ps_header_format,
	kpse_troff_font_format,
	kpse_type1_format,
	kpse_vf_format,
	kpse_dvips_config_format,
	kpse_ist_format,
	kpse_truetype_format,
	kpse_type42_format,
	kpse_web2c_format,
	kpse_program_text_format,
	kpse_program_binary_format,
	kpse_miscfonts_format,
	kpse_web_format,
	kpse_cweb_format,
	kpse_enc_format,
	kpse_cmap_format,
	kpse_sfd_format,
	kpse_opentype_format,
	kpse_pdftex_config_format,
	kpse_lig_format,
	kpse_texmfscripts_format,
	kpse_lua_format,
	kpse_fea_format,
	kpse_cid_format,
	kpse_mlbib_format,
	kpse_mlbst_format,
	kpse_clua_format,
	kpse_ris_format,
	kpse_bltxml_format,
	kpse_last_format /* one past last index */
} kpse_file_format_type;

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
		enum class KeyType { None, Name, Depend, Runfiles, Srcfiles };
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
