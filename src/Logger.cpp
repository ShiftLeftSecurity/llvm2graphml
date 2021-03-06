#include "Logger.h"
#include <llvm/Support/FileSystem.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

using namespace llvm2graphml;

static std::string getDebugLogPath() {
  llvm::Twine model("llvm2graphml-%%%%%%.log");
  llvm::SmallString<128> output;
  llvm::sys::fs::createUniquePath(model, output, true);
  return output.str();
}

static std::shared_ptr<spdlog::sinks::sink> stdoutSink() {
  return std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
}

static std::shared_ptr<spdlog::sinks::sink> fileSink(const std::string &path) {
  return std::make_shared<spdlog::sinks::basic_file_sink_mt>(path);
}

Logger::Logger()
    : debugLogPath(getDebugLogPath()),
      stdoutLog(std::make_shared<spdlog::logger>("llvm2graphml", stdoutSink())),
      fileLog(std::make_shared<spdlog::logger>("file", fileSink(debugLogPath))) {
  fileLog->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");
  fileLog->flush_on(spdlog::level::info);
  fileLog->flush_on(spdlog::level::warn);
}

void Logger::uiInfo(const std::string &message) {
  stdoutLog->info(message);
}

void Logger::uiWarning(const std::string &message) {
  stdoutLog->warn(message);
}

void Logger::uiFatal(const std::string &message) {
  stdoutLog->critical(message);
}

void Logger::logInfo(const std::string &message) {
  fileLog->info(message);
}

void Logger::logWarning(const std::string &message) {
  fileLog->warn(message);
}

const std::string &Logger::getLogPath() {
  return debugLogPath;
}