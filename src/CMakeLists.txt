set (SOURCES
  FileType.cpp
  Edge.cpp
  Node.cpp
  GraphmlWriter.cpp
  Properties.cpp
  Builder.cpp
  Logger.cpp
  BitcodeLoader.cpp
  Emitter.cpp
  TypeEmitter.cpp
  llvm2graphmlTool.cpp
  EdgeConnector.cpp
)

add_executable(llvm2graphml ${SOURCES})

if (LLVM IN_LIST LLVM_AVAILABLE_LIBS)
  set (LLVM_LINK_LIBS LLVM)
else()
  set (LLVM_LINK_LIBS LLVMCore LLVMSupport LLVMIRReader)
endif()

target_link_libraries(llvm2graphml Version ${LLVM_LINK_LIBS} ebc spdlog)
target_link_directories(llvm2graphml PRIVATE /usr/local/lib)
target_include_directories(llvm2graphml PRIVATE ${LLVM2GRAPHML_INCLUDE_DIRS})
target_compile_options(llvm2graphml PRIVATE ${LLVM2GRAPHML_CXX_FLAGS})
target_compile_definitions(llvm2graphml PUBLIC SPDLOG_NO_EXCEPTIONS)
install(TARGETS llvm2graphml
  RUNTIME DESTINATION bin
)