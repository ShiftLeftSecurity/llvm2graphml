#include "Builder.h"

using namespace llvm2graphml;

Builder::Builder() : currentId(0) {}

const std::vector<std::unique_ptr<Node>> &Builder::getNodes() const {
  return nodes;
}

const std::vector<std::unique_ptr<Edge>> &Builder::getEdges() const {
  return edges;
}

Node *Builder::newNode(NodeKind kind) {
  nodes.emplace_back(new Node(currentId++, kind));
  return nodes.back().get();
}

Edge *Builder::newEdge(uint64_t source, uint64_t target) {
  edges.emplace_back(new Edge(currentId++, source, target));
  return edges.back().get();
}

/// Node Constructors

Node *Builder::newModuleNode() {
  return newNode(NodeKind::Module);
}

Node *Builder::newFunctionNode() {
  return newNode(NodeKind::Function);
}

Node *Builder::newBasicBlockNode() {
  return newNode(NodeKind::BasicBlock);
}

Node *Builder::newInstructionNode() {
  return newNode(NodeKind::Instruction);
}

Node *Builder::newValueNode() {
  return newNode(NodeKind::Value);
}

Node *Builder::newTypeNode() {
  return newNode(NodeKind::Type);
}

/// Edge Connectors

void Builder::connectModule(Node *moduleNode, Node *anyNode) {
  assert(moduleNode->getKind() == NodeKind::Module);

  newEdge(anyNode->getID(), moduleNode->getID())->setKind(EdgeKind::Module);
}

void Builder::connectFunction(Node *functionNode, Node *anyNode) {
  assert(functionNode->getKind() == NodeKind::Function);

  newEdge(anyNode->getID(), functionNode->getID())->setKind(EdgeKind::Function);
}

void Builder::connectArgument(Node *functionNode, Node *argumentNode, unsigned order) {
  assert(functionNode->getKind() == NodeKind::Function);

  Edge *edge = newEdge(functionNode->getID(), argumentNode->getID());
  edge->setKind(EdgeKind::Argument);
  edge->setOrder(order);
}

void Builder::connectInstruction(Node *instructionNode, Node *anyNode) {
  assert(instructionNode->getKind() == NodeKind::Instruction);

  newEdge(anyNode->getID(), instructionNode->getID())->setKind(EdgeKind::Instruction);
}

void Builder::connectBasicBlocks(Node *successor, Node *predecessor) {
  assert(successor->getKind() == NodeKind::BasicBlock);
  assert(predecessor->getKind() == NodeKind::BasicBlock);

  newEdge(predecessor->getID(), successor->getID())->setKind(EdgeKind::Successor);
  newEdge(successor->getID(), predecessor->getID())->setKind(EdgeKind::Predecessor);
}

void Builder::connectOperand(Node *instructionNode, Node *anyValue, unsigned order) {
  assert(instructionNode->getKind() == NodeKind::Instruction);

  Edge *edge = newEdge(instructionNode->getID(), anyValue->getID());
  edge->setKind(EdgeKind::Operand);
  edge->setOrder(order);
}

void Builder::connectPointeeType(Node *pointerNode, Node *pointeeNode) {
  assert(pointerNode->getKind() == NodeKind::Type);
  assert(pointeeNode->getKind() == NodeKind::Type);

  newEdge(pointerNode->getID(), pointeeNode->getID())->setKind(EdgeKind::PointeeType);
}

void Builder::connectFunctionParameterType(Node *functionType, Node *parameterType,
                                           unsigned order) {
  assert(functionType->getKind() == NodeKind::Type);
  assert(parameterType->getKind() == NodeKind::Type);

  Edge *edge = newEdge(functionType->getID(), parameterType->getID());
  edge->setKind(EdgeKind::ParameterType);
  edge->setOrder(order);
}

void Builder::connectFunctionReturnType(Node *functionType, Node *returnType) {
  assert(functionType->getKind() == NodeKind::Type);
  assert(returnType->getKind() == NodeKind::Type);

  newEdge(functionType->getID(), returnType->getID())->setKind(EdgeKind::ReturnType);
}

void Builder::connectStructElementType(llvm2graphml::Node *structType,
                                       llvm2graphml::Node *elementType, unsigned order) {
  assert(structType->getKind() == NodeKind::Type);
  assert(elementType->getKind() == NodeKind::Type);

  Edge *edge = newEdge(structType->getID(), elementType->getID());
  edge->setKind(EdgeKind::ElementType);
  edge->setOrder(order);
}

void Builder::connectElementType(Node *type, Node *elementType) {
  assert(type->getKind() == NodeKind::Type);
  assert(elementType->getKind() == NodeKind::Type);

  newEdge(type->getID(), elementType->getID())->setKind(EdgeKind::ElementType);
}

void Builder::connectType(Node *type, Node *node) {
  assert(type->getKind() == NodeKind::Type);

  newEdge(node->getID(), type->getID())->setKind(EdgeKind::Type);
}
