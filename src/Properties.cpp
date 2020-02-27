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

void replace(std::string &input, char c, const char *replacement) {
  size_t pos = input.find(c);
  while (pos != std::string::npos) {
    input.replace(pos, 1, replacement);
    pos = input.find(c, pos + 1);
  }
}

static std::string escapeSpecialXmlCharacters(const std::string &input) {
  std::string output = input;
  replace(output, '&', "&amp;");
  replace(output, '"', "&quot;");
  replace(output, '\'', "&apos;");
  replace(output, '<', "&lt;");
  replace(output, '>', "&gt;");
  return output;
}

static std::string sanitize(const std::string &input) {
  return escapeSpecialXmlCharacters(dropUnsupportedXmlChars(input));
}

void Properties::setStringProperty(const std::string &key, const std::string &value) {
  strings[key] = sanitize(value);
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
