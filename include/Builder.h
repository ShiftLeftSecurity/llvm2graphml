#pragma once

#include "Edge.h"
#include "Node.h"

#include <memory>
#include <vector>

#include <llvm/IR/Instructions.h>

namespace llvm2graphml {

class Builder {
public:
  Node *newModuleNode();
  Node *newFunctionNode();
  Node *newBasicBlockNode();
  Node *newInstructionNode();
  Node *newValueNode();

  void connectModule(Node *moduleNode, Node *anyNode);
  void connectFunction(Node *functionNode, Node *anyNode);
  void connectInstruction(Node *instructionNode, Node *anyNode);
  void connectBasicBlocks(Node *successor, Node *predecessor);
  void connectOperand(Node *instructionNode, Node *anyValue, unsigned index);

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
