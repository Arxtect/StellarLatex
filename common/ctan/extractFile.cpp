#include <archive.h>
#include <archive_entry.h>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <string>
#include "extractFile.hpp"
namespace extractor {
bool tar_xz(const char* archive_path, const char* target_file, const char* output_path) {
	// std::cerr << "extracting " << target_file << " from " << archive_path << std::endl;
	struct archive*		  a = archive_read_new();
	struct archive_entry* entry;
	archive_read_support_filter_xz(a);
	archive_read_support_format_tar(a);
	if (archive_read_open_filename(a, archive_path, 10240) != ARCHIVE_OK) {
		std::cerr << "Error opening archive: " << archive_error_string(a) << std::endl;
		return -1;
	}
	while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
		const char* current_file = archive_entry_pathname(entry);
		if (strcmp(current_file, target_file) == 0) {
			archive_entry_set_pathname(entry, output_path);
			if (archive_read_extract(a, entry, 0) != ARCHIVE_OK) {
				// std::cerr << "Extraction failed: " << archive_error_string(a)
				// 		  << std::endl;
				archive_read_free(a);
				return -1;
			}
			// std::cerr << "Successfully extracted: " << current_file << std::endl;
			archive_read_free(a);
			return true;
		}
		archive_read_data_skip(a);
	}
	std::cerr << "File not found in archive: " << target_file << std::endl;
	return false;
}

bool xz(const char* archive_path, const char* output_path) {
	std::cerr << "extracting from " << archive_path << std::endl;
	struct archive* a = archive_read_new();
	archive_read_support_filter_xz(a);
	archive_read_support_format_raw(a);
	if (archive_read_open_filename(a, archive_path, 10240) != ARCHIVE_OK) {
		std::cerr << "Error opening stdin: " << archive_error_string(a) << std::endl;
		return false;
	}
	struct archive_entry* entry;
	if (archive_read_next_header(a, &entry) != ARCHIVE_OK) {
		std::cerr << "Error reading header: " << archive_error_string(a) << std::endl;
		return false;
	}
	const void* buff;
	size_t		size;
	la_int64_t	offset;
	FILE*		fp = fopen(output_path, "wb");
	if (fp == nullptr) {
		std::cerr << "Error opening output file: " << output_path << std::endl;
		return false;
	}
	while (archive_read_data_block(a, &buff, &size, &offset) == ARCHIVE_OK) {
		fwrite(buff, 1, size, fp);
	}
	archive_read_free(a);
	fclose(fp);
	return true;
}
}  // namespace extractor
