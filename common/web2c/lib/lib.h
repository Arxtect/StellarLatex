#ifndef LIB_LIB_H
#define LIB_LIB_H
#include <w2c/config.h>
/* openclose.c */
extern boolean open_input (FILE **, int, const_string fopen_mode);
extern boolean open_output (FILE **, const_string fopen_mode);
extern boolean open_input_with_dirname (FILE **, int, const char *);
extern void close_file (FILE *);
extern void recorder_change_filename (string);
extern void recorder_record_input (const_string);
extern void recorder_record_output (const_string);
extern boolean dir_p (string fn);
extern boolean eof (FILE *);

extern string fullnameoffile;
extern boolean recorder_enabled;
extern string output_directory;

/* setupvar.c */
extern void setupboundvariable(integer*, const_string, integer);
/* texmfmp.c */
extern boolean texmfyesno(const_string var);
/* version.c */
extern string versionstring;

#endif
