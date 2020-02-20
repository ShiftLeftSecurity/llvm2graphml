#pragma once

#include "Edge.h"
#include "Node.h"

#include <memory>
#include <vector>

namespace llvm2graphml {

class Builder {
public:
  Node *newModuleNode();
  Node *newFunctionNode();
  Node *newBasicBlockNode();

  void connectModule(Node *moduleNode, Node *anyNode);
  void connectFunction(Node *functionNode, Node *anyNode);
  void connectBasicBlocks(Node *successor, Node *predecessor);

  const std::vector<std::unique_ptr<Node>> &getNodes() const;
  const std::vector<std::unique_ptr<Edge>> &getEdges() const;

private:
  Node *newNode(NodeKind kind);
  Edge *newEdge(uint64_t source, uint64_t target);

  uint64_t currentId;

  std::vector<std::unique_ptr<Edge>> edges;
  std::vector<std::unique_ptr<Node>> nodes;
};

} // namespace llvm2graphml
