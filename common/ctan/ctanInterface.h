#ifndef CTAN_INTERFACE_HEADER
#define CTAN_INTERFACE_HEADER

#include <kpathsea/type.h>
/**
 * @brief get file from ctan server
 * 
 * @param request_name 
 * @param type 
 * @return null for fail, else file path
 */
#ifdef __cplusplus
extern "C"
#endif
char* ctan_get_file(const char* request_name, kpse_file_format_type type);
#endif
