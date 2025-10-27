#ifndef W2CEMUHEADER
#define W2CEMUHEADER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <localkpse/type.h>
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
#ifndef TECTONIC_CORE_MEMORY_H
	#include <memory/xmemory.h>
#endif
	#include <localkpse/kpseemu.h>
#ifdef __cplusplus
}
#endif

#define LONGINTEGER_TYPE long
#define LONGINTEGER_PRI "l"

#define INTEGER_TYPE int
#define INTEGER_MAX INT_MAX
#define INTEGER_MIN INT_MIN

// version
#define ARXTECT_VERSION_STRING __DATE__
#define WEB2C_NORETURN
extern void uexitbody(int code, const char* file, int line);
#define uexit(code) uexitbody(code, __FILE__, __LINE__)
#define abort() uexitbody(0xbeef, __FILE__, __LINE__)

#endif
