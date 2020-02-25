set(LIT_EXEC lit)
set(FILECHECK_EXEC filecheck)

if (GREMLIN_CONSOLE_EXEC)
  add_custom_target(gremlin)
else()
  include(ExternalProject)

  ExternalProject_Add(gremlin
    URL https://downloads.apache.org/tinkerpop/3.4.6/apache-tinkerpop-gremlin-console-3.4.6-bin.zip
    URL_HASH MD5=e810f5cc9890a23bdf5f4aca1b4f0471
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gremlin-console
    STAMP_DIR ${CMAKE_CURRENT_BINARY_DIR}/gremlin-console/stamp
    SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/gremlin-console/src
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/gremlin-console/build
    )
  set(GREMLIN_CONSOLE_EXEC ${CMAKE_CURRENT_BINARY_DIR}/gremlin-console/src/bin/gremlin.sh)
endif()

set(LIT_COMMAND
  CURRENT_DIR=${CMAKE_CURRENT_SOURCE_DIR}
  LLVM2GRAPHML_EXEC=$<TARGET_FILE:llvm2graphml>
  GREMLIN_CONSOLE_EXEC=${GREMLIN_CONSOLE_EXEC}
  FILECHECK_EXEC=${FILECHECK_EXEC}
  ${LIT_EXEC}
  -vv
  ${CMAKE_CURRENT_LIST_DIR}/integration-tests
  )

add_custom_target(graphml-integration-tests
  COMMAND ${LIT_COMMAND}
  DEPENDS llvm2graphml gremlin
)