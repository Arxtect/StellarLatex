cmake_minimum_required(VERSION 3.5)

project(pplib
    LANGUAGES C)
set(VERSION 1.0.5)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS -sUSE_ZLIB)
set(CMAKE_CXX_FLAGS -sUSE_ZLIB)
set(LINKER_FLAGS -sUSE_ZLIB)

add_library(pplib_utils STATIC
    repo/src/util/utilplat.h
    repo/src/util/utilcryptdef.h
    repo/src/util/utildecl.h
    #
    repo/src/util/utilcrypt.c
    repo/src/util/utilcrypt.h
    repo/src/util/utiliof.c
    repo/src/util/utiliof.h
    repo/src/util/utillog.c
    repo/src/util/utillog.h
    repo/src/util/utilmd5.c
    repo/src/util/utilmd5.h
    repo/src/util/utilmem.c
    repo/src/util/utilmem.h
    #
    repo/src/util/utilmemheap.c
    repo/src/util/utilmemheap.h
    repo/src/util/utilmemheapiof.c
    repo/src/util/utilmemheapiof.h
    repo/src/util/utilmeminfo.c
    repo/src/util/utilmeminfo.h
    #
    repo/src/util/utilnumber.c
    repo/src/util/utilnumber.h
    repo/src/util/utilsha.c
    repo/src/util/utilsha.h
)

target_include_directories(pplib_utils PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/repo/src/util>
)

target_link_libraries(pplib_utils
    PUBLIC
        m
)

add_library(pplib_filters STATIC
    repo/src/util/utilbasexx.c
    repo/src/util/utilbasexx.h
    repo/src/util/utilflate.c
    repo/src/util/utilflate.h
    repo/src/util/utilfpred.c
    repo/src/util/utilfpred.h
    repo/src/util/utillzw.c
    repo/src/util/utillzw.h
)

target_include_directories(pplib_filters PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/repo/src/util>
)

target_link_libraries(pplib_filters
    PUBLIC
        m
)

add_library(pplib
    repo/src/ppapi.h
    repo/src/ppconf.h
    repo/src/pplib.h
    #
    repo/src/pparray.c
    repo/src/pparray.h
    repo/src/ppcrypt.c
    repo/src/ppcrypt.h
    repo/src/ppdict.c
    repo/src/ppdict.h
    repo/src/ppfilter.h
    repo/src/ppheap.c
    repo/src/ppheap.h
    repo/src/ppload.c
    repo/src/ppload.h
    repo/src/ppstream.c
    repo/src/ppstream.h
    repo/src/ppxref.c
    repo/src/ppxref.h
)

target_include_directories(pplib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/repo/src/util>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/repo/src>
)

target_link_libraries(pplib
    PRIVATE
        pplib_filters
        pplib_utils
)

target_include_directories(pplib
    PRIVATE
        util
)

if (MSVC)
    #set(warning_flags '') # /W4 /WX
else (MSVC)
    set(warning_flags
        -Wall
        -Wextra
        -Wcast-align
        -Wcast-qual
        -Wdeclaration-after-statement
        -Wnested-externs
        -Wno-unknown-pragmas
        -Wpointer-arith
        -Wwrite-strings
    )
    
    foreach(target pplib_utils pplib_filters pplib)
        target_compile_options(${target} PRIVATE ${warning_flags})
    endforeach()
endif (MSVC)

set_target_properties(pplib
    PROPERTIES
        PUBLIC_HEADER "ppapi.h;ppconf.h;pplib.h"
)

add_library(pplib::pplib ALIAS pplib)

install(TARGETS pplib
    EXPORT pplib
    DESTINATION lib
)

enable_testing()

list(APPEND tests pptest1 pptest2 pptest3)

foreach(_test IN LISTS tests)
    add_executable(${_test} repo/src/${_test}.c)
    target_link_libraries(${_test} PRIVATE pplib)

    add_test(
        NAME pplib.${_test}
        COMMAND $<TARGET_FILE:${_test}>
    )
endforeach()
