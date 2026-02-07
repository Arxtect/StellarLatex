cmake_minimum_required(VERSION 3.10)
project(stellarlatexpdftex)

find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)

# =============================================================
# 1. 路径定义
# =============================================================
set(THIRD_PARTY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty")
set(COMMON_CODE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../common")

# =============================================================
# 2. 第三方库（必须是 wasm 版本 .a）
# =============================================================
set(LIB_XPDF      "${THIRD_PARTY_DIR}/libxpdf/build/libxpdf.a")
set(LIB_ARCHIVE  "${THIRD_PARTY_DIR}/libarchive/build/libarchive/libarchive.a")
set(LIB_LZMA     "${THIRD_PARTY_DIR}/liblzma/build/liblzma.a")
set(LIB_TINYXML2 "${THIRD_PARTY_DIR}/libtinyxml2/build/libtinyxml2.a")

# =============================================================
# 3. 编译选项
# =============================================================
set(COMMON_FLAGS
    -O3
    -Wno-parentheses-equality
    -Wno-pointer-sign
    -fno-rtti
    -fexceptions

    -sUSE_ZLIB=1
    -sUSE_LIBPNG=1
    -sUSE_FREETYPE=1
    -sUSE_ICU=1
)

string(REPLACE ";" " " COMMON_FLAGS_STR "${COMMON_FLAGS}")
set(CMAKE_C_FLAGS   "${COMMON_FLAGS_STR}")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS_STR}")
add_definitions(-DHAVE_REGEX_H)


# =============================================================
# 4. 链接选项
# =============================================================
set(LIBRARY_JS ${CMAKE_CURRENT_SOURCE_DIR}/library.js)
set(PRE_JS     ${CMAKE_CURRENT_SOURCE_DIR}/pre.js)

set(LINKER_FLAGS
    --js-library=${LIBRARY_JS}
    --pre-js=${PRE_JS}

    -sENVIRONMENT=node
    -sMODULARIZE=1
    -sEXPORT_ES6=1
    -sEXIT_RUNTIME=0

    -sWASM=1
    -sALLOW_MEMORY_GROWTH=1
    -sINITIAL_MEMORY=268435456
    -sSTACK_SIZE=5242880

    -sUSE_ZLIB=1
    -sUSE_LIBPNG=1
    -sUSE_FREETYPE=1
    -sUSE_ICU=1

    -sEXPORTED_FUNCTIONS='["_compileLaTeX","_main","_malloc","_synctex_view","_synctex_edit"]'
    -sEXPORTED_RUNTIME_METHODS='["ccall","cwrap"]'
)

string(REPLACE ";" " " LINKER_FLAGS_STR "${LINKER_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${LINKER_FLAGS_STR}")

# =============================================================
# 5. 源文件
# =============================================================
file(GLOB_RECURSE COMMONSOURCES
    ${COMMON_CODE_DIR}/web2c/*.c
    ${COMMON_CODE_DIR}/web2c/*.cpp
    ${COMMON_CODE_DIR}/web2c/lib/*.c
    ${COMMON_CODE_DIR}/web2c/controller/*.cpp
    ${COMMON_CODE_DIR}/web2c/controller/*.cpp
    ${COMMON_CODE_DIR}/ctan/*.cpp
    ${COMMON_CODE_DIR}/bibtex/bibtex.c
    ${COMMON_CODE_DIR}/kpathsea/*.c
    ${COMMON_CODE_DIR}/kpathsea/*.cpp
    ${COMMON_CODE_DIR}/memory/xmemory.c
    ${COMMON_CODE_DIR}/makeindexk/*.c
    ${COMMON_CODE_DIR}/tree/*.c
    ${COMMON_CODE_DIR}/synctexdir/*.c
    ${COMMON_CODE_DIR}/md5/md5.c
)

file(GLOB_RECURSE PDFTEXSOURCES
    tex/*.c
    pdftexdir/*.c
    pdftexdir/*.cc
)

list(FILTER PDFTEXSOURCES EXCLUDE REGEX ".*pdftexdir/regex/.*")
list(FILTER PDFTEXSOURCES EXCLUDE REGEX ".*pdftexdir/pdftexextra.*")
list(FILTER PDFTEXSOURCES EXCLUDE REGEX ".*pdftexdir/ttf2afm.*")
list(FILTER PDFTEXSOURCES EXCLUDE REGEX ".*pdftexdir/pdftosrc.*")
list(FILTER PDFTEXSOURCES EXCLUDE REGEX ".*pdftexdir/macnames.*")


# =============================================================
# 6. 构建目标
# =============================================================
add_executable(${PROJECT_NAME}
    ${COMMONSOURCES}
    ${PDFTEXSOURCES}
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    HAVE_CONFIG_H
    SYNCTEX_ENGINE_H="synctex-pdftex.h"
    PDFTEXWASM
)

target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<COMPILE_LANGUAGE:C>:-std=gnu89>
  $<$<COMPILE_LANGUAGE:C>:-Wno-implicit-function-declaration>
)

target_compile_definitions(${PROJECT_NAME} PRIVATE HAVE_CONFIG_H)
target_compile_definitions(${PROJECT_NAME} PRIVATE __SyncTeX__)
target_compile_definitions(${PROJECT_NAME} PRIVATE SYNCTEX_ENGINE_H="synctex-pdftex.h")
target_compile_definitions(${PROJECT_NAME} PRIVATE PDFTEXWASM)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/tex
    ${CMAKE_CURRENT_SOURCE_DIR}/pdftexdir
    ${CMAKE_CURRENT_SOURCE_DIR}/pdftexdir/regex

    ${COMMON_CODE_DIR}
    ${COMMON_CODE_DIR}/web2c
    ${COMMON_CODE_DIR}/web2c/lib
    ${COMMON_CODE_DIR}/synctexdir
    ${COMMON_CODE_DIR}/memory
    ${COMMON_CODE_DIR}/md5
    ${COMMON_CODE_DIR}/makeindexk

    ${THIRD_PARTY_DIR}/libxpdf/inc
    ${THIRD_PARTY_DIR}/libxpdf/repo
    ${THIRD_PARTY_DIR}/libxpdf/repo/goo
    ${THIRD_PARTY_DIR}/libxpdf/repo/xpdf
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${ZLIB_LIBRARIES}
    ${PNG_LIBRARIES}
    ${LIB_XPDF}
    ${LIB_ARCHIVE}
    ${LIB_LZMA}
    ${LIB_TINYXML2}
)
