#define EXTERN extern
#if defined(XETEXWASM)
#include <xetexd.h>
#elif defined(PDFTEXWASM)
#include <pdftexd.h>
#endif
#include <sys/stat.h>
#include <sys/types.h>

string fullnameoffile;
boolean recorder_enabled;
string output_directory;
int tfmtemp;
int ocptemp;
int texinputtype;

static char* get_parent_path(const char* path) {
    if (path == NULL || strlen(path) <= 1) {
        return NULL;
    }
    char* last_slash = strrchr(path, '/');
    if (last_slash == NULL || last_slash == path) {
        return NULL;
    }
    size_t parent_len = last_slash - path;
    char* parent = (char*)malloc(parent_len + 1);
    if (parent == NULL) {
        return NULL;
    }
    strncpy(parent, path, parent_len);
    parent[parent_len] = '\0';
    return parent;
}

static int makedirs(const char* path) {
    struct stat st;
    if (stat(path, &st) == 0) {
        return 0;
    }
    char* parent_path = get_parent_path(path);
    if (parent_path != NULL && *parent_path != '\0') {
        if (makedirs(parent_path) != 0) {
            free(parent_path);
            return -1;
        }
        free(parent_path);
    } else if (parent_path != NULL) {
        free(parent_path);
    }
    if (mkdir(path, 0755) != 0) {
        fprintf(stderr, "! Error: web2c error: mkdir '%s' failed: %s\n", path, strerror(errno));
        return -1;
    }
    return 0;
}
void recorder_record_input(const_string name) {}

void recorder_record_output(const_string name) {}

void recorder_change_filename(string new_name) {}

boolean open_input(FILE **f_ptr, int filefmt, const_string fopen_mode) {
  string fname = NULL;

  // printf("open input %s\n", nameoffile + 1);

  *f_ptr = NULL;
  if (fullnameoffile) {
    free(fullnameoffile);
  }
  fullnameoffile = NULL;
  /* Look in -output-directory first, if the filename is not
     absolute.  This is because .aux and other such files will get
     written to the output directory, and we have to be able to read
     them from there.  We only look for the name as-is.  */

  if (output_directory && !kpse_absolute_p(nameoffile + 1, false)) {

    fname = concat3(output_directory, "/", nameoffile + 1);
    *f_ptr = fopen(fname, fopen_mode);

    /*
        if fname is a directory, discard it.
    */
    if (*f_ptr && dir_p(fname)) {
      fclose(*f_ptr);
      *f_ptr = NULL;
    }

    if (*f_ptr) {
      free(nameoffile);
      namelength = strlen(fname);
      nameoffile = xmalloc(namelength + 2);
      strcpy(nameoffile + 1, fname);
      fullnameoffile = fname;
    } else {
      free(fname);
    }
  }

  /* No file means do the normal search. */
  if (*f_ptr == NULL) {
    /* A negative FILEFMT means don't use a path.  */
    if (filefmt < 0) {
      /* no_file_path, for BibTeX .aux files and MetaPost things.  */
      *f_ptr = fopen(nameoffile + 1, fopen_mode);
      /* FIXME... fullnameoffile = xstrdup(nameoffile + 1); */
    } else {

      boolean must_exist;
      must_exist = (filefmt != kpse_tex_format || texinputtype) &&
                   (filefmt != kpse_vf_format);
      fname = kpse_find_file(nameoffile + 1, (kpse_file_format_type)filefmt,
                             must_exist);
      if (fname) {
        fullnameoffile = xstrdup(fname);
        /* If we found the file in the current directory, don't leave
           the `./' at the beginning of `nameoffile', since it looks
           dumb when `tex foo' says `(./foo.tex ... )'.  On the other
           hand, if the user said `tex ./foo', and that's what we
           opened, then keep it -- the user specified it, so we
           shouldn't remove it.  */
        if (fname[0] == '.' && IS_DIR_SEP(fname[1]) &&
            (nameoffile[1] != '.' || !IS_DIR_SEP(nameoffile[2]))) {
          unsigned i = 0;
          while (fname[i + 2] != 0) {
            fname[i] = fname[i + 2];
            i++;
          }
          fname[i] = 0;
        }
        *f_ptr = xfopen(fname, fopen_mode);

        /* kpse_find_file always returns a new string. */
        free(nameoffile);
        namelength = strlen(fname);
        nameoffile = xmalloc(namelength + 2);
        strcpy(nameoffile + 1, fname);
        free(fname);
      }
    }
  }

  if (*f_ptr) {
    recorder_record_input(nameoffile + 1);

    if (filefmt == kpse_tfm_format) {
      tfmtemp = getc(*f_ptr);
    } else if (filefmt == kpse_ofm_format) {
      tfmtemp = getc(*f_ptr);
    }
  }

  return *f_ptr != NULL;
}

boolean open_output(FILE **f_ptr, const_string fopen_mode) {
  string fname;
  boolean absolute = kpse_absolute_p(nameoffile + 1, false);

  /* If we have an explicit output directory, use it. */
  if (output_directory && !absolute) {
    fname = concat3(output_directory, "/", nameoffile + 1);
  } else {
    fname = nameoffile + 1;
  }

  const char* parentPath = get_parent_path(fname);
  if (parentPath != NULL) makedirs(parentPath);
  /* Is the filename openable as given?  */
  *f_ptr = fopen(fname, fopen_mode);

  /* If this succeeded, change nameoffile accordingly.  */
  if (*f_ptr) {
    if ((char *)fname != (char *)nameoffile + 1) {
      free(nameoffile);
      namelength = strlen(fname);
      nameoffile = xmalloc(namelength + 2);
      strcpy(nameoffile + 1, fname);
    }
    recorder_record_output(fname);
  }
  if ((char *)fname != (char *)nameoffile + 1) {
    free(fname);
  }
  return *f_ptr != NULL;
}

void close_file(FILE *f) {
  if (!f)
    return;
  xfclose(f, "closefile");
}
