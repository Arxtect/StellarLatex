# FIRST, WE SET EMSDK TOOLCHAIN. IF YOU ALREADY HAVE THAT, YOU CAN DEFINE EMSDK_PATH TO SKIP TOOLCHAIN BUILD WAY.
## this feature requires cmake 3.20 or upon.
cmake_minimum_required(VERSION 3.20)
include(ExternalProject)

## check if emsdk env is set
if(NOT DEFINED ENV{EMSDK_PATH})
    set(EMSDK_PATH "${CMAKE_SOURCE_DIR}/3rdparty/emsdk" CACHE PATH "EMSDK path (default)")
    execute_process(COMMAND git clone git@github.com:emscripten-core/emsdk.git ${EMSDK_PATH})
    execute_process(COMMAND ${EMSDK_PATH}/emsdk install latest)
    execute_process(COMMAND ${EMSDK_PATH}/emsdk activate latest)
endif()
## set cmake toolchain
execute_process(COMMAND ${EMSDK_PATH}/upstream/emscripten/embuilder build zlib libpng icu freetype RESULT_VARIABLE RESULT)
if(NOT RESULT EQUAL 0)
    message(FATAL_ERROR "Failed to build emscripten libraries")
endif()
set(CMAKE_TOOLCHAIN_FILE "${EMSDK_PATH}/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake")
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty)
set(COMMON_CODE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/common)

# then, we need some 3rd libraries
ExternalProject_Add(
    libgraphite2
    GIT_REPOSITORY git@github.com:silnrsi/graphite.git
    GIT_TAG        master # TAG 6768ea92b89ed2505a3624208c42ce05e417496c is avaliable
    SOURCE_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libgraphite2/repo
    BINARY_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libgraphite2/build
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -S <SOURCE_DIR> -B <BINARY_DIR> -DBUILD_SHARED_LIBS=OFF -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    UPDATE_COMMAND ""
    BUILD_ALWAYS   OFF
    BUILD_COMMAND     ${CMAKE_COMMAND} --build <BINARY_DIR>
)
ExternalProject_Add(
    libharfbuzz
    GIT_REPOSITORY git@github.com:harfbuzz/harfbuzz.git
    GIT_TAG        main # e41dc20c1cec30a168028947fdbd90071f6c2967 is possible
    SOURCE_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libharfbuzz/repo
    BINARY_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libharfbuzz/build
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -S <SOURCE_DIR>/.. -B <BINARY_DIR> -DBUILD_SHARED_LIBS=OFF -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    UPDATE_COMMAND ""
    BUILD_ALWAYS   OFF
    BUILD_COMMAND     ${CMAKE_COMMAND} --build <BINARY_DIR>
    INSTALL_COMMAND ""
)
ExternalProject_Add(
    libxpdf
    URL            https://dl.xpdfreader.com/xpdf-latest.tar.gz # version 4.0.5 is possible
    SOURCE_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libxpdf/repo
    BINARY_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libxpdf/build
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -S <SOURCE_DIR>/.. -B <BINARY_DIR> -DBUILD_SHARED_LIBS=OFF -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    UPDATE_COMMAND ""
    BUILD_ALWAYS   OFF
    BUILD_COMMAND     ${CMAKE_COMMAND} --build <BINARY_DIR>
    INSTALL_COMMAND ""
)
ExternalProject_Add(
    libpplib
    GIT_REPOSITORY git@github.com:contextgarden/pplib.git
    GIT_TAG        master # 47faa509c47216a93ffb9cfb62562e88470d4451 is possible
    GIT_CONFIG     "submodule.recurse=false" # disable submodules here
    GIT_SUBMODULES "" # disable submodules here
    SOURCE_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libpplib/repo
    BINARY_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libpplib/build
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -S <SOURCE_DIR>/.. -B <BINARY_DIR> -DBUILD_SHARED_LIBS=OFF -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    UPDATE_COMMAND ""
    BUILD_ALWAYS   OFF
    BUILD_COMMAND     ${CMAKE_COMMAND} --build <BINARY_DIR>
    INSTALL_COMMAND ""
)
ExternalProject_Add(
    libbinary
    SOURCE_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libbinary
    BINARY_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libpplib/build
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -S <SOURCE_DIR> -B <BINARY_DIR> -DBUILD_SHARED_LIBS=OFF -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    UPDATE_COMMAND ""
    BUILD_ALWAYS   OFF
    INSTALL_COMMAND ""
)
ExternalProject_Add(
    liblzma
    GIT_REPOSITORY git@github.com:tukaani-project/xz.git
    GIT_TAG        master # TAG a69fbd3aaebc15dc5912e64724e5abfcef09bcdf is avaliable
    SOURCE_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/liblzma/repo
    BINARY_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/liblzma/build
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -S <SOURCE_DIR> -B <BINARY_DIR> -DBUILD_SHARED_LIBS=OFF -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    UPDATE_COMMAND ""
    BUILD_ALWAYS   OFF
    BUILD_COMMAND     ${CMAKE_COMMAND} --build <BINARY_DIR>
)
ExternalProject_Add(
    libarchive
    GIT_REPOSITORY git@github.com:libarchive/libarchive.git
    GIT_TAG        master # TAG 8f49a18f64b42651fac9e7b210a779c076184c53 is avaliable
    SOURCE_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libarchive/repo
    BINARY_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libarchive/build
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -S <SOURCE_DIR> -B <BINARY_DIR> -DBUILD_SHARED_LIBS=OFF -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE} -DENABLE_TEST=OFF
    UPDATE_COMMAND ""
    BUILD_ALWAYS   OFF
    BUILD_COMMAND     ${CMAKE_COMMAND} --build <BINARY_DIR>
)
ExternalProject_Add(
    libtinyxml2
    GIT_REPOSITORY git@github.com:leethomason/tinyxml2.git
    GIT_TAG        master # TAG 9148bdf719e997d1f474be6bcc7943881046dba1 is avaliable
    SOURCE_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libtinyxml2/repo
    BINARY_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libtinyxml2/build
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -S <SOURCE_DIR> -B <BINARY_DIR> -DBUILD_SHARED_LIBS=OFF -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    UPDATE_COMMAND ""
    BUILD_ALWAYS   OFF
    BUILD_COMMAND     ${CMAKE_COMMAND} --build <BINARY_DIR>
)

# THEN the projects go
project(stellarlatex)
add_subdirectory(xetex.wasm)
add_subdirectory(pdftex.wasm)

# Convert to correct format
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/xetex.wasm/xetex.js.prettier
    COMMAND prettier --tab-width=2 --semi --trailing-comma es5 --write stellarlatexxetex.js
    COMMAND sed -i "1i/* eslint-disable */" stellarlatexxetex.js
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/xetex.wasm
    DEPENDS stellarlatexxetex
    COMMENT "Running prettier on stellarlatexxetex.js"
)
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/pdftex.wasm/pdftex.js.prettier
    COMMAND prettier --tab-width=2 --semi --trailing-comma es5 --write stellarlatexpdftex.js
    COMMAND sed -i "1i/* eslint-disable */" stellarlatexpdftex.js
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/pdftex.wasm
    DEPENDS stellarlatexpdftex
    COMMENT "Running prettier on stellarlatexpdftex.js"
)
add_custom_target(post_build_commands ALL
    DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/build/xetex.wasm/xetex.js.prettier
        ${CMAKE_CURRENT_SOURCE_DIR}/build/pdftex.wasm/pdftex.js.prettier
)
