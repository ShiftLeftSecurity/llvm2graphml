#include "Builder.h"

using namespace llvm2graphml;

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

/// Edge Connectors

void Builder::connectModule(Node *moduleNode, Node *anyNode) {
  assert(moduleNode->getKind() == NodeKind::Module);

  newEdge(anyNode->getID(), moduleNode->getID())->setKind(EdgeKind::Module);
}

void Builder::connectFunction(Node *functionNode, Node *anyNode) {
  assert(functionNode->getKind() == NodeKind::Function);

  newEdge(anyNode->getID(), functionNode->getID())->setKind(EdgeKind::Function);
}

void Builder::connectBasicBlocks(Node *successor, Node *predecessor) {
  assert(successor->getKind() == NodeKind::BasicBlock);
  assert(predecessor->getKind() == NodeKind::BasicBlock);

  newEdge(predecessor->getID(), successor->getID())->setKind(EdgeKind::Successor);
  newEdge(successor->getID(), predecessor->getID())->setKind(EdgeKind::Predecessor);
}
