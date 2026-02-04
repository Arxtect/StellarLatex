#ifndef CPASCAL_H
#define CPASCAL_H
// number
#define	Xchr(x) xchr[x]
#define incr(x) ++(x)
#define decr(x) --(x)
#define chr(x)		(x)
#define ord(x)		(x)
#define odd(x)		((x) & 1)
// #define round(x)	zround ((double) (x)) // for llvm math.h have round(x)
// #define trunc(x)	((integer) (x)) // for llvm math.h have trunc(x)
#define maxint INTEGER_MAX
#define nil NULL

#define addressof(x) (&(x))

// file
#define aopenin(f, p) open_input(&(f), p, FOPEN_RBIN_MODE)
#define aopenout(f) open_output(&(f), FOPEN_WBIN_MODE)
#define aclose close_file
#define WRITE_OUT(a, b)             \
  if ((size_t) fwrite ((char *) &OUT_BUF[a], sizeof (OUT_BUF[a]),       \
                    (size_t) ((size_t)(b) - (size_t)(a) + 1), OUT_FILE) \
      != (size_t) ((size_t) (b) - (size_t) (a) + 1))                    \
    fprintf (stderr, "fwrite failed");

#define putbyte(x, f)                                                                    \
	do {                                                                                 \
		if (putc((char)(x) & 255, f) == EOF)                                             \
			fprintf(stderr, "putbyte(%ld) failed", (long)x);                             \
	} while (0)
#define ucharcast(x) ((unsigned char) (x))
#define int64cast(x) ((integer64) (x))
#define stringcast(x) ((string) (x))
#define conststringcast(x) ((const_string) (x))
#define ustringcast(x) ((unsigned char *) (x))

#define Fputs(f, s) (void)fputs(s, f)
#define promptfilenamehelpmsg "(Press Enter to retry, or Control-D to exit"

#define printcstring(STR)                                                                \
	do {                                                                                 \
		const_string ch_ptr = (STR);                                                     \
		while (*ch_ptr) printchar(*(ch_ptr++));                                          \
	} while (0)

extern int	loadpoolstrings(integer);
#endif
