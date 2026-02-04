#ifndef W2CEMUHEADER
#define W2CEMUHEADER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
typedef int integer;
typedef int boolean;
typedef long longinteger;
typedef const char* constcstring;
typedef char* cstring;
typedef int cinttype;
typedef signed char schar;
typedef char* string;
typedef const char* const_string;
typedef FILE* text;
typedef double real;
typedef double glueratio;
typedef long long longword;
#define false 0
#define true 1

#ifdef __cplusplus
extern "C" {
#endif
#include <memory/xmemory.h>
#include <kpathsea/type.h>
#include <kpathsea/kpathsea.h>
#ifdef __cplusplus
}
#endif

#define FOPEN_W_MODE "wb"
#define FOPEN_R_MODE "rb"
#define FOPEN_RBIN_MODE "rb"
#define FOPEN_WBIN_MODE "wb"

#define LONGINTEGER_TYPE long
#define LONGINTEGER_PRI "l"

#define INTEGER_TYPE int
#define INTEGER_MAX INT_MAX
#define INTEGER_MIN INT_MIN

// version
#define ARXTECT_VERSION_STRING __DATE__
#define WEB2C_NORETURN
#ifdef __cplusplus
extern "C"
#endif
void uexitbody(int type, int code, const char* file, int line);
#define UEXIT_TAG 0x83726001 /* a random code */
#define ABORT_TAG 0x83726002 /* a random code */
#define EXIT_TAG 0x83726003 /* a random code */
#define STOP_TAG 0x83726004 /* a random code */
#define uexit(code) uexitbody(UEXIT_TAG, code, __FILE__, __LINE__)
#define abort() uexitbody(ABORT_TAG, 0, __FILE__, __LINE__)
#define exit(i) uexitbody(EXIT_TAG, i, __FILE__, __LINE__)
#define comp_stop(i) uexitbody(STOP_TAG, i, __FILE__, __LINE__)

#endif
