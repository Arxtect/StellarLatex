cmake_minimum_required(VERSION 3.10)
project(stellarlatexxetex)

# =============================================================
# 1. 路径定义 (根据你的目录结构调整)
# =============================================================
# 假设 3rdparty 文件夹在当前 CMakeLists.txt 同级目录
set(THIRD_PARTY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty")
set(COMMON_CODE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../common") # 假设 common 在上一级，请根据实际情况调整

# =============================================================
# 2. 查找并定义第三方库 (基于你提供的 find 结果)
# =============================================================
set(LIB_HARFBUZZ    "${THIRD_PARTY_DIR}/libharfbuzz/build/libharfbuzz.a")
set(LIB_GRAPHITE2   "${THIRD_PARTY_DIR}/libgraphite2/build/src/libgraphite2.a") # 注意是 src 下的
set(LIB_XPDF        "${THIRD_PARTY_DIR}/libxpdf/build/libxpdf.a")
set(LIB_TINYXML2    "${THIRD_PARTY_DIR}/libtinyxml2/build/libtinyxml2.a")
set(LIB_LZMA        "${THIRD_PARTY_DIR}/liblzma/build/liblzma.a")
set(LIB_ARCHIVE     "${THIRD_PARTY_DIR}/libarchive/build/libarchive/libarchive.a") # 注意路径层级

# PPlib 分成了三个库
set(LIB_PPLIB_CORE  "${THIRD_PARTY_DIR}/libpplib/build/libpplib.a")
set(LIB_PPLIB_UTIL  "${THIRD_PARTY_DIR}/libpplib/build/libpplib_utils.a")
set(LIB_PPLIB_FILT  "${THIRD_PARTY_DIR}/libpplib/build/libpplib_filters.a")

# 检查文件是否存在，避免编译到一半才报错
if(NOT EXISTS "${LIB_HARFBUZZ}")
    message(WARNING "Library not found: ${LIB_HARFBUZZ} \nDid you build the 3rdparty dependencies?")
endif()

# =============================================================
# 3. 编译选项 (Compile Flags)
# =============================================================
# 移除 find_package(ZLIB/PNG)，直接用 Emscripten 内置支持
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
    -fexceptions      # 允许异常
)

# 转换为字符串
string(REPLACE ";" " " COMMON_FLAGS_STR "${COMMON_FLAGS}")
set(CMAKE_C_FLAGS "${COMMON_FLAGS_STR}")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS_STR}")

# =============================================================
# 4. 链接选项 (Link Flags)
# =============================================================
set(LIBRARY_JS ${CMAKE_CURRENT_SOURCE_DIR}/library.js)
set(PRE_JS ${CMAKE_CURRENT_SOURCE_DIR}/pre.js)

set(LINKER_FLAGS
    --js-library=${LIBRARY_JS}
    --pre-js=${PRE_JS}
    -sENVIRONMENT=web
    -sEXPORTED_FUNCTIONS='["_compileLaTeX","_main","_malloc","_synctex_view","_synctex_edit"]'
    -sNO_EXIT_RUNTIME=1
    -sWASM=1
    -sEXPORTED_RUNTIME_METHODS=["cwrap"]
    -sALLOW_MEMORY_GROWTH=1
    -sINITIAL_MEMORY=268435456  # 建议设置初始内存 256MB，防止启动 OOM
    -sSTACK_SIZE=5242880        # 5MB 栈

    -sEXPORTED_RUNTIME_METHODS='["ccall","cwrap"]' # 建议加上这个以便调试

    -fno-rtti
)

string(REPLACE ";" " " LINKER_FLAGS_STR "${LINKER_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${LINKER_FLAGS_STR}")

# =============================================================
# 5. 源文件定义
# =============================================================
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
    xetexdir/xetex-shim.cpp
)

# =============================================================
# 6. 构建目标 (Target)
# =============================================================
add_executable(${PROJECT_NAME} ${COMMONSOURCES} ${XETEXSOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/tex
    ${CMAKE_CURRENT_SOURCE_DIR}/xetexdir
    ${THIRD_PARTY_DIR}/libxpdf/inc
    ${THIRD_PARTY_DIR}/libxpdf/repo
    ${THIRD_PARTY_DIR}/libxpdf/repo/goo
    ${THIRD_PARTY_DIR}/libxpdf/repo/xpdf
    ${THIRD_PARTY_DIR}/libpplib/repo/src
    ${THIRD_PARTY_DIR}/libharfbuzz/repo/src
    ${COMMON_CODE_DIR}
    ${COMMON_CODE_DIR}/web2c
    ${COMMON_CODE_DIR}/web2c/lib
    ${COMMON_CODE_DIR}/synctexdir
    ${COMMON_CODE_DIR}/memory
    ${COMMON_CODE_DIR}/md5
    ${COMMON_CODE_DIR}/makeindexk
    ${COMMON_CODE_DIR}/teckit
    ${COMMON_CODE_DIR}/teckit/Public-headers
)

# 链接第三方库 (使用上面定义的绝对路径变量)
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${LIB_XPDF}
    ${LIB_ARCHIVE}
    ${LIB_LZMA}
    ${LIB_TINYXML2}
    ${LIB_PPLIB_CORE}
    ${LIB_PPLIB_UTIL}
    ${LIB_PPLIB_FILT}
    ${LIB_GRAPHITE2}
    ${LIB_HARFBUZZ}
    
    # [说明] libcb 和 libdvi 通常是 TeX 内部库。
    # 既然你上面 GLOB 了 web2c/lib/*.c 和 tex/*.c，
    # 这些代码应该已经包含在 executable 里了，不需要额外链接 libcb.a / libdvi.a。
    # 如果编译报错 undefined symbol，请检查 COMMONSOURCES 是否漏了文件。
)