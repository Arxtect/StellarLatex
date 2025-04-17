cmake_minimum_required(VERSION 3.10)
project(swiftlatexxetex)

#  COMPILE FLAGS
## set flags
set(COMMON_FLAGS
    -O3
    -Wno-parentheses-equality
    -Wno-pointer-sign
    -DWEBASSEMBLY_BUILD
    -DXETEXWASM
    -sUSE_FREETYPE
    -sUSE_ICU
    -sUSE_LIBPNG
    -fno-rtti
    -fno-exceptions
)
string(REPLACE ";" " " COMMON_FLAGS_STR "${COMMON_FLAGS}")
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
    -sEXPORTED_FUNCTIONS='["_compileBibtex","_compileLaTeX","_compileFormat","_main","_setMainEntry","_malloc"]'
    -sNO_EXIT_RUNTIME=1
    -sWASM=1
    -sEXPORTED_RUNTIME_METHODS=["cwrap"]
    -sALLOW_MEMORY_GROWTH=1
)
string(REPLACE ";" " " LINKER_FLAGS_STR "${LINKER_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${LINKER_FLAGS_STR}")

#  SOURCES
## tex
file(GLOB_RECURSE TEXSOURCES
    tex/xetex0.c
    tex/xetexini.c
    tex/xetex-pool.c
    texfile.c
    texmfmp.c
    main.c
    xetexdir/XeTeX_ext.c
    xetexdir/XeTeX_pic.c
    xetexdir/image/bmpimage.c
    xetexdir/image/jpegimage.c
    xetexdir/image/pngimage.c
    xetexdir/trans.c
)
## ctan
file(GLOB_RECURSE COMMONSOURCES
    ${COMMON_CODE_DIR}/ctan/ctanFileManager.cpp
    ${COMMON_CODE_DIR}/ctan/extractFile.cpp
    ${COMMON_CODE_DIR}/md5/md5.c
    ${COMMON_CODE_DIR}/bibtex/bibtex.c
    ${COMMON_CODE_DIR}/localkpse/kpseemu.c
    ${COMMON_CODE_DIR}/memory/xmemory.c
)
## xetex
file(GLOB_RECURSE XETEXSOURCES
    xetexdir/XeTeXOTMath.cpp
    xetexdir/XeTeXLayoutInterface.cpp
    xetexdir/XeTeXFontMgr.cpp xetexdir/XeTeXFontInst.cpp
    xetexdir/XeTeXFontMgr_FC.cpp xetexdir/hz.cpp
    xetexdir/pdfimage.cpp
)
## teckit
file(GLOB_RECURSE TECKITSOURCES
    teckit/teckit-Engine.cpp
)

#  SET CMAKE PROJECT
add_executable(${PROJECT_NAME} ${TEXSOURCES} ${COMMONSOURCES} ${XETEXSOURCES} ${TECKITSOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/tex
    ${CMAKE_CURRENT_SOURCE_DIR}/xetexdir
    ${CMAKE_CURRENT_SOURCE_DIR}/teckit
    ${THIRD_PARTY_DIR}/libharfbuzz/repo/src
    ${THIRD_PARTY_DIR}/libxpdf/inc
    ${THIRD_PARTY_DIR}/libxpdf/repo
    ${THIRD_PARTY_DIR}/libxpdf/repo/goo
    ${THIRD_PARTY_DIR}/libxpdf/repo/xpdf
    ${THIRD_PARTY_DIR}/libpplib/repo/src
    ${COMMON_CODE_DIR}
    ${COMMON_CODE_DIR}/memory
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${THIRD_PARTY_DIR}/libxpdf/build/libxpdf.a
    ${THIRD_PARTY_DIR}/libgraphite2/build/src/libgraphite2.a
    ${THIRD_PARTY_DIR}/libharfbuzz/build/libharfbuzz.a
    ${THIRD_PARTY_DIR}/libpplib/build/libpplib.a
    ${THIRD_PARTY_DIR}/libpplib/build/libpplib_utils.a
    ${THIRD_PARTY_DIR}/libpplib/build/libpplib_filters.a
    ${THIRD_PARTY_DIR}/libarchive/build/libarchive/libarchive.a
    ${THIRD_PARTY_DIR}/liblzma/build/liblzma.a
)
