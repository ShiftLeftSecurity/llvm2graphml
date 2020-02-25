cmake_minimum_required(VERSION 3.15)

set (LLVM2GRAPHML_VERSION 0.1.0)

project(llvm2graphml
        VERSION ${LLVM2GRAPHML_VERSION}
        LANGUAGES CXX
        )

set (PROJECT_DESCRIPTION "llvm2graphml converts LLVM Bitcode to GraphML")
set (PROJECT_HOMEPAGE_URL "https://github.com/ShiftLeftSecurity/llvm2graphml")

include(${CMAKE_CURRENT_LIST_DIR}/build-system/build-system.cmake)

add_subdirectory(src)
add_subdirectory(tests)