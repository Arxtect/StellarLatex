cmake_minimum_required(VERSION 3.5)

file(GLOB STATIC_LIBS "${CMAKE_CURRENT_SOURCE_DIR}/lib*.a")

if(STATIC_LIBS)
    install(
        FILES ${STATIC_LIBS}
        DESTINATION lib
    )
endif()
