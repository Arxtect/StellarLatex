cmake_minimum_required(VERSION 3.10)
project(stellarlatexpdftex)

find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)

#  COMPILE FLAGS
## set flags
set(COMMON_FLAGS
    -O3
    -Wno-parentheses-equality
    -Wno-pointer-sign
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
    -sEXPORTED_FUNCTIONS='["_compileLaTeX","_main","_malloc","_synctex_view","_synctex_edit"]'
    -sNO_EXIT_RUNTIME=1
    -sEXPORTED_RUNTIME_METHODS=["cwrap"]
    -sALLOW_MEMORY_GROWTH=1
)
string(REPLACE ";" " " LINKER_FLAGS_STR "${LINKER_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${LINKER_FLAGS_STR}")

#  SOURCES
## common
file(GLOB_RECURSE COMMONSOURCES
    ${COMMON_CODE_DIR}/web2c/*.c
    ${COMMON_CODE_DIR}/web2c/*.cpp
    ${COMMON_CODE_DIR}/web2c/lib/*.c
    ${COMMON_CODE_DIR}/web2c/controller/*.cpp
    ${COMMON_CODE_DIR}/ctan/*.cpp
    ${COMMON_CODE_DIR}/md5/md5.c
    ${COMMON_CODE_DIR}/bibtex/bibtex.c
    ${COMMON_CODE_DIR}/kpathsea/*.c
    ${COMMON_CODE_DIR}/kpathsea/*.cpp
    ${COMMON_CODE_DIR}/memory/xmemory.c
    ${COMMON_CODE_DIR}/makeindexk/*.c
    ${COMMON_CODE_DIR}/tree/*.c
    ${COMMON_CODE_DIR}/synctexdir/*.c
)
## pdftex
file(GLOB_RECURSE PDFTEXSOURCES
    tex/*.c
    pdftexdir/avl.c
    pdftexdir/utils.c
    pdftexdir/writejbig2.c
    pdftexdir/writettf.c
    pdftexdir/avlstuff.c
    pdftexdir/pkin.c
    pdftexdir/vfpacket.c
    pdftexdir/writejpg.c
    pdftexdir/writezip.c
    pdftexdir/epdf.c
    pdftexdir/subfont.c
    pdftexdir/writeenc.c
    pdftexdir/writepng.c
    pdftexdir/tounicode.c
    pdftexdir/writefont.c
    pdftexdir/writet1.c
    pdftexdir/mapfile.c
    pdftexdir/writeimg.c
    pdftexdir/writet3.c
    pdftexdir/pdftoepdf.cc
)

#  SET CMAKE PROJECT
add_executable(${PROJECT_NAME} ${COMMONSOURCES} ${PDFTEXSOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE HAVE_CONFIG_H)
target_compile_definitions(${PROJECT_NAME} PRIVATE __SyncTeX__)
target_compile_definitions(${PROJECT_NAME} PRIVATE SYNCTEX_ENGINE_H="synctex-pdftex.h")
target_compile_definitions(${PROJECT_NAME} PRIVATE PDFTEXWASM)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/tex
    ${CMAKE_CURRENT_SOURCE_DIR}/pdftexdir
    ${THIRD_PARTY_DIR}/libxpdf/inc
    ${THIRD_PARTY_DIR}/libxpdf/repo
    ${THIRD_PARTY_DIR}/libxpdf/repo/goo
    ${THIRD_PARTY_DIR}/libxpdf/repo/xpdf
    ${COMMON_CODE_DIR}
    ${COMMON_CODE_DIR}/web2c
    ${COMMON_CODE_DIR}/web2c/lib
    ${COMMON_CODE_DIR}/synctexdir
    ${COMMON_CODE_DIR}/memory
    ${COMMON_CODE_DIR}/md5
    ${COMMON_CODE_DIR}/makeindexk
)
target_link_directories(${PROJECT_NAME} PRIVATE ${THIRD_PARTY_DIR}/emsdk/upstream/emscripten/cache/sysroot/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${ZLIB_LIBRARIES}
    ${PNG_LIBRARIES}
    libxpdf.a
    libarchive.a
    liblzma.a
    libtinyxml2.a
    libcb.a
)
