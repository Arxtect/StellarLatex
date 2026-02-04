#include "texmfmp.h"
#include <limits.h>
// char *backup_pool = 0;
// unsigned int backupptr = 0;
// void*  dlmalloc(size_t);
// void*  dlrealloc(void*, size_t);
// void   dlfree(void*);
void* xmalloc(size_t newsize) {
	void* ptr = malloc(newsize ? newsize : 1);
	if (!ptr) {
		fprintf(stderr, "Malloc Failed");
		abort();
	}
	memset(ptr, 0, newsize);
	// printf("malloc %p size %ld\n", ptr, newsize);
	return ptr;
}

void* xrealloc(void* oriptr, size_t newsize) {
	if (oriptr == NULL) return xmalloc(newsize);
	void* ptr = realloc(oriptr, newsize ? newsize : 1);
	if (!ptr) {
		fprintf(stderr, "Realloc Failed");
		abort();
	}
	return ptr;
}

void* xcalloc(size_t num, size_t size) {
	void* ptr = calloc(num ? num : 1, size ? size : 1);
	if (!ptr) {
		fprintf(stderr, "Realloc Failed");
		abort();
	}
	return ptr;
}

void xfree(void* ptr) {
	free(ptr);
}

string xstrdup(const_string s) {
	string new_string = (string)malloc(strlen(s) + 1);
	return strcpy(new_string, s);
}

string xgetcwd (void)
{
    char path[PATH_MAX + 1];
    if (getcwd (path, PATH_MAX + 1) == NULL) {
        return NULL;
    }
    return xstrdup (path);
}
