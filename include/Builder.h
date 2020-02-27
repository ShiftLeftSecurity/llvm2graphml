#pragma once

#include "Edge.h"
#include "Node.h"

#include <memory>
#include <vector>

#include <llvm/IR/Instructions.h>

namespace llvm2graphml {

class Builder {
public:
  Builder();

  Node &newModuleNode();
  Node &newFunctionNode();
  Node &newBasicBlockNode();
  Node &newInstructionNode();
  Node &newValueNode();
  Node &newArgumentNode();
  Node &newTypeNode();

  Edge &newEdge(uint64_t source, uint64_t target);

  const std::vector<std::unique_ptr<Node>> &getNodes() const;
  const std::vector<std::unique_ptr<Edge>> &getEdges() const;

private:
  Node &newNode(NodeKind kind);

  uint64_t currentId;

  std::vector<std::unique_ptr<Edge>> edges;
  std::vector<std::unique_ptr<Node>> nodes;
};

} // namespace llvm2graphml
