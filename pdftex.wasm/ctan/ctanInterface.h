#ifndef CTAN_INTERFACE_HEADER
#define CTAN_INTERFACE_HEADER

#include <texmfmp.h>
/**
 * @brief get file from ctan server
 * 
 * @param request_name 
 * @param type 
 * @return 0 for success, 1 for fail
 */
extern char* ctan_get_file(const char* request_name, kpse_file_format_type type);
#endif
