#include "Properties.h"
#include <utility>

using namespace llvm2graphml;

static std::string dropUnsupportedXmlChars(const std::string &input) {
  std::string output;
  output.reserve(input.size());
  for (char c : input) {
    if (iscntrl(c) && (c != 0x9) && (c != 0xa) && (c != 0xd)) {
      continue;
    }
    output.push_back(c);
  }

  return output;
}

void Properties::setStringProperty(const std::string &key, const std::string &value) {
  strings[key] = dropUnsupportedXmlChars(value);
}

void Properties::setBooleanProperty(const std::string &key, bool value) {
  booleans[key] = value;
}

void Properties::setLongProperty(const std::string &key, uint64_t value) {
  longs[key] = value;
}

const std::unordered_map<std::string, std::string> &Properties::getStrings() const {
  return strings;
}

const std::unordered_map<std::string, bool> &Properties::getBooleans() const {
  return booleans;
}

const std::unordered_map<std::string, uint64_t> &Properties::getLongs() const {
  return longs;
}
