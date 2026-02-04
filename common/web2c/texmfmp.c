#ifdef PDFTEXWASM
#define EXTERN /* Instantiate data from pdftexd.h here.  */
#include <pdftexd.h>
#include <pdftexextra.h>
const char *ptexbanner = BANNER;
#elif defined(XETEXWASM)
#define EXTERN /* Instantiate data from pdftexd.h here.  */
#include <xetexd.h>
#else
#error "compiler error"
#endif
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
#define DIGEST_SIZE 16
#define FILE_BUF_SIZE 1024
int ac;
char **av;
string translate_filename;
const_string c_job_name;
char start_time_str[32];
static char *last_source_name;
static int last_lineno;
static char *cstrbuf = NULL;
static int allocsize;
const char* bootstrapcmd;
jmp_buf jmpenv;
#define check_nprintf(size_get, size_want)                                     \
  if ((unsigned)(size_get) >= (unsigned)(size_want)) {                         \
    fprintf(stderr, "snprintf failed: file %s, line %d", __FILE__, __LINE__);  \
    abort();                                                                   \
  }
int exit_code;

void uexitbody(int type, int code, const char* file, int line) {
  const char* fileAbs = NULL;
#ifdef XeTeX
  fileAbs = strstr(file, "xetex.wasm");
#elif defined(pdfTeX)
  fileAbs = strstr(file, "pdftex.wasm");
#else
#	error "unknown compiler"
#endif
  if (fileAbs == NULL) fileAbs = strstr(file, "common");
  if (fileAbs == NULL) fileAbs = strstr(file, "src");
  if (fileAbs == NULL) fileAbs = file;
  switch (type)
  {
  case UEXIT_TAG:
    if (code != 0) fprintf(stderr, "[WASM ENGINE] uexit(%d)@%s:%d\n", code, fileAbs, line);
    break;
  case ABORT_TAG:
    fprintf(stderr, "! Error: Call abort():\nAt %s:%d\n\n", fileAbs, line);
    code = 0x401;
    break;
  case EXIT_TAG:
    if (code != 0) fprintf(stderr, "! Error: Call exit(%d):\nAt %s:%d\n\n", code, fileAbs, line);
    break;
  case STOP_TAG:
    if (code != 0) fprintf(stderr, "! Error: Compile engine stop(%d):\nAt %s:%d\n\n", code, fileAbs, line);
    break;
  default:
    fprintf(stderr, "! Error: Call uexitbody() for unknown tag\n");
    code = 0x402;
    break;
  }
  exit_code = code;
  longjmp(jmpenv, 1);
}
boolean texmfyesno(const_string var)
{
  return 0;
}
void topenin(void) {

  buffer[first] = 0;
  const unsigned char *ptr = bootstrapcmd;
  int k = first;
#ifdef XeTeX
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
  bootstrapcmd = NULL;
  for (last = first; buffer[last]; ++last) {
    
  }
  #define IS_SPC_OR_EOL(c) ((c) == ' ' || (c) == '\r' || (c) == '\n')
  for (--last; last >= first && IS_SPC_OR_EOL (buffer[last]); --last) 
    ;
  last++;
}

int _compile() {
  haltonerrorp = 0;
  output_directory = "/output";
#ifdef XeTeX
  const char *DEFAULT_FMT_NAME = " stellarlatexxetex.fmt";
  dumpname = "stellarlatex";
  if (strcmp(bootstrapcmd, "*xelatex.ini") == 0) { iniversion = 1; }
  else { nopdfoutput = 1; }
#elif defined(pdfTeX)
  const char *DEFAULT_FMT_NAME = " stellarlatexpdftex.fmt";
  dumpname = "stellarlatex";
  if (strcmp(bootstrapcmd, "*pdflatex.ini") == 0) { iniversion = 1; }
#else
#	error "unknown compiler"
#endif
  int fmtstrlen = strlen(DEFAULT_FMT_NAME);
  TEXformatdefault = xmalloc(fmtstrlen + 2);
  memcpy(TEXformatdefault, DEFAULT_FMT_NAME, fmtstrlen);
  formatdefaultlength = strlen(TEXformatdefault + 1);
  interactionoption = 1;
  synctexoption = 1;
  filelineerrorstylep = 0;
  parsefirstlinep = 0;
  // Go
  if (setjmp(jmpenv) == 0)
    mainbody();

  // printf("Compile stop with %d\n", exit_code);
  return exit_code;
}

static int compare_paths(const_string p1, const_string p2) {
  int ret;
  while ((((ret = (*p1 - *p2)) == 0) && (*p2 != 0))

         || (IS_DIR_SEP(*p1) && IS_DIR_SEP(*p2))) {
    p1++, p2++;
  }
  ret = (ret < 0 ? -1 : (ret > 0 ? 1 : 0));
  return ret;
}

void readtcxfile(void) {}

void do_undump(char *p, int item_size, int nitems, gzFile in_file) {
  if (gzread (in_file, p, item_size * nitems) != item_size * nitems) {
    fprintf(stderr, "Could not undump %d %d-byte item(s) from %s", nitems,
            item_size, nameoffile + 1);
    abort();
  }
}

void do_dump(char *p, int item_size, int nitems, gzFile out_file) {
  if (gzwrite (out_file, p, item_size * nitems) != item_size * nitems) {
    fprintf(stderr, "! Could not write %d %d-byte item(s) to %s.\n", nitems,
            item_size, nameoffile + 1);
    abort();
  }
}

boolean isnewsource(strnumber srcfilename, int lineno) {
  char *name = gettexstring(srcfilename);
  return (compare_paths(name, last_source_name) != 0 || lineno != last_lineno);
}
#if !defined(XeTeX)
char *makecstring(integer s) {

  char *p;

  int allocgrow, i, l = strstart[s + 1] - strstart[s];
  if ((unsigned)(l + 1) > (unsigned)(MAX_CSTRING_LEN)) {
    fprintf(stderr, "buffer overflow at file %s, line %d", __FILE__, __LINE__);
    abort();
  }

  if (cstrbuf == NULL) {
    allocsize = l + 1;
    cstrbuf = xmallocarray(char, allocsize);
  } else if (l + 1 > allocsize) {
    allocgrow = allocsize * 0.2;
    if (l + 1 - allocgrow > allocsize)
      allocsize = l + 1;
    else if (allocsize < MAX_CSTRING_LEN - allocgrow)
      allocsize += allocgrow;
    else
      allocsize = MAX_CSTRING_LEN;
    cstrbuf = xreallocarray(cstrbuf, char, allocsize);
  }
  p = cstrbuf;
  for (i = 0; i < l; i++)
    *p++ = strpool[i + strstart[s]];
  *p = 0;
  return cstrbuf;
}
char *makecfilename(integer s) {
  char *name = makecstring(s);
  char *p = name;
  char *q = name;

  while (*p) {
    if (*p != '"')
      *q++ = *p;
    p++;
  }
  *q = '\0';
  return name;
}
#endif


void maketimestr(char *time_str) {
  time_t start_time = time((time_t *)NULL);
  struct tm lt;
  lt = *localtime(&start_time);
  size_t size = strftime(time_str, 31, "D:%Y%m%d%H%M%S", &lt);

  if (size == 0) {
    time_str[0] = '\0';
    return;
  }

  if (time_str[14] == '6') {
    time_str[14] = '5';
    time_str[15] = '9';
    time_str[16] = '\0'; /* for safety */
  }

  time_str[size++] = 'Z';
  time_str[size] = 0;
}

void initstarttime() {
  if (start_time_str[0] == '\0') {
    maketimestr(start_time_str);
  }
}

void getcreationdate(void) {
  size_t len;

  initstarttime();
  /* put creation date on top of string pool and update poolptr */
  len = strlen(start_time_str);
  if ((unsigned)(poolptr + len) >= (unsigned)(poolsize)) {
    poolptr = poolsize;
    /* error by str_toks that calls str_room(1) */
    return;
  }
  memcpy(&strpool[poolptr], start_time_str, len);
  poolptr += len;
}

void getfilemoddate(integer s) {
  struct stat file_data;

  char *file_name = find_input_file(s);
  if (file_name == NULL) {
    return; /* empty string */
  }

  recorder_record_input(file_name);
  /* get file status */

  if (stat(file_name, &file_data) == 0) {

    size_t len;
    char time_str[32];
    maketimestr(time_str);
    len = strlen(time_str);
    if ((unsigned)(poolptr + len) >= (unsigned)(poolsize)) {
      poolptr = poolsize;
      /* error by str_toks that calls str_room(1) */
    } else {
#if defined(XeTeX)
        for (int i = 0; i < len; i++)
            strpool[poolptr++] = (uint16_t)time_str[i];
#else
        memcpy(&strpool[poolptr], time_str, len);
        poolptr += len;
#endif
    }
  }
  /* else { errno contains error code } */

  free(file_name);
}

void getfilesize(integer s) {
  struct stat file_data;
  int i;
  char *file_name = find_input_file(s);
  if (file_name == NULL) {
    return; /* empty string */
  }

  recorder_record_input(file_name);
  /* get file status */

  if (stat(file_name, &file_data) == 0) {

    size_t len;
    char buf[20];
    /* st_size has type off_t */
    i = snprintf(buf, sizeof(buf), "%lu", (long unsigned int)file_data.st_size);
    len = strlen(buf);
    if ((unsigned)(poolptr + len) >= (unsigned)(poolsize)) {
      poolptr = poolsize;
      /* error by str_toks that calls str_room(1) */
    } else {
#if defined(XeTeX)
        for (i = 0; i < len; i++)
            strpool[poolptr++] = (uint16_t)buf[i];
#else
        memcpy(&strpool[poolptr], buf, len);
        poolptr += len;
#endif
    }
  }
  /* else { errno contains error code } */

  free(file_name);
}

void getfiledump(integer s, int offset, int length) {
  FILE *f;
  int read, i;
#if defined(XeTeX)
    unsigned char *readbuffer;
    char strbuf[3];
    int j, k;
#elif defined(pdfTeX)
    poolpointer data_ptr;
    poolpointer data_end;
#else
#	error "unknown compiler"
#endif
	char* file_name;

	if (length == 0) {
		/* empty result string */
		return;
	}

	if (poolptr + 2 * length + 1 >= poolsize) {
		/* no place for result */
		poolptr = poolsize;
		/* error by str_toks that calls str_room(1) */
		return;
	}

	file_name = find_input_file(s);
	if (file_name == NULL) { return; /* empty string */ }

	/* read file data */
	f = fopen(file_name, FOPEN_RBIN_MODE);
	if (f == NULL) {
		free(file_name);
		return;
	}
	recorder_record_input(file_name);
	if (fseek(f, offset, SEEK_SET) != 0) {
		free(file_name);
		return;
	}
#if defined(XeTeX)
    readbuffer = (unsigned char *)xmalloc (length + 1);
    read = fread(readbuffer, sizeof(char), length, f);
    fclose(f);
    for (j = 0; j < read; j++) {
        i = snprintf (strbuf, 3, "%.2X", (unsigned int)readbuffer[j]);
        check_nprintf(i, 3);
        for (k = 0; k < i; k++)
            strpool[poolptr++] = (uint16_t)strbuf[k];
    }
    xfree (readbuffer);
#elif defined(pdfTeX)
    /* there is enough space in the string pool, the read
       data are put in the upper half of the result, thus
       the conversion to hex can be done without overwriting
       unconverted bytes. */
    data_ptr = poolptr + length;
    read = fread(&strpool[data_ptr], sizeof(char), length, f);
    fclose(f);

    /* convert to hex */
    data_end = data_ptr + read;
    for (; data_ptr < data_end; data_ptr++) {
        i = snprintf((char *) &strpool[poolptr], 3,
                     "%.2X", (unsigned int) strpool[data_ptr]);
        check_nprintf(i, 3);
        poolptr += i;
    }
#else
#error "unknown compiler"
#endif
  free(file_name);
}
void convertStringToHexString(const char *in, char *out, int lin) {
  int i, j, k;
  char buf[3];
  j = 0;
  for (i = 0; i < lin; i++) {
    k = snprintf(buf, sizeof(buf), "%02X", (unsigned int)(unsigned char)in[i]);
    out[j++] = buf[0];
    out[j++] = buf[1];
  }
  out[j] = '\0';
}

void getmd5sum(strnumber s, boolean file) {
  md5_state_t state;
  md5_byte_t digest[DIGEST_SIZE];
  char outbuf[2 * DIGEST_SIZE + 1];
  int len = 2 * DIGEST_SIZE;
#if defined(XeTeX)
    char *xname;
    int i;
#endif

  if (file) {
    char file_buf[FILE_BUF_SIZE];
    int read = 0;
    FILE *f;
    char *file_name;
    file_name = find_input_file(s);
    if (file_name == NULL) {
      return; /* empty string */
    }
    if (!kpse_in_name_ok(file_name)) {
      return; /* no permission */
    }

    /* in case of error the empty string is returned,
       no need for xfopen that aborts on error.
     */
    f = fopen(file_name, FOPEN_RBIN_MODE);
    if (f == NULL) {
      free(file_name);
      return;
    }
    recorder_record_input(file_name);
    md5_init(&state);
    while ((read = fread(&file_buf, sizeof(char), FILE_BUF_SIZE, f)) > 0) {
      md5_append(&state, (const md5_byte_t *)file_buf, read);
    }
    md5_finish(&state, digest);
    fclose(f);

    free(file_name);
  } else {
    /* s contains the data */
    md5_init(&state);
#if defined(XeTeX)
        xname = gettexstring (s);
        md5_append(&state,
                   (md5_byte_t *) xname,
                   strlen (xname));
        xfree (xname);
#else
        md5_append(&state,
                   (md5_byte_t *) &strpool[strstart[s]],
                   strstart[s + 1] - strstart[s]);
#endif
        md5_finish(&state, digest);
  }


  if (poolptr + len >= poolsize) {
    /* error by str_toks that calls str_room(1) */
    return;
  }
  convertStringToHexString((char *)digest, outbuf, DIGEST_SIZE);
#if defined(XeTeX) || IS_pTeX
    for (i = 0; i < 2 * DIGEST_SIZE; i++)
        strpool[poolptr++] = (uint16_t)outbuf[i];
#else
    memcpy(&strpool[poolptr], outbuf, len);
    poolptr += len;
#endif
}

#if defined(XeTeX)
static void checkpoolpointer(poolpointer poolptr, size_t len) {
  if (poolptr + len >= poolsize) {
    fprintf(stderr, "\nstring pool overflow [%i bytes]\n",
            (int)poolsize); /* fixme */
    exit(1);
  }
}

int maketexstring(const_string s) {
  size_t len;

  UInt32 rval;
  const unsigned char *cp = (const unsigned char *)s;

  if (s == NULL || *s == 0)
    return getnullstr();

  len = strlen(s);
  checkpoolpointer(poolptr,
                   len); /* in the XeTeX case, this may be more than enough */

  while ((rval = *(cp++)) != 0) {
    UInt16 extraBytes = bytesFromUTF8[rval];
    switch (extraBytes) { /* note: code falls through cases! */
    case 5:
      rval <<= 6;
      if (*cp)
        rval += *(cp++);
    case 4:
      rval <<= 6;
      if (*cp)
        rval += *(cp++);
    case 3:
      rval <<= 6;
      if (*cp)
        rval += *(cp++);
    case 2:
      rval <<= 6;
      if (*cp)
        rval += *(cp++);
    case 1:
      rval <<= 6;
      if (*cp)
        rval += *(cp++);
    case 0:;
    };
    rval -= offsetsFromUTF8[extraBytes];
    if (rval > 0xffff) {
      rval -= 0x10000;
      strpool[poolptr++] = 0xd800 + rval / 0x0400;
      strpool[poolptr++] = 0xdc00 + rval % 0x0400;
    } else
      strpool[poolptr++] = rval;
  }

  return makestring();
}
#endif
strnumber makefullnamestring(void) { return maketexstring(fullnameoffile); }

strnumber getjobname(strnumber name) {
  strnumber ret = name;
  if (c_job_name != NULL)
    ret = maketexstring(c_job_name);
  return ret;
}

int runsystem(const char *noused) { return 0; }

void get_seconds_and_micros(integer *seconds, integer *micros) {

  struct timeval tv;
  gettimeofday(&tv, NULL);
  *seconds = tv.tv_sec;
  *micros = tv.tv_usec;
}
void calledit(packedASCIIcode *filename, poolpointer fnstart, integer fnlength,
              integer linenumber) {
  fprintf(stderr, "Never calledit.. aborting\n");
#ifdef pdfTeX
  for (int i = 1; i <= inopen; i++)
    xfclose(inputfile[i], "inputfile");
#endif
  exit(1);
}

void get_date_and_time(integer *minutes, integer *day, integer *month,
                       integer *year) {
  struct tm *tmptr;

  /* whether the envvar was not set (usual case) or invalid,
     use current time.  */
  time_t myclock = time((time_t *)0);
  tmptr = localtime(&myclock);

  *minutes = tmptr->tm_hour * 60 + tmptr->tm_min;
  *day = tmptr->tm_mday;
  *month = tmptr->tm_mon + 1;
  *year = tmptr->tm_year + 1900;
}

#ifdef XeTeX
string gettexstring(strnumber s) {
  unsigned bytesToWrite = 0;
  poolpointer len, i, j;
  string name;
  if (s >= 65536L)
    len = strstart[s + 1 - 65536L] - strstart[s - 65536L];
  else
    len = 0;
  name = xmalloc(len * 3 + 1); /* max UTF16->UTF8 expansion
                                  (code units, not bytes) */
  for (i = 0, j = 0; i < len; i++) {
    unsigned c = strpool[i + strstart[s - 65536L]];
    if (c >= 0xD800 && c <= 0xDBFF) {
      unsigned lo = strpool[++i + strstart[s - 65536L]];
      if (lo >= 0xDC00 && lo <= 0xDFFF)
        c = (c - 0xD800) * 0x0400 + lo - 0xDC00;
      else
        c = 0xFFFD;
    }
    if (c < 0x80)
      bytesToWrite = 1;
    else if (c < 0x800)
      bytesToWrite = 2;
    else if (c < 0x10000)
      bytesToWrite = 3;
    else if (c < 0x110000)
      bytesToWrite = 4;
    else {
      bytesToWrite = 3;
      c = 0xFFFD;
    }

    j += bytesToWrite;
    switch (bytesToWrite) { /* note: everything falls through. */
    case 4:
      name[--j] = ((c | 0x80) & 0xBF);
      c >>= 6;
    case 3:
      name[--j] = ((c | 0x80) & 0xBF);
      c >>= 6;
    case 2:
      name[--j] = ((c | 0x80) & 0xBF);
      c >>= 6;
    case 1:
      name[--j] = (c | firstByteMark[bytesToWrite]);
    }
    j += bytesToWrite;
  }
  name[j] = 0;
  return name;
}
#elif defined(pdfTeX)
string gettexstring(strnumber s) {
  poolpointer len;
  string name;
  len = strstart[s + 1] - strstart[s];
  name = (string)xmalloc(len + 1);
  strncpy(name, (string)&strpool[strstart[s]], len);
  name[len] = 0;
  return name;
}
#else
#error "unknown compiler"
#endif

void remembersourceinfo(strnumber srcfilename, int lineno) {
  if (last_source_name) {
    free(last_source_name);
  }
  last_source_name = gettexstring(srcfilename);
  last_lineno = lineno;
}

poolpointer makesrcspecial(strnumber srcfilename, int lineno) {
  poolpointer oldpoolptr = poolptr;
  char *filename = gettexstring(srcfilename);
  /* FIXME: Magic number. */
  char buf[40];
  char *s = buf;

  /* Always put a space after the number, which makes things easier
   * to parse.
   */
  sprintf(buf, "src:%d ", lineno);

  if (poolptr + strlen(buf) + strlen(filename) >= (size_t)poolsize) {
    fprintf(stderr, "\nstring pool overflow\n"); /* fixme */
    exit(1);
  }
  s = buf;
  while (*s)
    strpool[poolptr++] = *s++;

  s = filename;
  while (*s)
    strpool[poolptr++] = *s++;

  return (oldpoolptr);
}
string
find_input_file(integer s)
{
    string filename;

#if defined(XeTeX)
    filename = gettexstring(s);
#elif defined(pdfTeX)
    filename = makecfilename(s);
#else
#error "unknown compiler"
#endif
    /* Look in -output-directory first, if the filename is not
       absolute.  This is because we want the pdf* functions to
       be able to find the same files as \openin */
    if (output_directory && !kpse_absolute_p (filename, false)) {
        string pathname;

        pathname = concat3(output_directory, DIR_SEP_STRING, filename);
        if (!access(pathname, R_OK) && !dir_p (pathname)) {
            return pathname;
        }
        xfree (pathname);
    }
    return kpse_find_tex(filename);
}

char * generic_synctex_get_current_name (void)
{
  char *pwdbuf, *ret;
  if (!fullnameoffile) {
    ret = xstrdup("");
    return ret;
  }
  if (kpse_absolute_p(fullnameoffile, false)) {
     return xstrdup(fullnameoffile);
  }
  pwdbuf = xgetcwd();
  ret = concat3(pwdbuf, DIR_SEP_STRING, fullnameoffile);
  free(pwdbuf) ;
  return ret;
}
#ifndef XeTeX
boolean input_line(FILE *f) {
  // printf("%p\n", f);
  int i = EOF;

  /* Recognize either LF or CR as a line terminator.  */

  last = first;
  while (last < bufsize && (i = getc(f)) != EOF && i != '\n' && i != '\r')
    buffer[last++] = i;

  if (i == EOF && errno != EINTR && last == first)
    return false;

  /* We didn't get the whole line because our buffer was too small.  */
  if (i != EOF && i != '\n' && i != '\r') {
    fprintf(stderr, "! Unable to read an entire line---bufsize=%u.\n",
            (unsigned)bufsize);
    abort();
  }

  buffer[last] = ' ';
  if (last >= maxbufstack)
    maxbufstack = last;

  /* If next char is LF of a CRLF, read it.  */
  if (i == '\r') {
    while ((i = getc(f)) == EOF && errno == EINTR)
      ;
    if (i != '\n')
      ungetc(i, f);
  }

  while (last > first && buffer[last - 1] == ' ')
    --last;

  return true;
}
#endif
