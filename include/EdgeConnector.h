#pragma once

#include <cstdint>

namespace llvm2graphml {

class Builder;
class Node;
class Edge;
enum class EdgeKind;

class EdgeConnector {
public:
  friend Node;

  EdgeConnector *operator->();
  Edge &module(Node &to);
  Edge &function(Node &to);
  Edge &argument(const Node &to);
  Edge &instruction(const Node &to);
  Edge &basicBlock(const Node &to);
  Edge &successor(const Node &to);
  Edge &predecessor(const Node &to);
  Edge &operand(const Node &to);
  Edge &pointeeType(const Node &to);
  Edge &returnType(const Node &to);
  Edge &parameterType(const Node &to);
  Edge &elementType(const Node &to);
  Edge &type(const Node &to);

private:
  EdgeConnector(Builder &builder, Node &from);
  Edge &edge(uint64_t to, EdgeKind kind);

  Builder &builder;
  Node &from;
};

} // namespace llvm2graphml
