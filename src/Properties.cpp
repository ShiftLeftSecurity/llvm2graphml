#include "Properties.h"
#include <utility>

using namespace llvm2graphml;

void Properties::setStringProperty(const std::string& key, std::string value) {
  strings[key] = std::move(value);
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
