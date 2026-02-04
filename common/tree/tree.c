#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#define MAX_DEPTH 20
#define MAX_PATH 1024

// print dir tree (file in one line)
static uint32_t simpleHash(const char* filePath) {
	FILE* file = fopen(filePath, "rb");
	if (!file) return 0;
	uint32_t	   hash = 0xC0FFEE;
	const uint32_t seed = 131;
	int			   byte;
	while ((byte = fgetc(file)) != EOF) { hash = (hash * seed) + (uint8_t)byte; }
	fclose(file);
	return hash;
}
static uint32_t (*hashFunc)(const char*) = NULL;
static void print_tree2(const char* base_path, const char* prefix, int depth, FILE* fp) {
	if (depth >= MAX_DEPTH) return;

	DIR* dir = opendir(base_path);
	if (!dir) return;

	struct dirent* entry;
	struct stat	   stat_buf;
	char		   full_path[MAX_PATH];
	char		   symlink_target[MAX_PATH];

	// total count
	int count			  = 0;
	int have_regular_file = 0;
	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, ".") == 0 && strcmp(entry->d_name, "..") == 0) continue;
		snprintf(full_path, sizeof(full_path), "%s/%s", base_path, entry->d_name);
		if (lstat(full_path, &stat_buf) == -1) continue;
		if (S_ISDIR(stat_buf.st_mode) && !S_ISLNK(stat_buf.st_mode))
			count++;
		else
			have_regular_file++;
	}
	if (have_regular_file != 0) count++;
	rewinddir(dir);

	int current = 0;
	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

		// full path
		snprintf(full_path, sizeof(full_path), "%s/%s", base_path, entry->d_name);
		if (lstat(full_path, &stat_buf) == -1) continue;
		if (S_ISDIR(stat_buf.st_mode) && !S_ISLNK(stat_buf.st_mode)) {
			fprintf(fp, "%s", prefix);
			fprintf(fp, "%s", (current == count - 1) ? "└─ " : "├─ ");
			fprintf(fp, "%s/", entry->d_name);
			fprintf(fp, "\n");

			char new_prefix[MAX_PATH];
			snprintf(
				new_prefix, sizeof(new_prefix), "%s%s", prefix,
				(current == count - 1) ? "    " : "│   ");
			print_tree2(full_path, new_prefix, depth + 1, fp);

			current++;
		}
	}
	rewinddir(dir);
	if (have_regular_file != 0) {
		int reg_current = 0;
		fprintf(fp, "%s", prefix);
		fprintf(fp, "%s", "└─ ");
		while ((entry = readdir(dir)) != NULL) {
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
				continue;

			// full path
			snprintf(full_path, sizeof(full_path), "%s/%s", base_path, entry->d_name);
			if (lstat(full_path, &stat_buf) == -1) continue;
			if (S_ISDIR(stat_buf.st_mode) && !S_ISLNK(stat_buf.st_mode)) continue;
			if (S_ISREG(stat_buf.st_mode) && hashFunc != NULL)
				fprintf(fp, "[%04x]", hashFunc(full_path) & 0xFFFF);
			fprintf(fp, "%s", entry->d_name);
			if (S_ISLNK(stat_buf.st_mode)) {
				ssize_t len =
					readlink(full_path, symlink_target, sizeof(symlink_target) - 1);
				if (len != -1) {
					symlink_target[len] = '\0';
					fprintf(fp, "@ ->%s", symlink_target);
				}
			}
			if (reg_current == have_regular_file - 1)
				fprintf(fp, "\n");
			else
				fprintf(fp, ", ");
			reg_current++;
		}
	}
	closedir(dir);
}
static void print_tree(const char* base_path, const char* prefix, int depth, FILE* fp) {
	if (depth >= MAX_DEPTH) return;

	DIR* dir = opendir(base_path);
	if (!dir) return;

	struct dirent* entry;
	struct stat	   stat_buf;
	char		   full_path[MAX_PATH];
	char		   symlink_target[MAX_PATH];

	// full count
	int count = 0;
	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
			count++;
		}
	}
	rewinddir(dir);

	int current = 0;
	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

		// full path
		snprintf(full_path, sizeof(full_path), "%s/%s", base_path, entry->d_name);

		// get file info
		if (lstat(full_path, &stat_buf) == -1) continue;
		fprintf(fp, "%s", prefix);
		fprintf(fp, "%s", (current == count - 1) ? "└─ " : "├─ ");
		if (S_ISDIR(stat_buf.st_mode) && !S_ISLNK(stat_buf.st_mode))
			fprintf(fp, "%s/", entry->d_name);
		else {
			if (S_ISREG(stat_buf.st_mode) && hashFunc != NULL)
				fprintf(fp, "[%08x] ", hashFunc(full_path));
			if (S_ISREG(stat_buf.st_mode)) {
				char time_buf[20];
				strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M", localtime(&stat_buf.st_mtime));
				fprintf(fp, "%-12s %s", entry->d_name, time_buf);
			} else {
				fprintf(fp, "%s", entry->d_name);
			}
		}
		if (S_ISLNK(stat_buf.st_mode)) {
			ssize_t len = readlink(full_path, symlink_target, sizeof(symlink_target) - 1);
			if (len != -1) {
				symlink_target[len] = '\0';
				fprintf(fp, "@ -> %s", symlink_target);
			}
		}
		fprintf(fp, "\n");
		if (S_ISDIR(stat_buf.st_mode) && !S_ISLNK(stat_buf.st_mode)) {
			char new_prefix[MAX_PATH];
			snprintf(
				new_prefix, sizeof(new_prefix), "%s%s", prefix,
				(current == count - 1) ? "    " : "│   ");
			// for /tex, use print tree in one line
			if (strcmp(full_path, "//tex") == 0)
				print_tree2(full_path, new_prefix, depth + 1, fp);
			else
				print_tree(full_path, new_prefix, depth + 1, fp);
		}

		current++;
	}
	closedir(dir);
}

void tree_dir(const char* path, FILE* fp) {
	fprintf(fp, "%s\n", path);
	print_tree(path, "", 0, fp);
}

void lsdir(const char* path, FILE* fp) {
	struct dirent* entry;
	DIR*		   dir = opendir(path);
	fprintf(fp, "lsdir %s: ", path);
	if (!dir) return;
	while ((entry = readdir(dir)) != NULL) fprintf(fp, "%s, ", entry->d_name);
	fprintf(fp, "\n");
}
