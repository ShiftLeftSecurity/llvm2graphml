cmake_minimum_required(VERSION 3.15)

project(llvm2graphml
        VERSION 0.1.0
        LANGUAGES C CXX
        )

include(${CMAKE_CURRENT_LIST_DIR}/build-system/build-system.cmake)

add_subdirectory(src)
add_subdirectory(tests)