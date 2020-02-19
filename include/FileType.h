#pragma once

#include <string>

namespace llvm2graphml {

class Logger;
enum class FileType { Unsupported, Bitcode, Binary, LLVM_IR };
FileType getFileType(llvm2graphml::Logger &logger, const std::string &path);

} // namespace llvm2graphml