#include "controller/control_utils.hpp"
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <libgen.h>
#include <makeindexk/makeindex.h>
#include <map>
#include <md5/md5.h>
#include <setjmp.h>
#include <string>
#include <synctex_parser.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/un.h>
#include <time.h>
#include <tree/tree.h>
#include <unistd.h>

#ifdef XETEXWASM
extern jmp_buf jmpenv;
extern "C" int convertXDVPDF(const char* xdv, const char* pdf);
#endif
using cppstr = std::string;
namespace fs = std::filesystem;
char* synctexViewRoutine(const char* pdf, const char* tex, int line, int column) {
	synctex_scanner_p scanner = synctex_scanner_new_with_output_file(pdf, NULL, 1);
	if (!scanner) return NULL;

	int status = synctex_display_query(scanner, tex, line, column, 0);
	if (status <= 0) {
		synctex_scanner_free(scanner);
		return NULL;
	}

	synctex_node_p node;
	if ((node = synctex_scanner_next_result(scanner)) == NULL) return NULL;

	char  buffer[512];
	int	  page = synctex_node_page(node);
	float x	   = synctex_node_visible_h(node);
	float y	   = synctex_node_visible_v(node);
	float h	   = synctex_node_box_visible_h(node);
	float v	   = synctex_node_box_visible_v(node) + synctex_node_box_visible_depth(node);
	float W	   = synctex_node_box_visible_width(node);
	float H =
		synctex_node_box_visible_height(node) + synctex_node_box_visible_depth(node);
	snprintf(
		buffer, sizeof(buffer), "%d\x1F%.2f\x1F%.2f\x1F%.2f\x1F%.2f\x1F%.2f\x1F%.2f",
		page, x, y, h, v, W, H);
	synctex_scanner_free(scanner);
	return strdup(buffer);
}

char* synctexEditRoutine(const char* pdf_path, int page, float x, float y) {
	synctex_scanner_p scanner = synctex_scanner_new_with_output_file(pdf_path, NULL, 1);
	if (!scanner) return NULL;

	int status = synctex_edit_query(scanner, page, x, y);
	if (status <= 0) {
		synctex_scanner_free(scanner);
		return NULL;
	}

	synctex_node_p node;
	if ((node = synctex_scanner_next_result(scanner)) == NULL) return NULL;

	// now we only use the first one
	char		buffer[256];
	const char* name = synctex_scanner_get_name(scanner, synctex_node_tag(node));
	int			line = synctex_node_line(node);
	int			col	 = synctex_node_column(node);
	snprintf(buffer, sizeof(buffer), "%s\x1F%d\x1F%d", name, line, col);
	synctex_scanner_free(scanner);
	return strdup(buffer);
}

extern "C" char* synctex_view(const char* pdf, const char* tex, int line, int column) {
	if (tex == nullptr || pdf == nullptr) return nullptr;

	// 使用cppstr重写路径处理逻辑
	cppstr synctex_tex_path;
	cppstr input_path(tex);

	if (input_path[0] == '.') { synctex_tex_path = "/work" + input_path; }
	else if (input_path[0] == '/') {
		if (input_path.substr(0, 6) == "/work/" &&
			input_path.substr(0, 8) != "/work/./") {
			synctex_tex_path = "/work/./" + input_path.substr(6);
		}
		else { synctex_tex_path = "/work/." + input_path; }
	}
	else { synctex_tex_path = "/work/./" + input_path; }
	// std::cerr << "[WASM ENGINE] call synctexViewRoutine(\"" << pdf << "\", \""
	// 		  << synctex_tex_path << "\", " << line << ", " << column << ")\n";
	char* ret = synctexViewRoutine(pdf, synctex_tex_path.c_str(), line, column);
	// std::cerr << "[WASM ENGINE] call synctexViewRoutine(\"" << pdf << "\", \""
	// 		  << synctex_tex_path << "\", " << line << ", " << column << ") return \""
	// 		  << ret << "\"\n";
	return ret;
}
extern "C" char* synctex_edit(const char* pdf_path, int page, float x, float y) {
	if (pdf_path == nullptr) return nullptr;
	// std::cerr << "[WASM ENGINE] call synctexEditRoutine(\"" << pdf_path << "\", " << page
	// 		  << ", " << x << ", " << y << ")\n";
	char* ret = synctexEditRoutine(pdf_path, page, x, y);
	// std::cerr << "[WASM ENGINE] call synctexEditRoutine(\"" << pdf_path << "\", " << page
	// 		  << ", " << x << ", " << y << ") return \"" << ret << "\"\n";
	return ret;
}
int main(int argc, char** argv) {
	printf("StellarLatex Engine Loaded\n");
}
