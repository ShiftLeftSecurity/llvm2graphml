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
  }
}

Edge::Edge(uint64_t id, uint64_t source, uint64_t target)
    : id(id), sourceId(source), targetId(target) {}

void Edge::setKind(EdgeKind kind) {
  properties.setStringProperty("labelE", edgeKindToString(kind));
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
