# FIRST, WE SET EMSDK TOOLCHAIN. IF YOU ALREADY HAVE THAT, YOU CAN DEFINE EMSDK_PATH TO SKIP TOOLCHAIN BUILD WAY.
## this feature requires cmake 3.13 or upon.
cmake_minimum_required(VERSION 3.13)
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

# then, we need some 3rd libraries
ExternalProject_Add(
    libgraphite2
    GIT_REPOSITORY git@github.com:silnrsi/graphite.git
    GIT_TAG        master
    SOURCE_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libgraphite2/repo
    BINARY_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libgraphite2/build
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -S <SOURCE_DIR> -B <BINARY_DIR> -DBUILD_SHARED_LIBS=OFF -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    BUILD_COMMAND     ${CMAKE_COMMAND} --build <BINARY_DIR>
)
ExternalProject_Add(
    libharfbuzz
    GIT_REPOSITORY git@github.com:harfbuzz/harfbuzz.git
    GIT_TAG        main
    SOURCE_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libharfbuzz/repo
    BINARY_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libharfbuzz/build
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -S <SOURCE_DIR>/.. -B <BINARY_DIR> -DBUILD_SHARED_LIBS=OFF -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    BUILD_COMMAND     ${CMAKE_COMMAND} --build <BINARY_DIR>
    INSTALL_COMMAND ""
)
ExternalProject_Add(
    libxpdf
    URL            https://dl.xpdfreader.com/xpdf-latest.tar.gz
    SOURCE_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libxpdf/repo
    BINARY_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libxpdf/build
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -S <SOURCE_DIR>/.. -B <BINARY_DIR> -DBUILD_SHARED_LIBS=OFF -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    BUILD_COMMAND     ${CMAKE_COMMAND} --build <BINARY_DIR>
    INSTALL_COMMAND ""
)

# THEN the projects go
project(swiftlatex)
add_subdirectory(xetex.wasm)
add_subdirectory(pdftex.wasm)
add_subdirectory(dvipdfm.wasm)
