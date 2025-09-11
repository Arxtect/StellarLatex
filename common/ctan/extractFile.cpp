#include "extractFile.hpp"
#include <archive.h>
#include <archive_entry.h>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <string>
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
bool tar_xz(std::string archive_path, std::string target_file, std::string output_path) {
	return tar_xz(archive_path.c_str(), target_file.c_str(), output_path.c_str());
}
bool tar_xz(const char* archive_path, const char* output_path) {
	// std::cerr << "extracting all files from " << archive_path << " to " << output_path << std::endl;
	struct archive*		  a = archive_read_new();
	struct archive*		  ext = archive_write_disk_new();
	struct archive_entry* entry;
	
	archive_read_support_filter_xz(a);
	archive_read_support_format_tar(a);
	archive_write_disk_set_options(ext, ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS);

	if (archive_read_open_filename(a, archive_path, 10240) != ARCHIVE_OK) {
		std::cerr << "Error opening archive: " << archive_error_string(a) << std::endl;
		archive_read_free(a);
		archive_write_free(ext);
		return false;
	}
	while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
		const char* current_file = archive_entry_pathname(entry);
		std::string new_path = std::string(output_path) + "/" + std::string(current_file);
		archive_entry_set_pathname(entry, new_path.c_str());
		int res = archive_write_header(ext, entry);
		if (res != ARCHIVE_OK) {
			std::cerr << "Extraction failed for " << current_file << ": " << archive_error_string(ext) << std::endl;
			archive_read_free(a);
			archive_write_free(ext);
			return false;
		}
		const void* buff;
		size_t		size;
		la_int64_t	offset;
		while (archive_read_data_block(a, &buff, &size, &offset) == ARCHIVE_OK) {
			archive_write_data_block(ext, buff, size, offset);
		}
		// std::cerr << "Successfully extracted: " << current_file << std::endl;
	}
	archive_read_free(a);
	archive_write_free(ext);
	return true;
}
bool tar_xz(std::string archive_path, std::string output_path) {
	return tar_xz(archive_path.c_str(), output_path.c_str());
}

bool xz(const char* archive_path, const char* output_path) {
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
bool xz(std::string archive_path, std::string output_path) {
	return xz(archive_path.c_str(), output_path.c_str());
}
}  // namespace extractor
