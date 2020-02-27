#include "Edge.h"

using namespace llvm2graphml;

static std::string edgeKindToString(EdgeKind kind) {
  switch (kind) {
  case EdgeKind::Module:
    return "module";
  case EdgeKind::Function:
    return "function";
  case EdgeKind::Successor:
    return "successor";
  case EdgeKind::Predecessor:
    return "predecessor";
  case EdgeKind::Instruction:
    return "instruction";
  case EdgeKind::Operand:
    return "operand";
  case EdgeKind::PointeeType:
    return "pointee_type";
  case EdgeKind::ReturnType:
    return "return_type";
  case EdgeKind::ParameterType:
    return "parameter_type";
  case EdgeKind::ElementType:
    return "element_type";
  case EdgeKind::Argument:
    return "argument";
  case EdgeKind::Type:
    return "type";
  case EdgeKind::BasicBlock:
    return "basic_block";
  }
}

Edge::Edge(uint64_t id, uint64_t source, uint64_t target)
    : id(id), sourceId(source), targetId(target) {}

Edge &Edge::setKind(EdgeKind kind) {
  properties.setStringProperty("labelE", edgeKindToString(kind));
  return *this;
}

const Properties &Edge::getProperties() const {
  return properties;
}

uint64_t Edge::getID() const {
  return id;
}

uint64_t Edge::getSourceID() const {
  return sourceId;
}

uint64_t Edge::getTargetID() const {
  return targetId;
}

Edge &Edge::setOrder(unsigned order) {
  properties.setLongProperty("order", order);
  return *this;
}
