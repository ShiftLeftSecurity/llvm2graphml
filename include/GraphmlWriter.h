#pragma once

#include <string>

namespace llvm2graphml {

class Builder;

class GraphmlWriter {
public:
  void saveGraph(const Builder &builder, const std::string &output);

private:
};

} // namespace llvm2graphml
