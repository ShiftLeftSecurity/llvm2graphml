#include "Node.h"
#include <utility>

using namespace llvm2graphml;

static std::string kindToString(NodeKind kind) {
  switch (kind) {
  case NodeKind::Module:
    return "module";
  case NodeKind::Function:
    return "function";
  case NodeKind::BasicBlock:
    return "basicBlock";
  }
}

Node::Node(uint64_t id, NodeKind kind) : id(id), kind(kind) {
  properties.setStringProperty("labelV", kindToString(kind));
}

const Properties &Node::getProperties() const {
  return properties;
}

uint64_t Node::getID() const {
  return id;
}

NodeKind Node::getKind() const {
  return kind;
}

void Node::setModuleIdentifier(std::string identifier) {
  properties.setStringProperty("moduleIdentifier", std::move(identifier));
}

void Node::setName(std::string name) {
  properties.setStringProperty("name", std::move(name));
}

void Node::setIsDeclaration(bool isDeclaration) {
  properties.setBooleanProperty("isDeclaration", isDeclaration);
}

void Node::setIsVarArg(bool isVarArg) {
  properties.setBooleanProperty("isVarArg", isVarArg);
}

void Node::setIsIntrinsic(bool isIntrinsic) {
  properties.setBooleanProperty("isIntrinsic", isIntrinsic);
}

void Node::setNumOperands(uint64_t numOperands) {
  properties.setLongProperty("numOperands", numOperands);
}

void Node::setArgSize(uint64_t argSize) {
  properties.setLongProperty("argSize", argSize);
}

void Node::setInstructionCount(uint64_t instructionCount) {
  properties.setLongProperty("instructionCount", instructionCount);
}

void Node::setBasicBlockCount(uint64_t basicBlockCount) {
  properties.setLongProperty("basicBlockCount", basicBlockCount);
}
