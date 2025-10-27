cmake_minimum_required(VERSION 3.10)
project(swiftlatexxetex)

#  COMPILE FLAGS
## set flags
set(COMMON_FLAGS
    -O3
    -Wno-parentheses-equality
    -Wno-pointer-sign
    -D__SyncTeX__
    -DSYNCTEX_ENGINE_H='"synctex-xetex.h"'
    -DWEBASSEMBLY_BUILD
    -DXETEXWASM
    -DHAVE_CONFIG_H
    -sUSE_FREETYPE
    -sUSE_ICU
    -sUSE_LIBPNG
    -fno-rtti
    -fexceptions
)
## convert to string
string(REPLACE ";" " " COMMON_FLAGS_STR "${COMMON_FLAGS}")
## set to cmake variable
set(CMAKE_C_FLAGS "${COMMON_FLAGS_STR}")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS_STR}")

#  LINK FLAGS
## set js path
set(LIBRARY_JS ${CMAKE_CURRENT_SOURCE_DIR}/library.js)
set(PRE_JS ${CMAKE_CURRENT_SOURCE_DIR}/pre.js)
## set link flag
set(LINKER_FLAGS
    --js-library=${LIBRARY_JS}
    --pre-js=${PRE_JS}
    -sENVIRONMENT=web
    -sEXPORTED_FUNCTIONS='["_compileBibLatex","_compileLaTeX","_compileFormat","_main","_setMainEntry","_malloc","_synctex_view","_synctex_edit"]'
    -sNO_EXIT_RUNTIME=1
    -sWASM=1
    -sEXPORTED_RUNTIME_METHODS=["cwrap"]
    -sALLOW_MEMORY_GROWTH=1
)
string(REPLACE ";" " " LINKER_FLAGS_STR "${LINKER_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${LINKER_FLAGS_STR}")

#  SOURCES
## common
file(GLOB_RECURSE COMMONSOURCES
    ${COMMON_CODE_DIR}/web2c/*.c
    ${COMMON_CODE_DIR}/ctan/*.cpp
    ${COMMON_CODE_DIR}/md5/md5.c
    ${COMMON_CODE_DIR}/bibtex/bibtex.c
    ${COMMON_CODE_DIR}/localkpse/kpseemu.c
    ${COMMON_CODE_DIR}/localkpse/kpfind.cpp
    ${COMMON_CODE_DIR}/memory/xmemory.c
    ${COMMON_CODE_DIR}/makeindexk/*.c
    ${COMMON_CODE_DIR}/tree/*.c
    ${COMMON_CODE_DIR}/synctexdir/*.c
    ${COMMON_CODE_DIR}/teckit/Engine.cpp
)
## xetex
file(GLOB_RECURSE XETEXSOURCES
    tex/*.c
    xetexdir/XeTeXOTMath.cpp
    xetexdir/XeTeXLayoutInterface.cpp
    xetexdir/XeTeXFontMgr.cpp
    xetexdir/XeTeXFontInst.cpp
    xetexdir/XeTeXFontMgr_FC.cpp
    xetexdir/hz.cpp
    xetexdir/pdfimage.cpp
    xetexdir/XeTeX_ext.c
    xetexdir/XeTeX_pic.c
    xetexdir/image/bmpimage.c
    xetexdir/image/jpegimage.c
    xetexdir/image/pngimage.c
    xetexdir/trans.c
)

#  SET CMAKE PROJECT
add_executable(${PROJECT_NAME} ${COMMONSOURCES} ${XETEXSOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/tex
    ${CMAKE_CURRENT_SOURCE_DIR}/xetexdir
    ${THIRD_PARTY_DIR}/libharfbuzz/repo/src
    ${THIRD_PARTY_DIR}/libxpdf/inc
    ${THIRD_PARTY_DIR}/libxpdf/repo
    ${THIRD_PARTY_DIR}/libxpdf/repo/goo
    ${THIRD_PARTY_DIR}/libxpdf/repo/xpdf
    ${THIRD_PARTY_DIR}/libpplib/repo/src
    ${COMMON_CODE_DIR}
    ${COMMON_CODE_DIR}/web2c
    ${COMMON_CODE_DIR}/synctexdir
    ${COMMON_CODE_DIR}/memory
    ${COMMON_CODE_DIR}/md5
    ${COMMON_CODE_DIR}/teckit
    ${COMMON_CODE_DIR}/teckit/Public-headers
    ${COMMON_CODE_DIR}/makeindexk
)
target_link_directories(${PROJECT_NAME} PRIVATE ${THIRD_PARTY_DIR}/emsdk/upstream/emscripten/cache/sysroot/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE
    libxpdf.a
    libarchive.a
    liblzma.a
    libtinyxml2.a
    libgraphite2.a
    libharfbuzz.a
    libcb.a
    libpplib.a
    libpplib_utils.a
    libpplib_filters.a
)
