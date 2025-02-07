cmake_minimum_required(VERSION 3.10)
project(swiftlatexpdftex)

#  COMPILER
set(CMAKE_C_COMPILER emcc)
set(CMAKE_CXX_COMPILER em++)

#  COMPILE FLAGS
## set flags
set(COMMON_FLAGS
    -O3
	-sUSE_ZLIB=1
    -sUSE_LIBPNG=1
    -Wno-parentheses-equality
    -Wno-pointer-sign
    -DWEBASSEMBLY_BUILD
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
    -sEXPORTED_FUNCTIONS='["_compileBibtex","_compileLaTeX","_compileFormat","_main","_setMainEntry","_malloc"]'
    -sNO_EXIT_RUNTIME=1
    -sEXPORTED_RUNTIME_METHODS=["cwrap"]
    -sALLOW_MEMORY_GROWTH=1
	-sUSE_ZLIB=1
    -sUSE_LIBPNG=1
)
string(REPLACE ";" " " LINKER_FLAGS_STR "${LINKER_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${LINKER_FLAGS_STR}")

#  SOURCES
## tex
file(GLOB_RECURSE TEXSOURCES
    tex/pdftex0.c
    tex/pdftexini.c
    tex/pdftex-pool.c
    md5.c
    xmemory.c
    texfile.c
    kpseemu.c
    main.c
    bibtex.c
)
## pdftex
file(GLOB_RECURSE PDFTEXSOURCES
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
)
## teckit
file(GLOB_RECURSE EPDFSOURCES
    pdftexdir/pdftoepdf.cc
)

#  SET CMAKE PROJECT
add_executable(${PROJECT_NAME} ${TEXSOURCES} ${PDFTEXSOURCES} ${EPDFSOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/tex
    ${CMAKE_CURRENT_SOURCE_DIR}/pdftexdir
    ${CMAKE_CURRENT_SOURCE_DIR}/xpdf
    ${CMAKE_CURRENT_SOURCE_DIR}/xpdf/goo
	${CMAKE_CURRENT_SOURCE_DIR}/xpdf/xpdf
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/xpdf/xpdf.a
)
