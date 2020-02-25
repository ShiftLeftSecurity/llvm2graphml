#pragma once

#include <string>
#include <unordered_map>

namespace llvm2graphml {

class Properties {
public:
  void setStringProperty(const std::string &key, const std::string &value);
  void setBooleanProperty(const std::string &key, bool value);
  void setLongProperty(const std::string &key, uint64_t value);

  const std::unordered_map<std::string, std::string> &getStrings() const;
  const std::unordered_map<std::string, bool> &getBooleans() const;
  const std::unordered_map<std::string, uint64_t> &getLongs() const;

private:
  std::unordered_map<std::string, std::string> strings;
  std::unordered_map<std::string, bool> booleans;
  std::unordered_map<std::string, uint64_t> longs;
};

} // namespace llvm2graphml
