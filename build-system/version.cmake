execute_process(
  COMMAND git log -1 --format=%h
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_COMMIT
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
  COMMAND date "+%d %b %Y"
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE BUILD_DATE
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

configure_file (
  ${CMAKE_SOURCE_DIR}/src/Version.cpp
  ${CMAKE_BINARY_DIR}/src/Version.cpp
  @ONLY
)

add_library(Version ${CMAKE_BINARY_DIR}/src/Version.cpp)
target_compile_options(Version PRIVATE ${LLVM2GRAPHML_CXX_FLAGS} -fno-rtti)
target_include_directories(Version PUBLIC ${LLVM2GRAPHML_INCLUDE_DIRS})
target_include_directories(Version SYSTEM PUBLIC ${LLVM_INCLUDE_DIRS})

if (LLVM IN_LIST LLVM_AVAILABLE_LIBS)
  target_link_libraries(Version LLVM)
else()
  target_link_libraries(Version LLVMSupport)
endif()
