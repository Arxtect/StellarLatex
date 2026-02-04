#ifndef MIN_TEXMFMP
#define MIN_TEXMFMP
#include "w2c/config.h"
#include "cpascal.h"
#include "lib/lib.h"
#include <assert.h>
#include <errno.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stddef.h>
#include <zlib.h>

#ifdef TeX
#if defined (pdfTeX)
#define TEXMFPOOLNAME "pdftex.pool"
#define TEXMFENGINENAME "pdftex"
#elif defined (XeTeX)
#define TEXMFPOOLNAME "xetex.pool"
#define TEXMFENGINENAME "xetex"
#else
#error "unknown compiler"
#endif
#define DUMP_FILE fmtfile
#define DUMP_FORMAT kpse_fmt_format
#define writedvi WRITE_OUT
#define flushdvi flush_out
#define OUT_FILE dvifile
#define OUT_BUF dvibuf
#endif

#ifdef XeTeX
#define XETEX_UNICODE_FILE_DEFINED	1
typedef struct {
  FILE *f;
  long  savedChar;
  short skipNextLF;
  short encodingMode;
  void *conversionData;
} UFILE;
typedef UFILE* unicodefile;
typedef void* voidpointer;
#endif

// File
#define recorderchangefilename recorder_change_filename

/* (Un)dumping.  These are called from the change file.  */
#define dumpthings(base, len) do_dump((char*)&(base), sizeof(base), (int)(len), DUMP_FILE)
#define undumpthings(base, len)                                                          \
	do_undump((char*)&(base), sizeof(base), (int)(len), DUMP_FILE)

#ifndef PRIdPTR
#define PRIdPTR "ld"
#endif
#ifndef PRIxPTR
#define PRIxPTR "lx"
#endif

#define undumpcheckedthings(low, high, base, len)                                        \
	do {                                                                                 \
		unsigned i;                                                                      \
		undumpthings(base, len);                                                         \
		for (i = 0; i < (len); i++) {                                                    \
			if ((&(base))[i] < (low) || (&(base))[i] > (high)) {                         \
				fprintf(                                                                 \
					stderr,                                                              \
					"Item %u (=%" PRIdPTR ") of .fmt array at %" PRIxPTR " <%" PRIdPTR   \
					" or >%" PRIdPTR,                                                    \
					i, (uintptr_t)(&(base))[i], (uintptr_t)&(base), (uintptr_t)low,      \
					(uintptr_t)high);                                                    \
			}                                                                            \
		}                                                                                \
	} while (0)

/* Like undump_checked_things, but only check the upper value. We use
   this when the base type is unsigned, and thus all the values will be
   greater than zero by definition.  */
#define undumpuppercheckthings(high, base, len)                                          \
	do {                                                                                 \
		unsigned i;                                                                      \
		undumpthings(base, len);                                                         \
		for (i = 0; i < (len); i++) {                                                    \
			if ((&(base))[i] > (high)) {                                                 \
				fprintf(                                                                 \
					stderr,                                                              \
					"Item %u (=%" PRIdPTR ") of .fmt array at %" PRIxPTR " >%" PRIdPTR,  \
					i, (uintptr_t)(&(base))[i], (uintptr_t)&(base), (uintptr_t)high);    \
			}                                                                            \
		}                                                                                \
	} while (0)

// Misc
#if !defined(Aleph)
extern void readtcxfile (void);
extern string translate_filename;
#define translatefilename translate_filename
#endif

// File Function
#define	inputln(stream, flag) input_line (stream)
#ifndef XETEXWASM
boolean input_line(FILE *f);
#endif

#define dateandtime(i,j,k,l) get_date_and_time (&(i), &(j), &(k), &(l))
extern void get_date_and_time (integer *, integer *, integer *, integer *);

#define secondsandmicros(i, j) get_seconds_and_micros(&(i), &(j))
extern void get_seconds_and_micros(integer *, integer *);

extern void	   topenin(void);

#define bopenin(f) open_input(&(f), kpse_tfm_format, FOPEN_RBIN_MODE)
#define bopenout(f) open_output(&(f), FOPEN_WBIN_MODE)
#define bclose aclose
#define wopenin(f) (open_input ((FILE**)&(f), DUMP_FORMAT, FOPEN_RBIN_MODE) \
                        && (f = gzdopen(fileno((FILE*)f), FOPEN_RBIN_MODE)))
#define wopenout(f) (open_output ((FILE**)&(f), FOPEN_WBIN_MODE) \
                        && (f = gzdopen(fileno((FILE*)f), FOPEN_WBIN_MODE)) \
                        && (gzsetparams(f, 1, Z_DEFAULT_STRATEGY) == Z_OK))
#define wclose(f)    gzclose(f)

#ifdef XeTeX
#define uopenin(f, p, m, d) u_open_in(&(f), p, FOPEN_RBIN_MODE, m, d)
#define uclose(f) u_close_inout(&(f))
#endif

// Misc Function
extern char start_time_str[];
extern void initstarttime(void);
extern string find_input_file(integer s);
#if !defined(XeTeX)
extern char *makecstring(integer s);
extern char *makecfilename(integer s);
#endif
extern void getcreationdate(void);
extern void getfilemoddate(integer s);
extern void getfilesize(integer s);
extern void getfiledump(integer s, int offset, int length);
extern void convertStringToHexString(const char *in, char *out, int lin);
extern void getmd5sum(integer s, boolean file);

extern int runsystem(const char *);

#define kpsedvipsconfigformat kpse_dvips_config_format
#define kpsefontmapformat kpse_fontmap_format
#define kpsemfpoolformat kpse_mfpool_format
#define kpsempformat kpse_mp_format
#define kpsemppoolformat kpse_mppool_format
#define kpsetexpoolformat kpse_texpool_format
#define kpsetexformat kpse_tex_format
extern int tfmtemp, texinputtype;

/* We define the routines to do the actual work in texmfmp.c.  */
extern void do_dump (char *, int, int, gzFile);
extern void do_undump (char *, int, int, gzFile);
/* Use the above for all the other dumping and undumping.  */
#define generic_dump(x) dumpthings(x, 1)
#define generic_undump(x) undumpthings(x, 1)

#define dumpwd generic_dump
#define dumphh generic_dump
#define dumpqqqq generic_dump
#define undumpwd generic_undump
#define undumphh generic_undump
#define undumpqqqq generic_undump

/* `dump_int' is called with constant integers, so we put them into a
   variable first.  */
#define dumpint(x)                                                                       \
	do {                                                                                 \
		integer x_val = (x);                                                             \
		generic_dump(x_val);                                                             \
	} while (0)
#define undumpint generic_undump
/* Handle SyncTeX, if requested */
#if defined(TeX)
# if defined(__SyncTeX__)
#  include "synctexdir/synctex-common.h"
extern char *generic_synctex_get_current_name(void);
# endif
#endif

#endif
