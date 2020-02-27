#include "EdgeConnector.h"
#include "Builder.h"

using namespace llvm2graphml;

EdgeConnector::EdgeConnector(Builder &builder, Node &from) : builder(builder), from(from) {}

EdgeConnector *EdgeConnector::operator->() {
  return this;
}

Edge &EdgeConnector::edge(uint64_t to, EdgeKind kind) {
  return builder.newEdge(from.getID(), to).setKind(kind);
}

Edge &EdgeConnector::module(Node &to) {
  assert(to.getKind() == NodeKind::Module);
  return edge(to.getID(), EdgeKind::Module);
}

Edge &EdgeConnector::function(Node &to) {
  assert(to.getKind() == NodeKind::Function);
  return edge(to.getID(), EdgeKind::Function);
}

Edge &EdgeConnector::argument(const Node &to) {
  assert(to.getKind() == NodeKind::Argument);
  return edge(to.getID(), EdgeKind::Argument);
}

Edge &EdgeConnector::instruction(const Node &to) {
  assert(to.getKind() == NodeKind::Instruction);
  return edge(to.getID(), EdgeKind::Instruction);
}

Edge &EdgeConnector::basicBlock(const llvm2graphml::Node &to) {
  assert(to.getKind() == NodeKind::BasicBlock);
  return edge(to.getID(), EdgeKind::BasicBlock);
}

Edge &EdgeConnector::successor(const llvm2graphml::Node &to) {
  assert(to.getKind() == NodeKind::BasicBlock);
  assert(from.getKind() == NodeKind::BasicBlock);
  return edge(to.getID(), EdgeKind::Successor);
}

Edge &EdgeConnector::predecessor(const llvm2graphml::Node &to) {
  assert(to.getKind() == NodeKind::BasicBlock);
  assert(from.getKind() == NodeKind::BasicBlock);
  return edge(to.getID(), EdgeKind::Predecessor);
}

Edge &EdgeConnector::operand(const llvm2graphml::Node &to) {
  return edge(to.getID(), EdgeKind::Operand);
}

Edge &EdgeConnector::pointeeType(const Node &to) {
  assert(to.getKind() == NodeKind::Type);
  assert(from.getKind() == NodeKind::Type);

  return edge(to.getID(), EdgeKind::PointeeType);
}

Edge &EdgeConnector::returnType(const Node &to) {
  assert(to.getKind() == NodeKind::Type);
  assert(from.getKind() == NodeKind::Type);

  return edge(to.getID(), EdgeKind::ReturnType);
}

Edge &EdgeConnector::parameterType(const Node &to) {
  assert(to.getKind() == NodeKind::Type);
  assert(from.getKind() == NodeKind::Type);

  return edge(to.getID(), EdgeKind::ParameterType);
}

Edge &EdgeConnector::elementType(const Node &to) {
  assert(to.getKind() == NodeKind::Type);
  assert(from.getKind() == NodeKind::Type);

  return edge(to.getID(), EdgeKind::ElementType);
}

Edge &EdgeConnector::type(const Node &to) {
  assert(to.getKind() == NodeKind::Type);
  return edge(to.getID(), EdgeKind::Type);
}
