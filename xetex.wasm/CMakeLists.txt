cmake_minimum_required(VERSION 3.10)
project(swiftlatexxetex)

#  COMPILE FLAGS
## set flags
set(COMMON_FLAGS
    -O3
    -Wno-parentheses-equality
    -Wno-pointer-sign
    -DWEBASSEMBLY_BUILD
    -sUSE_FREETYPE=1
    -sUSE_ICU=1
    -sUSE_LIBPNG=1
    -fno-rtti
    -fno-exceptions
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
    md5.c
    xmemory.c
    texfile.c
    kpseemu.c
    texmfmp.c
    main.c
    bibtex.c
    xetexdir/XeTeX_ext.c
    xetexdir/XeTeX_pic.c
    xetexdir/image/bmpimage.c
	xetexdir/image/jpegimage.c
	xetexdir/image/pngimage.c
    xetexdir/trans.c
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
add_executable(${PROJECT_NAME} ${TEXSOURCES} ${XETEXSOURCES} ${TECKITSOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/tex
    ${CMAKE_CURRENT_SOURCE_DIR}/xetexdir
    ${CMAKE_CURRENT_SOURCE_DIR}/harfbuzz
    ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/libxpdf/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/libxpdf/repo
    ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/libxpdf/repo/goo
    ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/libxpdf/repo/xpdf
    ${CMAKE_CURRENT_SOURCE_DIR}/teckit
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/libxpdf/build/libxpdf.a
    ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/libgraphite2/build/src/libgraphite2.a
    ${CMAKE_CURRENT_SOURCE_DIR}/harfbuzz/libharfbuzz.a
)
