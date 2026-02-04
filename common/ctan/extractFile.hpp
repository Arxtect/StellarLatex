#pragma once
#include <string>
namespace extractor {
/**
 * @brief extract .tar.xz file
 * 
 * @param archive_path .tar.xz file path
 * @param target_file file path in archive_path
 * @param output_path where to write
 * @return true extract success
 * @return false extract failed
 */
bool tar_xz(const char* archive_path, const char* target_file, const char* output_path);
/**
 * @brief extract .tar.xz file
 * 
 * @param archive_path .tar.xz file path
 * @param target_file file path in archive_path
 * @param output_path where to write
 * @return true extract success
 * @return false extract failed
 */
bool tar_xz(std::string archive_path, std::string target_file, std::string output_path);
/**
 * @brief extract full .tar.xz file
 * 
 * @param archive_path .tar.xz file path
 * @param output_path where to write
 * @return true extract success
 * @return false extract failed
 */
bool tar_xz(std::string archive_path, std::string output_path);
/**
 * @brief extract full .tar.xz file
 * 
 * @param archive_path .tar.xz file path
 * @param output_path where to write
 * @return true extract success
 * @return false extract failed
 */
bool tar_xz(const char* archive_path, const char* output_path);
/**
 * @brief extract .xz file
 * 
 * @param archive_path .xz file path
 * @param output_path where to write
 * @return true extract success
 * @return false extract failed
 */
bool xz(const char* archive_path, const char* output_path);
/**
 * @brief extract .xz file
 * 
 * @param archive_path .xz file path
 * @param output_path where to write
 * @return true extract success
 * @return false extract failed
 */
bool xz(std::string archive_path, std::string output_path);
}  // namespace extractor
