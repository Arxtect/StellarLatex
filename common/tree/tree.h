#ifndef _TREE_H_
#define _TREE_H_ 
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif
void tree_dir(const char* path, FILE* fp);
void lsdir(const char* path, FILE* fp);
#ifdef __cplusplus
}
#endif
#endif
