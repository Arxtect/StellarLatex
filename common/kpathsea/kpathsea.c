#define EXTERN extern
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#ifdef XETEXWASM
#include <xetexd.h>
#elif defined(PDFTEXWASM)
#include <pdftexd.h>
#else
#error "unknown compiler"
#endif
#include <stdlib.h>
#include <libgen.h>
#include <string.h>
#include <dirent.h>

#include <ctan/ctanInterface.h>

string kpse_program_name = NULL;
int kpse_make_tex_discard_errors;
int kpathsea_debug;
void setupboundvariable(integer *var, const_string var_name, integer dflt) {

  *var = dflt;

  if (strcmp(var_name, "main_memory") == 0) {
    *var = 5000000;
  } else if (strcmp(var_name, "extra_mem_top") == 0) {
    *var = 0;
  } else if (strcmp(var_name, "extra_mem_bot") == 0) {
    *var = 0;
  } else if (strcmp(var_name, "pool_size") == 0) {
    *var = 6250000;
  } else if (strcmp(var_name, "string_vacancies") == 0) {
    *var = 90000;
  } else if (strcmp(var_name, "pool_free") == 0) {
    *var = 47500;
  } else if (strcmp(var_name, "max_strings") == 0) {
    *var = 500000;
  } else if (strcmp(var_name, "font_mem_size") == 0) {
    *var = 8000000;
  } else if (strcmp(var_name, "font_max") == 0) {
    *var = 9000;
  } else if (strcmp(var_name, "trie_size") == 0) {
    *var = 1000000;
  } else if (strcmp(var_name, "hyph_size") == 0) {
    *var = 8191;
  } else if (strcmp(var_name, "buf_size") == 0) {
    *var = 200000;
  } else if (strcmp(var_name, "nest_size") == 0) {
    *var = 500;
  } else if (strcmp(var_name, "max_in_open") == 0) {
    *var = 15;
  } else if (strcmp(var_name, "param_size") == 0) {
    *var = 10000;
  } else if (strcmp(var_name, "save_size") == 0) {
    *var = 100000;
  } else if (strcmp(var_name, "stack_size") == 0) {
    *var = 5000;
  } else if (strcmp(var_name, "dvi_buf_size") == 0) {
    *var = 16384;
  } else if (strcmp(var_name, "error_line") == 0) {
    *var = 79;
  } else if (strcmp(var_name, "half_error_line") == 0) {
    *var = 50;
  } else if (strcmp(var_name, "max_print_line") == 0) {
    *var = 79;
  } else if (strcmp(var_name, "hash_extra") == 0) {
    *var = 600000;
  }
}

string concat3(const_string s1, const_string s2, const_string s3) {
  int s2l = s2 ? strlen(s2) : 0;
  int s3l = s3 ? strlen(s3) : 0;
  string answer = (string)xmalloc(strlen(s1) + s2l + s3l + 1);
  strcpy(answer, s1);
  if (s2)
    strcat(answer, s2);
  if (s3)
    strcat(answer, s3);

  return answer;
}

integer zround(double r) {
  integer i;
  if (r > 2147483647.0)
    i = 2147483647;
  else if (r < -2147483647.0)
    i = -2147483647;
  else if (r >= 0.0)
    i = (integer)(r + 0.5);
  else
    i = (integer)(r - 0.5);

  return i;
}

const_string xbasename(const_string name) {
#define IS_DEVICE_SEP(ch) ((ch) == ':')
#define NAME_BEGINS_WITH_DEVICE(name) (*(name) && IS_DEVICE_SEP((name)[1]))
  const_string base = name;
  const_string p;
  if (NAME_BEGINS_WITH_DEVICE(name))
    base += 2;

  for (p = base; *p; p++) {
    if (*p == '/')
      base = p + 1;
  }

  return base;
}

boolean dir_p(string fn) {
  struct stat stats;
  return stat(fn, &stats) == 0 && S_ISDIR(stats.st_mode);
}

boolean kpse_absolute_p(const_string filename, boolean relative_ok) {
  boolean absolute;
  boolean explicit_relative;

  absolute = (*filename == '/')? true : false;
  explicit_relative = relative_ok;
  return absolute || explicit_relative;
}

void kpse_init_prog(const_string prefix, unsigned dpi, const_string mode,
                    const_string fallback) {}

boolean kpse_in_name_ok(const_string fname) { return true; }
boolean kpse_out_name_ok(const_string fname) { return true; }

void kpse_set_program_enabled(kpse_file_format_type fmt, boolean value,
                              kpse_src_type level) {}

void kpse_set_program_name(const_string argv0, const_string progname) {
  if (kpse_program_name != NULL) free(kpse_program_name);
  kpse_program_name = malloc(strlen(progname)+1);
  if (kpse_program_name != NULL) strcpy(kpse_program_name, progname);
}

void kpse_reset_program_name(const_string progname) {}

string 		kpse_program_basename (const_string argv0) {
  return xstrdup(argv0);
}

void xfseek(FILE *fp, long offset, int wherefrom, const_string filename) {
  int ret = fseek(fp, offset, wherefrom);
  if (ret != 0) {
    fprintf(stderr, "File Seek Failed %s", filename);
    abort();
  }
}

long xftell(FILE *f, const_string filename) {
  long where = ftell(f);

  if (where < 0) {
    fprintf(stderr, "File Tell Failed %s", filename);
    abort();
  }

  return where;
}

long xftello(FILE *f, const_string filename) {
  long where = ftello(f);

  if (where < 0) {
    fprintf(stderr, "File Tello Failed %s", filename);
    abort();
  }

  return where;
}

void xfseeko(FILE *f, off_t offset, int wherefrom, const_string filename) {
  if (fseeko(f, offset, wherefrom) != 0) {
    fprintf(stderr, "File fseeko Failed (%s %d %d)", filename, (int)(offset),
            wherefrom);
    abort();
  }
}

FILE *xfopen(const_string filename, const_string mode) {
  FILE *f;
  f = fopen(filename, mode);
  if (f == NULL) {
    fprintf(stderr, "File Open Failed (%s)\n", filename);
    abort();
  }

  return f;
}

int xfclose(FILE *stream, const_string filename) {
  int ret = fclose(stream);
  if (ret != 0) {
    fprintf(stderr, "File Close Failed %s", filename);
    abort();
  }
  return 0;
}
