// First of all, remove pdf_files_init/close from xetex-ini.c
// And remove picture handling functions from xetex-pic.c
#include "core-bridge.h"
#include <md5/md5.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <libgen.h>
#include "core-memory.h"
#include <localkpse/type.h>
#include <tree/tree.h>
void issue_warning(void *context, char const *text) {
    printf("%s\n", text);
}

void issue_error(void *context, char const *text) {
    printf("%s\n", text);
}

int get_file_md5(void *context, char const *path, char *digest) {

    md5_state_t state;
#define FILE_BUF_SIZE 128
    char file_buf[FILE_BUF_SIZE];
    size_t read;
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        fprintf(stderr, "This file does not exists %s\n, so returning an empty md5",
                path);
        return -1;
    }

    md5_init(&state);
    while ((read = fread(&file_buf, sizeof(char), FILE_BUF_SIZE, f)) > 0) {
        md5_append(&state, (const md5_byte_t *)file_buf, read);
    }
    md5_finish(&state, digest);
    fclose(f);
#undef FILE_BUF_SIZE
    return 0;
}
int get_data_md5(void *context, char const *data, size_t len, char *digest) {

    md5_state_t state;
    md5_init(&state);
    md5_append(&state, data, len);
    md5_finish(&state, digest);
    return 0;
}


void *output_open(void *context, char const *path, int is_gz) {
    return fopen(path, "w");
}

void *output_open_stdout(void *context) { return stdout; }

int output_putc(void *context, void *handle, int c) {
    // printf("output_putc\n");
    return fputc(c, handle);
}

size_t output_write(void *context, void *handle, const char *data, size_t len) {
    // printf("output_write\n");
    return fwrite(data, 1, len, handle);
}

int output_flush(void *context, void *handle) {
    // printf("output_fflush\n");
    return fflush(handle);
}

int output_close(void *context, void *handle) {
    return fclose(handle);
}

int _formatConvert(int format) {
    switch (format) {
    case TTIF_TFM:
        return kpse_tfm_format;
    case TTIF_AFM:
        return kpse_afm_format;
    case TTIF_BIB:
        return kpse_bib_format;
    case TTIF_BST:
        return kpse_bst_format;
    case TTIF_CNF:
        return kpse_cnf_format;
    case TTIF_FORMAT:
        return kpse_fmt_format;
    case TTIF_FONTMAP:
        return kpse_fontmap_format;
    case TTIF_OFM:
        return kpse_ofm_format;
    case TTIF_OVF:
        return kpse_ovf_format;
    case TTIF_TEX:
        return kpse_tex_format;
    case TTIF_TYPE1:
        return kpse_type1_format;
    case TTIF_VF:
        return kpse_vf_format;
    case TTIF_TRUETYPE:
        return kpse_truetype_format;
    case TTIF_ENC:
        return kpse_enc_format;
    case TTIF_CMAP:
        return kpse_cmap_format;
    case TTIF_SFD:
        return kpse_sfd_format;
    case TTIF_OPENTYPE:
        return kpse_opentype_format;
    default:
        // fprintf(stderr, "Unknown format %d\n", format);
        return kpse_tex_format;
    }
}
extern char* kpse_find_file(const char* _name, kpse_file_format_type format, bool must_exist);
void *input_open(void *context, char const *path, tt_input_format_type format,
                 int is_gz) {
    
    // fprintf(stderr, "Opening %s format %d\n", path, format);
    char *normalized_path = kpse_find_file(path, (kpse_file_format_type)_formatConvert(format), 0);
    if (normalized_path != NULL) {
        FILE *res = fopen(normalized_path, "rb");
        free(normalized_path);
        // fprintf(stderr, "Opening %s format %d pointer: %p\n", path, format, res);
        return res;
    } else {
        return NULL;
    }
}

size_t input_get_size(void *context, void *handle) {
    int fpno = fileno(handle);
    struct stat st;
    fstat(fpno, &st);
    return st.st_size;
}

size_t input_seek(void *context, void *handle, ssize_t offset, int whence,
                  int *internal_error) {

    int seek_res = fseek(handle, offset, whence);
    if (seek_res != 0) {
        fprintf(stderr, "seek failed  %d %p\n", seek_res, handle);
        *internal_error = 1;
        return -1;
    } else {
        if (whence == SEEK_SET) {
            return offset;
        }
        /* Return current file pointer */
        return ftell(handle);
    }
}

ssize_t input_read(void *context, void *handle, char *data, size_t len) {
    // printf("input_read\n");
    return fread(data, 1, len, handle);
}

int input_getc(void *context, void *handle) {
    // printf("input_getc\n");
    return fgetc(handle);
}

int input_ungetc(void *context, void *handle, int ch) {

    return ungetc(ch, handle);
}

int input_close(void *context, void *handle) { return fclose(handle); }


tt_bridge_api_t ourapi;
char main_entry_file[512];


int compilePDF(){
    char main_xdv_file[512];
    char main_pdf_file[512];
    strncpy(main_xdv_file, main_entry_file, 512);
    strncpy(main_pdf_file, main_entry_file, 512);
    int len = strlen(main_xdv_file);
    if(len < 3) return -1;
    main_xdv_file[len - 1] = 'v';
    main_xdv_file[len - 2] = 'd';
    main_xdv_file[len - 3] = 'x';
    main_pdf_file[len - 1] = 'f';
    main_pdf_file[len - 2] = 'd';
    main_pdf_file[len - 3] = 'p';
    return dvipdfmx_simple_main(&ourapi, main_xdv_file, main_pdf_file, false, false, time(0));
  // return tex_simple_main(&ourapi, "xelatex.fmt", "xelatex.ini", time(0), 1); //xelatex.fmt does not matter
}

int setMainEntry(const char *p) {
    strncpy(main_entry_file, p, 512);
    main_entry_file[511] = 0;
    return 0;
}

int main() {
    ourapi.issue_warning = issue_warning;
    ourapi.issue_error = issue_error;
    ourapi.get_file_md5 = get_file_md5;
    ourapi.get_data_md5 = get_data_md5;
    ourapi.output_open = output_open;
    ourapi.output_open_stdout = output_open_stdout;
    ourapi.output_putc = output_putc;
    ourapi.output_write = output_write;
    ourapi.output_close = output_close;
    ourapi.output_flush = output_flush;
    ourapi.input_open = input_open;
    ourapi.input_get_size = input_get_size;
    ourapi.input_seek = input_seek;
    ourapi.input_read = input_read;
    ourapi.input_getc = input_getc;
    ourapi.input_ungetc = input_ungetc;
    ourapi.input_close = input_close;
    strncpy(main_entry_file, "main.tex", 512);

    return 0;
}



