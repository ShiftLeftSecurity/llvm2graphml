#pragma once

#include "Properties.h"
#include <string>

namespace llvm2graphml {

enum class NodeKind { Module, Function };

class Node {
public:
  explicit Node(uint64_t id, NodeKind kind);

  void setModuleIdentifier(std::string identifier);
  void setName(std::string name);
  void setIsDeclaration(bool isDeclaration);
  void setIsVarArg(bool isVarArg);
  void setIsIntrinsic(bool isIntrinsic);
  void setNumOperands(uint64_t numOperands);
  void setArgSize(uint64_t argSize);
  void setInstructionCount(uint64_t instructionCount);
  void setBasicBlockCount(uint64_t basicBlockCount);

  const Properties &getProperties() const;
  uint64_t getID() const;
  NodeKind getKind() const;

private:
  uint64_t id;
  NodeKind kind;
  Properties properties;
};

} // namespace llvm2graphml
