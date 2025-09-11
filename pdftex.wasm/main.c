#define EXTERN /* Instantiate data from pdftexd.h here.  */

#include <pdftexd.h>
#include <pdftexextra.h>

#include <errno.h>
#include <md5/md5.h>
#include <setjmp.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/un.h>
#include <time.h>
#include <unistd.h>
#include <libgen.h>
#include <bibtex/bibtex.h>
#include <cbiber.h>
#include <makeindexk/makeindex.h>
#include <tree/tree.h>

int ac;
char **av;
const char *ptexbanner = BANNER;
const char *DEFAULT_FMT_NAME = " swiftlatexpdftex.fmt";
const char *DEFAULT_DUMP_NAME = "swiftlatexpdftex";
string versionstring = " (Arxtect PDFTeX " ARXTECT_VERSION_STRING ")";
#define MAXMAINFILENAME 512
char bootstrapcmd[MAXMAINFILENAME] = {0};
int exit_code;
jmp_buf jmpenv;

void topenin(void) {

  buffer[first] = 0;
  char *ptr = bootstrapcmd;
  int k = first;
#ifdef XETEXWASM
  UInt32 rval;
  while ((rval = *(ptr++)) != 0) {
    UInt16 extraBytes = bytesFromUTF8[rval];
    switch (extraBytes) { /* note: code falls through cases! */
      case 5: rval <<= 6; if (*ptr) rval += *(ptr++);
      case 4: rval <<= 6; if (*ptr) rval += *(ptr++);
      case 3: rval <<= 6; if (*ptr) rval += *(ptr++);
      case 2: rval <<= 6; if (*ptr) rval += *(ptr++);
      case 1: rval <<= 6; if (*ptr) rval += *(ptr++);
      case 0: ;
    };
    rval -= offsetsFromUTF8[extraBytes];
    buffer[k++] = rval;
  }
#else
  while (*ptr) {
    buffer[k++] = *(ptr++);
  }
#endif
  buffer[k++] = ' ';
  buffer[k] = 0;
  bootstrapcmd[0] = 0;
  for (last = first; buffer[last]; ++last) {
    
  }
  #define IS_SPC_OR_EOL(c) ((c) == ' ' || (c) == '\r' || (c) == '\n')
  for (--last; last >= first && IS_SPC_OR_EOL (buffer[last]); --last) 
    ;
  last++;
}

void uexit(int code) {
  exit_code = code;
  longjmp(jmpenv, 1);
}
boolean
texmfyesno(const_string var)
{
  return 0;
}

#ifndef WEBASSEMBLY_BUILD
int main(int argc, char **argv) {

  haltonerrorp = 0;
  ac = argc;
  av = argv;
  // Parse Argument
  int c;
  while ((c = getopt(ac, av, "io:")) != -1)
    switch (c) {
    case 'i':
      iniversion = 1;
      strncpy(bootstrapcmd, "*pdflatex.ini", MAXMAINFILENAME);
      break;
    case 'o':
      output_directory = optarg;
      break;
  }
  
  if (iniversion != 1) {
    for (int index = optind; index < argc; index++) {
      strncpy(bootstrapcmd, argv[index], MAXMAINFILENAME);
      bootstrapcmd[MAXMAINFILENAME - 1] = 0;
      break;
    }
  }

  if (strlen(bootstrapcmd) == 0) {
    fprintf(stderr, "Usage: swiftlatex foo.tex\n");
    return -1;
  }

  dumpname = DEFAULT_DUMP_NAME;
  int fmtstrlen = strlen(DEFAULT_FMT_NAME);
  TEXformatdefault = xmalloc(fmtstrlen + 2);
  memcpy(TEXformatdefault, DEFAULT_FMT_NAME, fmtstrlen);
  formatdefaultlength = strlen(TEXformatdefault + 1);
  interactionoption = 1;
  filelineerrorstylep = 0;
  parsefirstlinep = 0;
  // Go
  if (setjmp(jmpenv) == 0)
    mainbody();

  return EXIT_SUCCESS;
}
#else

char main_entry_file[MAXMAINFILENAME];

int _compile() {
  haltonerrorp = 0;
  dumpname = DEFAULT_DUMP_NAME;
  int fmtstrlen = strlen(DEFAULT_FMT_NAME);
  TEXformatdefault = xmalloc(fmtstrlen + 2);
  memcpy(TEXformatdefault, DEFAULT_FMT_NAME, fmtstrlen);
  formatdefaultlength = strlen(TEXformatdefault + 1);
  interactionoption = 1;
  filelineerrorstylep = 0;
  parsefirstlinep = 0;
  // Go
  if (setjmp(jmpenv) == 0)
    mainbody();

  // printf("Compile stop with %d\n", exit_code);
  return exit_code;
}

int compileLaTeX() {
    if (strlen(main_entry_file) == 0) {
      return -1;
    }
    // if we see space in main_entry_file, force use the quote
    boolean have_space = 0;
    for (int index = 0; main_entry_file[index] != 0; index++) {
      if (main_entry_file[index] == ' ') {
        have_space = 1;
        break;
      }
    }
    if (have_space == 1) {
      bootstrapcmd[0] = '\"';
      strncpy(bootstrapcmd + 1, main_entry_file, MAXMAINFILENAME - 1);
      int length = strlen(bootstrapcmd);
      bootstrapcmd[length] = '\"';
      bootstrapcmd[length + 1] = 0;
    }
    else {
      strncpy(bootstrapcmd, main_entry_file, MAXMAINFILENAME);
    }
    bootstrapcmd[MAXMAINFILENAME - 1] = 0;
    char *cwd = getcwd(NULL, 0);
    char *dir = dirname(strdup(main_entry_file));
    if (strcmp(dir, ".")!=0)chdir(dir);
    int ret = _compile();
    if (strcmp(dir, ".")!=0)chdir(cwd);
    free(cwd);
    return ret;
}

int compileFormat() {
    iniversion = 1;
    strncpy(bootstrapcmd, "*pdflatex.ini", MAXMAINFILENAME);
    return _compile();
}

int compileBibLatex() {
    char main_aux_file[MAXMAINFILENAME];
    char main_bcf_file[MAXMAINFILENAME];
    char main_bbl_file[MAXMAINFILENAME];
    strncpy(main_aux_file, main_entry_file, MAXMAINFILENAME);
    strncpy(main_bcf_file, main_entry_file, MAXMAINFILENAME);
    strncpy(main_bbl_file, main_entry_file, MAXMAINFILENAME);
    main_aux_file[MAXMAINFILENAME - 1] = 0;
    main_bcf_file[MAXMAINFILENAME - 1] = 0;
    main_bbl_file[MAXMAINFILENAME - 1] = 0;
    unsigned int s_len = strlen(main_entry_file);
    if (s_len < 3) {
      return -1;
    }
    main_aux_file[s_len - 1] = 'x';
    main_aux_file[s_len - 2] = 'u';
    main_aux_file[s_len - 3] = 'a';
    main_bcf_file[s_len - 1] = 'f';
    main_bcf_file[s_len - 2] = 'c';
    main_bcf_file[s_len - 3] = 'b';
    main_bbl_file[s_len - 1] = 'l';
    main_bbl_file[s_len - 2] = 'b';
    main_bbl_file[s_len - 3] = 'b';
    if (access(main_bbl_file, F_OK) == 0) {
      // if .bbl file exists and is not empty, do nothing
      struct stat buf;
      int ret = stat(main_bbl_file, &buf);
      if (ret == 0 && buf.st_size != 0) return 0;
    }
    int biblatex_res = 0;
    if (access(main_bcf_file, F_OK) == 0) {
      // if .bcf file exists, run biber as biblatex
      biblatex_res = biber_main(main_bcf_file);
    } else {
      // if .bcf file does not exist, run bibtex as biblatex
      biblatex_res = bibtex_main(main_aux_file);
    }
    makeindex_main(main_aux_file);
    tree_dir("/", stderr);
    return biblatex_res;
}

int setMainEntry(const char *p) {
    strncpy(main_entry_file, p, MAXMAINFILENAME);
    main_entry_file[MAXMAINFILENAME - 1] = 0;
    // fprintf(stderr,"setting main entry from c %s\n", main_entry_file);
    return 0;
}

int main(int argc, char **argv) {
    printf("SwiftLaTeX Engine Loaded\n");
}

#endif
