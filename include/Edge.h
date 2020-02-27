#pragma once

#include "Properties.h"
#include <string>

namespace llvm2graphml {

enum class EdgeKind {
  Module,
  Function,
  BasicBlock,
  Argument,
  Successor,
  Predecessor,
  Instruction,
  Operand,
  PointeeType,
  ReturnType,
  ParameterType,
  ElementType,
  Type
};

class Edge {
public:
  Edge(uint64_t id, uint64_t source, uint64_t target);

  Edge &setKind(EdgeKind kind);
  Edge &setOrder(unsigned order);

  const Properties &getProperties() const;
  uint64_t getID() const;
  uint64_t getSourceID() const;
  uint64_t getTargetID() const;

private:
  uint64_t id;
  uint64_t sourceId;
  uint64_t targetId;
  Properties properties;
};

} // namespace llvm2graphml
