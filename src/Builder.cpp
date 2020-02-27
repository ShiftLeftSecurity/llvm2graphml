#include "Builder.h"

using namespace llvm2graphml;

Builder::Builder() : currentId(0) {}

const std::vector<std::unique_ptr<Node>> &Builder::getNodes() const {
  return nodes;
}

const std::vector<std::unique_ptr<Edge>> &Builder::getEdges() const {
  return edges;
}

Node &Builder::newNode(NodeKind kind) {
  nodes.emplace_back(new Node(*this, currentId++, kind));
  return *nodes.back().get();
}

Edge &Builder::newEdge(uint64_t source, uint64_t target) {
  edges.emplace_back(new Edge(currentId++, source, target));
  return *edges.back().get();
}

/// Node Constructors

Node &Builder::newModuleNode() {
  return newNode(NodeKind::Module);
}

Node &Builder::newFunctionNode() {
  return newNode(NodeKind::Function);
}

Node &Builder::newBasicBlockNode() {
  return newNode(NodeKind::BasicBlock);
}

Node &Builder::newInstructionNode() {
  return newNode(NodeKind::Instruction);
}

Node &Builder::newValueNode() {
  return newNode(NodeKind::Value);
}

Node &Builder::newArgumentNode() {
  return newNode(NodeKind::Argument);
}

Node &Builder::newTypeNode() {
  return newNode(NodeKind::Type);
}
