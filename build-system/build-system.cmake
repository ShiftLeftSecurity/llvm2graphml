set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

include(${CMAKE_CURRENT_LIST_DIR}/vendor/vendor.cmake)

set (LLVM2GRAPHML_INCLUDE_DIRS
  ${CMAKE_SOURCE_DIR}/include
)

set (LLVM2GRAPHML_CXX_FLAGS
  -std=c++14
  -Wall
  -Werror
  -fno-exceptions
  -fvisibility=hidden
  -fvisibility-inlines-hidden
  -fno-rtti
  )

include(${CMAKE_CURRENT_LIST_DIR}/version.cmake)
