#ifndef CTAN_INTERFACE_HEADER
#define CTAN_INTERFACE_HEADER

#include <localkpse/type.h>
/**
 * @brief get file from ctan server
 * 
 * @param request_name 
 * @param type 
 * @return null for fail, else file path
 */
extern char* ctan_get_file(const char* request_name, kpse_file_format_type type);
#endif
