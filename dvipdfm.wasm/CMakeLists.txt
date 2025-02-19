cmake_minimum_required(VERSION 3.10)
project(swiftlatexdvipdfm)

# COMPILE FLAGS
set(COMMON_FLAGS
    -O3
    -DHAVE_ZLIB
    -sUSE_LIBPNG
    -fno-rtti
    -fno-exceptions
)
string(REPLACE ";" " " COMMON_FLAGS_STR "${COMMON_FLAGS}")
set(CMAKE_C_FLAGS "${COMMON_FLAGS_STR}")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS_STR}")

# LINK FLAGS
set(LINKER_FLAGS
    --js-library=${CMAKE_CURRENT_SOURCE_DIR}/library.js
    -sENVIRONMENT="web"
    -sUSE_LIBPNG
    --pre-js=${CMAKE_CURRENT_SOURCE_DIR}/pre.js
    -sEXPORTED_FUNCTIONS='["_compilePDF","_setMainEntry","_main","_malloc" ]'
    -sNO_EXIT_RUNTIME=1
    -sWASM=1
    -sALLOW_MEMORY_GROWTH=1
    -sEXPORTED_RUNTIME_METHODS=["cwrap"]
    -fno-rtti
    -fno-exceptions
)
string(REPLACE ";" " " LINKER_FLAGS_STR "${LINKER_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${LINKER_FLAGS_STR}")

# SOURCES
file(GLOB_RECURSE CSOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

# HEADERS
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

# SET CMAKE PROJECT
add_executable(${PROJECT_NAME} ${CSOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
