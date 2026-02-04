#include "filequery.hpp"
#include "type.h"
#include <algorithm>
#include <cctype>
#include <cstring>
#include <ctan/ctanFileManager.hpp>
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
#include <set>
#include <string>
#include <unistd.h>
#include <w2c/config.h>
#define DEBUG_HEAD std::cerr << "[DEBUG] " << __FILE__ << "@" << __LINE__
using cppstr = std::string;
namespace fs = std::filesystem;
extern "C" char* kpse_find_pk_js(const char* passed_fontname, unsigned int dpi);
cppstr			 getFileNameFromPath(const cppstr& path);
extern cppstr	 main_entry_file;
extern bool		 bbl_required;
std::set<cppstr> changed_files;
#ifdef XETEXWASM
std::set<cppstr> web_301 = {
	"20@EBGaramond-BoldItalic-lf-t1--base.ofm",
	"20@EBGaramond-BoldItalic-lf-t1.ofm",
	"20@EBGaramond-Italic-lf-t1--base.ofm",
	"20@EBGaramond-Italic-lf-t1.ofm",
	"20@EBGaramond-Regular-lf-ot1.ofm",
	"20@EBGaramond-Regular-lf-sc-t1--base.ofm",
	"20@EBGaramond-Regular-lf-sc-t1.ofm",
	"20@EBGaramond-Regular-lf-t1--base.ofm",
	"20@EBGaramond-Regular-lf-t1.ofm",
	"20@EBGaramond-Regular-lf-ts1--base.ofm",
	"20@EBGaramond-Regular-lf-ts1.ofm",
	"20@LibertineMathMI.ofm",
	"20@LibertineMathMI7.ofm",
	"20@LibertineMathRM.ofm",
	"20@MinLibReg-ot1.ofm",
	"20@NewTXBMI.ofm",
	"20@NewTXBMI5.ofm",
	"20@NewTXMI.ofm",
	"20@NewTXMI5.ofm",
	"20@NewTXMI7.ofm",
	"20@SourceSansPro-Black-tlf-t1--base.ofm",
	"20@SourceSansPro-Black-tlf-t1.ofm",
	"20@SourceSansPro-Bold-tlf-t1--base.ofm",
	"20@SourceSansPro-Bold-tlf-t1.ofm",
	"20@SourceSansPro-It-tlf-t1--base.ofm",
	"20@SourceSansPro-It-tlf-t1.ofm",
	"20@SourceSansPro-Light-tlf-t1--base.ofm",
	"20@SourceSansPro-Light-tlf-t1.ofm",
	"20@SourceSansPro-Regular-tlf-t1--base.ofm",
	"20@SourceSansPro-Regular-tlf-t1.ofm",
	"20@SourceSansPro-Regular-tlf-ts1--base.ofm",
	"20@SourceSansPro-Regular-tlf-ts1.ofm",
	"20@cmbx10.ofm",
	"20@cmbx7.ofm",
	"20@cmex10.ofm",
	"20@cmmi10.ofm",
	"20@cmmi12.ofm",
	"20@cmmi7.ofm",
	"20@cmmi8.ofm",
	"20@cmmib10.ofm",
	"20@cmr10.ofm",
	"20@cmr12.ofm",
	"20@cmr6.ofm",
	"20@cmr7.ofm",
	"20@cmr8.ofm",
	"20@cmsy10.ofm",
	"20@cmsy7.ofm",
	"20@cmsy8.ofm",
	"20@ec-lmtt10.ofm",
	"20@eurm10.ofm",
	"20@eurm7.ofm",
	"20@lcircle10.ofm",
	"20@lmex10.ofm",
	"20@lmmi12.ofm",
	"20@lmmi8.ofm",
	"20@lmmi9.ofm",
	"20@lmsy10.ofm",
	"20@lmsy8.ofm",
	"20@msam10.ofm",
	"20@msbm10.ofm",
	"20@ntx-Bold-tlf-ot1.ofm",
	"20@ntx-Bold-tlf-ot1r.ofm",
	"20@ntx-Regular-tlf-ot1.ofm",
	"20@ntx-Regular-tlf-ot1r.ofm",
	"20@ntxbmi.ofm",
	"20@ntxbmi5.ofm",
	"20@ntxexx.ofm",
	"20@ntxmi.ofm",
	"20@ntxmi5.ofm",
	"20@ntxmi7.ofm",
	"20@ntxmia.ofm",
	"20@ntxsy.ofm",
	"20@ntxsy5.ofm",
	"20@ntxsy7.ofm",
	"20@ntxsym.ofm",
	"20@nxlmi.ofm",
	"20@nxlmi7.ofm",
	"20@nxlmia.ofm",
	"20@pzdr.ofm",
	"20@rm-lmr12.ofm",
	"20@rm-lmr8.ofm",
	"20@stxscr.ofm",
	"20@txbmiaX.ofm",
	"20@txex-bar.ofm",
	"20@txexs.ofm",
	"20@txmiaSTbb.ofm",
	"20@txmiaX.ofm",
	"20@txsys.ofm",
	"20@zeurm10.ofm",
	"20@zeurm7.ofm",
	"26@Arial.fontspec",
	"26@FandolFang-Regular.fontspec",
	"26@FandolFang.fontspec",
	"26@FandolHei-Bold.fontspec",
	"26@FandolHei-Regular.fontspec",
	"26@FandolHei.fontspec",
	"26@FandolKai-Regular.fontspec",
	"26@FandolKai.fontspec",
	"26@FandolSong-Bold.fontspec",
	"26@FandolSong-Regular.fontspec",
	"26@FandolSong.fontspec",
	"26@Inconsolatazi4-Bold.fontspec",
	"26@Inconsolatazi4-Regular.fontspec",
	"26@KaiTi.fontspec",
	"26@LinBiolinum.fontspec",
	"26@LinBiolinum_K.fontspec",
	"26@LinBiolinum_R.fontspec",
	"26@LinBiolinum_RB.fontspec",
	"26@LinBiolinum_RBO.fontspec",
	"26@LinBiolinum_RI.fontspec",
	"26@LinLibertine.fontspec",
	"26@LinLibertine_DR.fontspec",
	"26@LinLibertine_I.fontspec",
	"26@LinLibertine_M.fontspec",
	"26@LinLibertine_MB.fontspec",
	"26@LinLibertine_MBO.fontspec",
	"26@LinLibertine_MO.fontspec",
	"26@LinLibertine_R.fontspec",
	"26@LinLibertine_RB.fontspec",
	"26@LinLibertine_RBI.fontspec",
	"26@LinLibertine_RI.fontspec",
	"26@LinLibertine_RZ.fontspec",
	"26@LinLibertine_RZI.fontspec",
	"26@SimSun.fontspec",
	"26@SourceSansPro-Black.fontspec",
	"26@SourceSansPro-BlackIt.fontspec",
	"26@SourceSansPro-Bold.fontspec",
	"26@SourceSansPro-BoldIt.fontspec",
	"26@SourceSansPro-ExtraLight.fontspec",
	"26@SourceSansPro-ExtraLightIt.fontspec",
	"26@SourceSansPro-Light.fontspec",
	"26@SourceSansPro-LightIt.fontspec",
	"26@SourceSansPro-Regular.fontspec",
	"26@SourceSansPro-RegularIt.fontspec",
	"26@SourceSansPro-Semibold.fontspec",
	"26@SourceSansPro-SemiboldIt.fontspec",
	"26@SourceSansPro.fontspec",
	"26@TUfbb-TLF.fd",
	"26@TUpcr.fd",
	"26@TUphv.fd",
	"26@TUptm.fd",
	"26@TeXGyreTermesX-Bold.fontspec",
	"26@TeXGyreTermesX-BoldItalic.fontspec",
	"26@TeXGyreTermesX-BoldSlanted.fontspec",
	"26@TeXGyreTermesX-Italic.fontspec",
	"26@TeXGyreTermesX-Regular.fontspec",
	"26@TeXGyreTermesX-Slanted.fontspec",
	"26@TimesNewRoman.fontspec",
	"26@acmart-preload-hook.tex",
	"26@amsart.cfg",
	"26@babel-xelatex.cfg",
	"26@biblatex-dm.cfg",
	"26@block.tss",
	"26@bookmark.cfg",
	"26@chicago-authordate-trad.dbx",
	"26@chicago-authordate16.dbx",
	"26@cleveref.cfg",
	"26@cup-logo-new",
	"26@cup-logo-new.bb",
	"26@example-image-16x10.bb",
	"26@fancyvrb.cfg",
	"26@fzhei.fontspec",
	"26@fzsong.fontspec",
	"26@gb7714-2015.dbx",
	"26@geometry.cfg",
	"26@gettitlestring.cfg",
	"26@hyperref.cfg",
	"26@l3bitset.sty",
	"26@l3graphics.sty",
	"26@l3opacity.sty",
	"26@lstlang0.sty",
	"26@lstlocal.cfg",
	"26@lstmisc0.sty",
	"26@mt-LinBiolinum.cfg",
	"26@mt-LinLibertine.cfg",
	"26@mt-SourceSansPro.cfg",
	"26@mt-cme.cfg",
	"26@mt-cmex.cfg",
	"26@mt-cmm.cfg",
	"26@mt-cmsy.cfg",
	"26@mt-fbb-TLF.cfg",
	"26@mt-fbb.cfg",
	"26@mt-inconsolat.cfg",
	"26@mt-inconsolata.cfg",
	"26@mt-lmr.cfg",
	"26@mt-lmtt.cfg",
	"26@mt-minlibertine.cfg",
	"26@mt-ntxex.cfg",
	"26@mt-ntxexa.cfg",
	"26@mt-ntxexx.cfg",
	"26@mt-ntxmi.cfg",
	"26@mt-ntxmia.cfg",
	"26@mt-ntxsy.cfg",
	"26@mt-ntxsyc.cfg",
	"26@mt-ntxsym.cfg",
	"26@mt-nxlmi.cfg",
	"26@mt-zeur.cfg",
	"26@natbib.cfg",
	"26@nomencl.cfg",
	"26@ntheorem.cfg",
	"26@nul:",
	"26@ot1ebgaramond-lf.fd",
	"26@pdfpages.cfg",
	"26@pdfpages.fix",
	"26@rerunfilecheck.cfg",
	"26@slashbox.sty",
	"26@soul.cfg",
	"26@t1ebgaramond-lf.fd",
	"26@t1sourcesanspro-tlf.fd",
	"26@textcomp.cfg",
	"26@times.fontspec",
	"26@timesbd.fontspec",
	"26@timesbi.fontspec",
	"26@timesi.fontspec",
	"26@ts1ebgaramond-lf.fd",
	"26@ts1sourcesanspro-tlf.fd",
	"26@tufbb-tlf.fd",
	"26@tupcr.fd",
	"26@tuphv.fd",
	"26@tuptm.fd",
	"32@Inconsolatazi4-Bold.otf",
	"32@TeXGyreTermesX-Italic.otf",
	"32@lmmono12-regular.otf",
	"32@lmroman12-bold.otf",
	"32@lmroman12-regular.otf",
	"32@lmroman17-regular.otf",
	"45@EBGaramond-BoldItalic-lf-t1--base",
	"45@EBGaramond-Italic-lf-t1--base",
	"45@EBGaramond-Regular-lf-ot1",
	"45@EBGaramond-Regular-lf-sc-t1--base",
	"45@EBGaramond-Regular-lf-t1--base",
	"45@EBGaramond-Regular-lf-ts1--base",
	"45@Inconsolatazi4-Bold.otf,000-UCS32-Add",
	"45@Inconsolatazi4-Regular.otf,000-UCS32-Add",
	"45@LibertineMathMI",
	"45@LibertineMathMI7",
	"45@LibertineMathRM",
	"45@LinBiolinum_R.otf,000-UCS32-Add",
	"45@LinBiolinum_RB.otf,000-UCS32-Add",
	"45@LinLibertine_R.otf,000-UCS32-Add",
	"45@LinLibertine_RB.otf,000-UCS32-Add",
	"45@LinLibertine_RI.otf,000-UCS32-Add",
	"45@MinLibReg-ot1",
	"45@NewTXBMI",
	"45@NewTXBMI5",
	"45@NewTXMI",
	"45@NewTXMI5",
	"45@NewTXMI7",
	"45@SourceSansPro-Black-tlf-t1--base",
	"45@SourceSansPro-Bold-tlf-t1--base",
	"45@SourceSansPro-It-tlf-t1--base",
	"45@SourceSansPro-Light-tlf-t1--base",
	"45@SourceSansPro-Regular-tlf-t1--base",
	"45@SourceSansPro-Regular-tlf-ts1--base",
	"45@TeXGyreTermesX-Bold.otf,000-UCS32-Add",
	"45@TeXGyreTermesX-Italic.otf,000-UCS32-Add",
	"45@TeXGyreTermesX-Regular.otf,000-UCS32-Add",
	"45@TeXGyreTermesX-Slanted.otf,000-UCS32-Add",
	"45@cmbx10",
	"45@cmbx7",
	"45@cmex10",
	"45@cmmi10",
	"45@cmmi12",
	"45@cmmi7",
	"45@cmmi8",
	"45@cmmib10",
	"45@cmr10",
	"45@cmr12",
	"45@cmr6",
	"45@cmr7",
	"45@cmr8",
	"45@cmsy10",
	"45@cmsy7",
	"45@cmsy8",
	"45@ec-lmtt10",
	"45@eurm10",
	"45@eurm7",
	"45@lcircle10",
	"45@lmex10",
	"45@lmmi12",
	"45@lmmi8",
	"45@lmmi9",
	"45@lmmono12-regular.otf,000-UCS32-Add",
	"45@lmmono9-regular.otf,000-UCS32-Add",
	"45@lmroman10-bold.otf,000-UCS32-Add",
	"45@lmroman10-regular.otf,000-UCS32-Add",
	"45@lmroman12-bold.otf,000-UCS32-Add",
	"45@lmroman12-regular.otf,000-UCS32-Add",
	"45@lmroman17-regular.otf,000-UCS32-Add",
	"45@lmroman6-regular.otf,000-UCS32-Add",
	"45@lmroman7-regular.otf,000-UCS32-Add",
	"45@lmroman8-regular.otf,000-UCS32-Add",
	"45@lmsans10-bold.otf,000-UCS32-Add",
	"45@lmsans12-regular.otf,000-UCS32-Add",
	"45@lmsy10",
	"45@lmsy8",
	"45@msam10",
	"45@msbm10",
	"45@ntx-Bold-tlf-ot1r",
	"45@ntx-Regular-tlf-ot1r",
	"45@ntxsym",
	"45@pzdr",
	"45@rm-lmr12",
	"45@rm-lmr8",
	"45@simkai.ttf,000-UCS32-Add",
	"45@simsun.ttc,000-UCS32-Add",
	"45@stxscr",
	"45@times.ttf,000-UCS32-Add",
	"45@timesbd.ttf,000-UCS32-Add",
	"45@timesi.ttf,000-UCS32-Add",
	"45@txbmiaX",
	"45@txex-bar",
	"45@txexs",
	"45@txmiaSTbb",
	"45@txmiaX",
	"45@txsys"};
const char* dpx_cfg = R"(V  7
p  a4
O  0
K  40
P  0x003C
D  "MakeEPSTOPDF '%o' '%i'"
f  pdftex.map
f kanjix.map
f ckx.map)";
#elif defined(PDFTEXWASM)
std::set<cppstr> web_301 = {

	"26@CJK.cfg",
	"26@acmart-preload-hook.tex",
	"26@amsart.cfg",
	"26@babel-pdflatex.cfg",
	"26@bblopts.cfg",
	"26@biblatex-dm.cfg",
	"26@block.tss",
	"26@bookmark.cfg",
	"26@c00enc.dfu",
	"26@c01enc.dfu",
	"26@c05enc.dfu",
	"26@c09enc.dfu",
	"26@c10enc.dfu",
	"26@c11enc.dfu",
	"26@c19enc.dfu",
	"26@c20enc.dfu",
	"26@c21enc.dfu",
	"26@c31enc.dfu",
	"26@c32enc.dfu",
	"26@c33enc.dfu",
	"26@c34enc.dfu",
	"26@c35enc.dfu",
	"26@c36enc.dfu",
	"26@c37enc.dfu",
	"26@c40enc.dfu",
	"26@c41enc.dfu",
	"26@c42enc.dfu",
	"26@c43enc.dfu",
	"26@c49enc.dfu",
	"26@c50enc.dfu",
	"26@c52enc.dfu",
	"26@c60enc.dfu",
	"26@c61enc.dfu",
	"26@c62enc.dfu",
	"26@c63enc.dfu",
	"26@c64enc.dfu",
	"26@c65enc.dfu",
	"26@c70enc.dfu",
	"26@c80enc.dfu",
	"26@c81enc.dfu",
	"26@chicago-authordate-trad.dbx",
	"26@chicago-authordate16.dbx",
	"26@cup-logo-new",
	"26@english.cfg",
	"26@epstopdf.cfg",
	"26@fancyvrb.cfg",
	"26@fleqn.ldf",
	"26@fzhei.fontspec",
	"26@fzsong.fontspec",
	"26@geometry.cfg",
	"26@gettitlestring.cfg",
	"26@hyperref.cfg",
	"26@l3bitset.sty",
	"26@l3graphics.sty",
	"26@l3opacity.sty",
	"26@lms.cmap",
	"26@lmsenc.dfu",
	"26@lmx.cmap",
	"26@lmxenc.dfu",
	"26@mt-LinuxBiolinumT-TLF.cfg",
	"26@mt-LinuxBiolinumT.cfg",
	"26@mt-LinuxLibertineT-TLF.cfg",
	"26@mt-LinuxLibertineT.cfg",
	"26@mt-SourceSansPro-TLF.cfg",
	"26@mt-SourceSansPro.cfg",
	"26@mt-cme.cfg",
	"26@mt-cme.cfg",
	"26@mt-cmex.cfg",
	"26@mt-cmex.cfg",
	"26@mt-cmm.cfg",
	"26@mt-cmsy.cfg",
	"26@mt-cmtt.cfg",
	"26@mt-fbb-TLF.cfg",
	"26@mt-fbb.cfg",
	"26@mt-lato-TLF.cfg",
	"26@mt-lato.cfg",
	"26@mt-ntxex.cfg",
	"26@mt-ntxexa.cfg",
	"26@mt-ntxexx.cfg",
	"26@mt-ntxmi.cfg",
	"26@mt-ntxmia.cfg",
	"26@mt-ntxsfmi.cfg",
	"26@mt-ntxsfmia.cfg",
	"26@mt-ntxsy.cfg",
	"26@mt-ntxsyc.cfg",
	"26@mt-ntxsym.cfg",
	"26@mt-nxlmi.cfg",
	"26@mt-phv.cfg",
	"26@mt-zeur.cfg",
	"26@mt-zi4.cfg",
	"26@natbib.cfg",
	"26@nul:",
	"26@omlcmm.fdx",
	"26@omlenc.dfu",
	"26@omscmsy.fdx",
	"26@omsptm.fdx",
	"26@omxcmex.fdx",
	"26@omxenc.dfu",
	"26@ot1cmr.fdx",
	"26@ot1ebgaramond-lf.fd",
	"26@ot1lato-tlf.fd",
	"26@ot1linuxlibertinet-tlf.fd",
	"26@ot1pcr.fdx",
	"26@ot1ptm.fdx",
	"26@pd1enc.dfu",
	"26@puenc.dfu",
	"26@rerunfilecheck.cfg",
	"26@sampleteaser",
	"26@soul.cfg",
	"26@t1ebgaramond-lf.fd",
	"26@t1fbb-tlf.fd",
	"26@t1lato-tlf.fd",
	"26@t1linuxbiolinumt-tlf.fd",
	"26@t1linuxlibertinet-tlf.fd",
	"26@t1sourcesanspro-tlf.fd",
	"26@textcomp.cfg",
	"26@thesis.lof",
	"26@thesis.lot",
	"26@times.fontspec",
	"26@timesbd.fontspec",
	"26@timesbi.fontspec",
	"26@timesi.fontspec",
	"26@ts1.cmap",
	"26@ts1ebgaramond-lf.fd",
	"26@ts1lato-tlf.fd",
	"26@ts1linuxlibertinet-tlf.fd",
	"26@ts1ptm.fdx",
	"26@ts1sourcesanspro-tlf.fd",
	"26@u.cmap",
	"26@uenc.dfu",
	"26@ulasy.fdx",
	"26@umsa.fdx",
	"26@umsb.fdx",
	"26@ustmry.fd",
	"26@ustmry.fdx",
	"26@utt.cmap"};
#else
#	error "Unknown TeX engine"
#endif
static uint32_t simpleHash(const std::string& filePath) {
	std::ifstream  file(filePath, std::ios::binary);
	uint32_t	   hash = 0;
	const uint32_t seed = 131;
	char		   byte;
	while (file.get(byte)) { hash = (hash * seed) + static_cast<uint8_t>(byte); }
	return hash;
}

template <typename... Args>
std::vector<cppstr> fixExt(const cppstr& filename, Args... extensions) {
	std::vector<cppstr> result;
	auto				checkAndAddExtension = [&filename, &result](const char* ext) {
		   size_t suffixLen = strlen(ext);
		   if (strcasecmp(filename.c_str() + filename.size() - suffixLen, ext) == 0) {
			   result.push_back(filename);
		   }
		   else { result.push_back(filename + ext); }
	};
	(checkAndAddExtension(extensions), ...);
	return result;
}
static vecstr fixExtension(const cppstr& filename, kpse_file_format_type format) {
	switch (format) {
		case kpse_gf_format: return fixExt(filename, ".gf");
		case kpse_pk_format: return fixExt(filename, ".pk");
		case kpse_tfm_format: return fixExt(filename, ".tfm");
		case kpse_afm_format: return fixExt(filename, ".afm");
		case kpse_base_format: return fixExt(filename, ".base");
		case kpse_bib_format: return fixExt(filename, ".bib");
		case kpse_bst_format: return fixExt(filename, ".bst");
		case kpse_cnf_format: return fixExt(filename, ".cnf");
		case kpse_db_format: return fixExt(filename, "ls-r", "ls-R");
		case kpse_fmt_format: return fixExt(filename, ".fmt");
		case kpse_fontmap_format: return fixExt(filename, ".map");
		case kpse_mem_format: return fixExt(filename, ".mem");
		case kpse_mf_format: return fixExt(filename, ".mf");
		case kpse_mft_format: return fixExt(filename, ".mft");
		case kpse_mfpool_format: return fixExt(filename, ".pool");
		case kpse_mp_format: return fixExt(filename, ".mp");
		case kpse_mppool_format: return fixExt(filename, ".pool");
		case kpse_mpsupport_format: return {};
		case kpse_ocp_format: return fixExt(filename, ".ocp");
		case kpse_ofm_format: return fixExt(filename, ".ofm", ".tfm");
		case kpse_opl_format: return fixExt(filename, ".opl", ".pl");
		case kpse_otp_format: return fixExt(filename, ".otp");
		case kpse_ovf_format: return fixExt(filename, ".ovf", ".vf");
		case kpse_ovp_format: return fixExt(filename, ".ovp", ".vpl");
		case kpse_pict_format: return fixExt(filename, ".eps", ".epsi");
		case kpse_tex_format:
			// TODO: why?
			return fixExt(filename, ".tex");
			// return fixExt(
			// 	filename, ".tex", ".sty", ".cls", ".fd", ".aux", ".bbl", ".def", ".clo",
			// 	".ldf");
		case kpse_texdoc_format: return {};
		case kpse_texpool_format: return fixExt(filename, ".pool");
		case kpse_texsource_format: return fixExt(filename, ".dtx", ".ins");
		case kpse_tex_ps_header_format: return fixExt(filename, ".pro");
		case kpse_troff_font_format: return {};
		case kpse_type1_format: return fixExt(filename, ".pfa", ".pfb");
		case kpse_vf_format: return fixExt(filename, ".vf");
		case kpse_dvips_config_format: return {};
		case kpse_ist_format: return fixExt(filename, ".ist");
		case kpse_truetype_format:
			return fixExt(filename, ".ttf", ".ttc", ".TTF", ".TTC", ".dfont");
		case kpse_type42_format: return fixExt(filename, ".t42", ".T42");
		case kpse_web2c_format: return {};
		case kpse_program_text_format: return {};
		case kpse_program_binary_format: return {};
		case kpse_miscfonts_format: return {};
		case kpse_web_format: return fixExt(filename, ".web", ".ch");
		case kpse_cweb_format: return fixExt(filename, ".w", ".web", ".ch");
		case kpse_enc_format: return fixExt(filename, ".enc");
		case kpse_cmap_format: return {};
		case kpse_sfd_format: return fixExt(filename, ".sfd");
		case kpse_opentype_format: return fixExt(filename, ".otf", ".OTF");
		case kpse_pdftex_config_format: return {};
		case kpse_lig_format: return fixExt(filename, ".lig");
		case kpse_texmfscripts_format: return {};
		case kpse_lua_format:
			return fixExt(
				filename, ".lua", ".luatex", ".luc", ".luctex", ".texlua", ".texluc",
				".tlu");
		case kpse_fea_format: return fixExt(filename, ".fea");
		case kpse_cid_format: return fixExt(filename, ".cid", ".cidmap");
		case kpse_mlbib_format: return fixExt(filename, ".mlbib", ".bib");
		case kpse_mlbst_format: return fixExt(filename, ".mlbst", ".bst");
		case kpse_clua_format: return fixExt(filename, ".dll", ".so");
		case kpse_ris_format: return fixExt(filename, ".ris");
		case kpse_bltxml_format: return fixExt(filename, ".bltxml");
		default: return {};
	}
}

cppstr getFileSize(const cppstr& path) {
	try {
		std::uintmax_t size = std::filesystem::file_size(path);

		const char* units[]		 = {"B", "KB", "MB", "GB", "TB"};
		int			unitIndex	 = 0;
		double		readableSize = static_cast<double>(size);

		// 当文件大小大于等于1024且还有更大的单位可用时，转换为更大的单位
		while (readableSize >= 1024.0 && unitIndex < 4) {
			readableSize /= 1024.0;
			unitIndex++;
		}

		// 格式化为字符串，只有当值小于10时才显示一位小数
		char buffer[32];
		if (unitIndex == 0) {  // 字节单位，总是显示整数
			snprintf(buffer, sizeof(buffer), "%.0f%s", readableSize, units[unitIndex]);
		}
		else if (readableSize < 10.0) {	 // 小于10的值显示一位小数
			snprintf(buffer, sizeof(buffer), "%.1f%s", readableSize, units[unitIndex]);
		}
		else {	// 大于等于10的值只显示整数部分
			snprintf(buffer, sizeof(buffer), "%.0f%s", readableSize, units[unitIndex]);
		}

		return cppstr(buffer);
	}
	catch (const std::filesystem::filesystem_error&) {
		return "Unknown";  // 如果无法获取文件信息，则返回未知
	}
}
class PackageManager {
public:
	PackageManager() {
		if (std::filesystem::exists("/tex/pkg/tlpkg.txt") == false) {
			char* result = ctan_get_file("tlpkg.txt", kpse_userdef_pkg_format);
			if (result == nullptr) return;
		}
		if (std::filesystem::exists("/tex/pkg/tlpkg.txt")) loadTLPKG();
		initialized = true;
	}
	void print() const {
		if (initialized == false) {
			std::cout << "PackageManager not initialized" << std::endl;
			return;
		}
		for (size_t i = 0; i < pkgList.size(); ++i) {
			std::cout << pkgList[i] << ": ";
			for (auto& fileName : fileMap) {
				if (fileName.second == i) std::cout << fileName.first << " ";
			}
			std::cout << std::endl;
		}
		return;
	}
	char* getFile(const cppstr& request_name, kpse_file_format_type type) {
		if (initialized == false) {
			std::cout << "PackageManager not initialized" << std::endl;
			return nullptr;
		}
		const auto& [filename, index] = findFile(request_name, type);
		if (filename.empty()) return nullptr;
		const cppstr packPath = "/tex/pkg/" + pkgList[index] + ".tar.xz";
		if (fs::exists(packPath) == false) {
			cppstr reqName = pkgList[index] + ".tar.xz";
			ctan_get_file(reqName.c_str(), kpse_userdef_pkg_format);
		}
		if (fs::exists(packPath) == false) return nullptr;
		if (extractor::tar_xz(packPath, filename, "/tex/" + filename)) {
			return strdup(("/tex/" + filename).c_str());
		}
		return nullptr;
	}
	static std::set<cppstr> blackList;

private:
	void loadTLPKG() {
		std::ifstream file("/tex/pkg/tlpkg.txt");
		if (!file.is_open()) { return; }
		pkgList.reserve(5000);
		cppstr line;
		int	   pkgIndex = 0;
		while (std::getline(file, line)) {
			if (line.empty()) continue;
			size_t spacePos = line.find_last_of(' ');
			if (spacePos == std::string::npos) continue;
			cppstr pkgName	 = line.substr(0, spacePos);
			int	   fileCount = std::stoi(line.substr(spacePos + 1));
			pkgList.push_back(pkgName);
			for (int i = 0; i < fileCount; ++i) {
				cppstr fileName;
				if (std::getline(file, fileName)) {
					// we don't need multiple file.
					if (blackList.find(fileName) != blackList.end()) continue;
					if (fileMap.find(fileName) != fileMap.end()) {
						blackList.insert(fileName);
						fileMap.erase(fileName);
						continue;
					}
					fileMap[fileName] = pkgIndex;
				}
			}
			pkgIndex++;
		}
		file.close();
	}
	std::pair<cppstr, size_t>
	findFile(const cppstr& filename, kpse_file_format_type format) {
		if (auto it = fileMap.find(filename); it != fileMap.end()) {
			return {filename, it->second};
		}
		for (const cppstr& fixedName : fixExtension(filename, format)) {
			if (auto it = fileMap.find(fixedName); it != fileMap.end()) {
				return {fixedName, it->second};
			}
		}
		return {cppstr(), 0};
	}
	bool				  initialized = false;
	std::vector<cppstr>	  pkgList;
	std::map<cppstr, int> fileMap;
};
class VFFileSupport {
public:
	VFFileSupport() {
		if (std::filesystem::exists("/tex/pkg/vfpkg.txt") == false) {
			char* result = ctan_get_file("vfpkg.txt", kpse_userdef_pkg_format);
			if (result == nullptr) return;
		}
		if (std::filesystem::exists("/tex/pkg/vfpkg.txt")) loadVFPKG();
	}
	bool checkVFFile(const cppstr& filename) {
		if (avaliableVFFile.size() == 0) return true;
		bool end_is_vf =
			filename.size() >= 3 && filename.substr(filename.size() - 3) == ".vf";
		bool end_is_fontspec =
			filename.size() >= 9 && filename.substr(filename.size() - 9) == ".fontspec";
		if (end_is_vf == false && end_is_fontspec == false) return true;
		return avaliableVFFile.find(filename) != avaliableVFFile.end();
	}

private:
	void loadVFPKG() {
		std::ifstream file("/tex/pkg/vfpkg.txt");
		if (!file.is_open()) { return; }
		cppstr line;
		while (std::getline(file, line)) {
			if (line.empty()) continue;
			avaliableVFFile.insert(line);
		}
		file.close();
	}
	std::set<cppstr> avaliableVFFile;
};
class Recorder {
public:
	Recorder(const cppstr& _name, kpse_file_format_type _type)
		: name_(_name), type_(_type) {}
	~Recorder() {
		name	= name_;
		type	= type_;
		success = success_;
	}
	char* failed() {
		success_ = false;
		return nullptr;
	}
	static cppstr				 name;
	static kpse_file_format_type type;
	static bool					 success;

private:
	cppstr				  name_;
	kpse_file_format_type type_;
	bool				  success_ = true;
};
cppstr				  Recorder::name	= "";
kpse_file_format_type Recorder::type	= kpse_userdef_pkg_format;
bool				  Recorder::success = true;
std::set<cppstr>	  PackageManager::blackList;

static cppstr caseExists(const cppstr& filename) {
	if (filename.empty()) { return {}; }
	if (std::filesystem::exists(filename)) return filename;
	if (std::filesystem::exists("/tex/" + filename)) return "/tex/" + filename;
	if (std::filesystem::exists("/output/" + filename)) return "/output/" + filename;
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
		if (DIR* dir = opendir("/output"); dir != nullptr) {
			struct dirent* entry;
			while ((entry = readdir(dir)) != nullptr) {
				if (strcasecmp(entry->d_name, base_name.c_str()) == 0)
					return cppstr("/output/") + entry->d_name;
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
static bool mainEntryLike(const cppstr& filename) {
	cppstr entry_file_base = fs::path(main_entry_file).filename();
	entry_file_base		   = entry_file_base.substr(0, entry_file_base.find_last_of("."));
	if (filename.size() <= entry_file_base.size() ||
		filename.substr(0, entry_file_base.size()) != entry_file_base)
		return false;
	if (filename == entry_file_base + ".aux" || filename == entry_file_base + ".log" ||
		filename == entry_file_base + ".tex" || filename == entry_file_base + ".pdf" ||
		filename == entry_file_base + ".out" || filename == entry_file_base + ".bbl" ||
		filename == entry_file_base + ".blg" || filename == entry_file_base + ".gls" ||
		filename == entry_file_base + ".toc" || filename == entry_file_base + ".toe" ||
		filename == entry_file_base + ".glsdefs" ||
		filename == entry_file_base + ".run.xml")
		return true;
	return false;
}
static void MakeBBLLabel(const cppstr& filename) {
	cppstr entry_file_base = fs::path(main_entry_file).filename();
	entry_file_base		   = entry_file_base.substr(0, entry_file_base.find_last_of("."));
	if (filename == entry_file_base + ".bbl") { bbl_required = true; }
}
extern "C" char*
kpse_find_file(const char* _name, kpse_file_format_type format, boolean must_exist) {
	Recorder recorder(_name, format);
	auto	 checkWebEntry = [&](const cppstr& filename) {
		if (filename.find("/") != cppstr::npos) return false;
		if (mainEntryLike(filename) == true) return false;
#ifdef PDFTEXWASM
		static VFFileSupport vfmgr;
		if (vfmgr.checkVFFile(filename) == false) return false;
#elif defined(XETEXWASM)
		/* 获取 filename 文件格式，拒绝某些特定格式 */
		if (size_t pos = filename.find_last_of("."); pos != std::string::npos) {
			cppstr filenameExt = filename.substr(pos);
			if (filenameExt == ".bb") return false;
		}
#endif
		if (size_t pos = filename.find_last_of("."); pos != std::string::npos) {
			cppstr		filenameExt = filename.substr(pos);
			const auto& bls			= PackageManager::blackList;
			if (filenameExt == ".cfg" && bls.find(filename) == bls.end()) return false;
		}
		if (format != recorder.type || recorder.success == true) return true;
		/* 和主文件名相同、上次也相同，且 format 一样，上次失败的，拒绝网络请求 */
		cppstr filenameNoExt = filename.substr(0, filename.find_last_of("."));
		cppstr lastnameNoExt = recorder.name.substr(0, recorder.name.find_last_of("."));
		if (filenameNoExt == lastnameNoExt && recorder.success == false) {
			// 对比主文件名
			cppstr entNoExt = fs::path(main_entry_file).filename();
			entNoExt		= entNoExt.substr(0, entNoExt.find_last_of("."));
			if (filenameNoExt == entNoExt) return false;
		}
		return true;
	};
	if (_name == nullptr) return recorder.failed();
	const cppstr name(_name);
#ifdef XETEXWASM
	if (name == "dvipdfmx.cfg" && format == kpse_program_text_format) {
		std::ofstream("/tex/dvipdfmx.cfg") << dpx_cfg;
	}
#endif
	if (name.empty()) return recorder.failed();
	const cppstr		  searchKey = std::to_string(format) + '@' + name;
	static FileQueryCache workCache;
	static SearchCache	  allCache;
	static cppstr		  latexmkrcPath = workCache.query(".latexmkrc");
	if (latexmkrcPath.empty()) latexmkrcPath = workCache.query("latexmkrc");
	// make return value and make cache
	if (auto it = allCache.find(searchKey); it != allCache.end()) {
		if (changed_files.find(getFileNameFromPath(name)) == changed_files.end()) {
			if (it->second != nullptr)
				return strdup(it->second);
			else
				return recorder.failed();
		}
	}
	if (latexmkrcPath.size() != 0) {
		static LatexmkrcParser parser(latexmkrcPath);
		auto				   data = parser.query(name);
		// todo: the parser query arg2
		if (data.size() != 0) return allCache.addCache(searchKey, data[0].second);
	}
	cppstr no_suffix_path;
	// check if there is a suffix
	auto has_dot_in_filename = [](const cppstr& path) -> bool {
		if (path.empty()) return false;
		size_t last_slash = path.find_last_of('/');
		size_t start	  = (last_slash == cppstr::npos) ? 0 : last_slash + 1;
		return path.find('.', start) != cppstr::npos;
	};
	// try with name
	if (auto ci_match = caseExists(name); !ci_match.empty()) {
		if (has_dot_in_filename(ci_match)) return allCache.addCache(searchKey, ci_match);
		if (no_suffix_path.empty()) no_suffix_path = std::move(ci_match);
	}
	// try to add suffix
	const auto fixedNames = fixExtension(name, format);
	for (auto nameFixExt : fixedNames) {
		if (auto ci_match = caseExists(nameFixExt); !ci_match.empty()) {
			if (has_dot_in_filename(ci_match))
				return allCache.addCache(searchKey, ci_match);
			if (no_suffix_path.empty()) no_suffix_path = std::move(ci_match);
		}
	}
	// try to find in local project(not root)
	if (const cppstr workQuert1 = workCache.query(name); workQuert1.size() != 0) {
		if (has_dot_in_filename(workQuert1))
			return allCache.addCache(searchKey, workQuert1);
		if (no_suffix_path.empty()) no_suffix_path = std::move(workQuert1);
	}
	// try to find in remote
	static PackageManager pkgMgr;
	if (char* remote1 = pkgMgr.getFile(name, format); remote1 != nullptr)
		return allCache.addCache(searchKey, remote1);
	if (web_301.find(searchKey) == web_301.end() && checkWebEntry(name)) {
		if (char* remote2 = ctan_get_file(name.c_str(), format); remote2 != nullptr)
			return allCache.addCache(searchKey, remote2);
	}
	// try to find in local project with more than(not root)
	for (auto nameFixExt : fixedNames) {
		if (const cppstr workQuert2 = workCache.query(nameFixExt);
			workQuert2.size() != 0) {
			if (has_dot_in_filename(workQuert2))
				return allCache.addCache(searchKey, workQuert2);
			if (no_suffix_path.empty()) no_suffix_path = std::move(workQuert2);
		}
	}
	// finally, we use no suffix result
	if (no_suffix_path.size() != 0) return allCache.addCache(searchKey, no_suffix_path);
	MakeBBLLabel(name);
	recorder.failed();
	return allCache.addCache(searchKey, nullptr);
}

#if 0
extern "C" char*
kpse_find_file(const char* _name, kpse_file_format_type format, boolean must_exist) {
	char* res = kpse_find_file_wrap(_name, format, must_exist);
	if (res == nullptr)
		std::cerr << "[DEBUG] kpse_find_file(name=\"" << _name << "\", format=" << format
				  << ") = nullptr" << std::endl;
	else
		std::cerr << "[DEBUG] kpse_find_file(name=\"" << _name << "\", format=" << format
				  << ") = " << res << std::endl;
	return res;
}
#endif
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
