#ifndef KPSEEMU
#define KPSEEMU
#include "type.h"
#include <w2c/config.h>

extern int kpse_make_tex_discard_errors;
extern int kpathsea_debug;
#define kpseinnameok kpse_in_name_ok
#define kpseoutnameok kpse_out_name_ok
#define kpseinitprog kpse_init_prog
#define kpse_find_tex(name) kpse_find_file(name, kpse_tex_format, true)
#define kpse_find_pict(name) kpse_find_file (name, kpse_pict_format, true)
#define kpsesetprogramenabled kpse_set_program_enabled
#define kpsetexformat kpse_tex_format
#define kpsebibformat kpse_bib_format
#define kpsebstformat kpse_bst_format
#define kpsepkformat kpse_pk_format
#define kpsesrccompile kpse_src_compile
#define kpsemaketexdiscarderrors kpse_make_tex_discard_errors
#define DIR_SEP '/'
#define DIR_SEP_STRING "/"
#define ISDIRSEP IS_DIR_SEP
#define IS_DIR_SEP(ch) ((ch) == DIR_SEP)
extern string  kpse_program_name;
extern boolean kpse_in_name_ok(const_string fname);
extern boolean kpse_out_name_ok(const_string fname);
extern void	   kpse_init_prog(
	   const_string prefix,
	   unsigned		dpi,
	   const_string mode,
	   const_string fallback);
extern void
kpse_set_program_enabled(kpse_file_format_type fmt, boolean value, kpse_src_type level);
extern string
kpse_find_file(const_string name, kpse_file_format_type format, boolean must_exist);
extern string		kpse_find_pk(const_string passed_fontname, unsigned int dpi);
extern boolean		kpse_absolute_p(const_string filename, boolean relative_ok);
extern boolean		kpse_in_name_ok(const_string fname);
extern boolean		kpse_out_name_ok(const_string fname);
extern void			kpse_set_program_name(const_string argv0, const_string progname);
extern void			kpse_reset_program_name(const_string progname);
extern string		kpse_program_basename(const_string argv0);
extern string		concat3(const_string s1, const_string s2, const_string s3);
extern const_string xbasename(const_string name);
extern int			xfclose(FILE* stream, const_string filename);
extern FILE*		xfopen(const_string filename, const_string mode);
extern void			xfseek(FILE* fp, long offset, int wherefrom, const_string filename);
extern long			xftell(FILE* f, const_string filename);
extern long			xftello(FILE* f, const_string filename);
extern void			xfseeko(FILE* f, off_t offset, int wherefrom, const_string filename);
#endif
