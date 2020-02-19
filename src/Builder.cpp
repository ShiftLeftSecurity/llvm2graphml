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

/// Edge Connectors

void Builder::connectModule(Node *moduleNode, Node *anyNode) {
  assert(moduleNode->getKind() == NodeKind::Module);
  Edge *edge = newEdge(anyNode->getID(), moduleNode->getID());
  edge->setKind(EdgeKind::Module);
}
