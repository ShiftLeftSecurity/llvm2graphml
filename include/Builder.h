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

  Node *newModuleNode();
  Node *newFunctionNode();
  Node *newBasicBlockNode();
  Node *newInstructionNode();
  Node *newValueNode();
  Node *newTypeNode();

  void connectModule(Node *moduleNode, Node *anyNode);
  void connectFunction(Node *functionNode, Node *anyNode);
  void connectArgument(Node *functionNode, Node *argumentNode, unsigned order);
  void connectInstruction(Node *instructionNode, Node *anyNode);
  void connectBasicBlocks(Node *successor, Node *predecessor);
  void connectOperand(Node *instructionNode, Node *anyValue, unsigned order);
  void connectPointeeType(Node *pointerNode, Node *pointeeNode);
  void connectFunctionReturnType(Node *functionType, Node *returnType);
  void connectFunctionParameterType(Node *functionType, Node *parameterType, unsigned order);
  void connectStructElementType(Node *structType, Node *elementType, unsigned order);
  void connectElementType(Node *type, Node *elementType);
  void connectType(Node *type, Node *node);

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
