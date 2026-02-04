cmake_minimum_required(VERSION 3.13)
project(libharfbuzz)

# use freetype for correct include path
set(CMAKE_C_FLAGS -sUSE_FREETYPE)
set(CMAKE_CXX_FLAGS -sUSE_FREETYPE)

file(GLOB HARFBUZZ_SOURCES "repo/src/hb-*.cc")

# build target
add_library(harfbuzz STATIC ${HARFBUZZ_SOURCES})
add_definitions(-DHAVE_GRAPHITE2)
add_definitions(-DHAVE_FREETYPE)
add_definitions(-DHAVE_ICU)

target_include_directories(harfbuzz PUBLIC ${CMAKE_SOURCE_DIR}/repo/src)
