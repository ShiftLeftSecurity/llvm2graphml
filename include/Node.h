#pragma once

#include "Properties.h"
#include <string>

namespace llvm2graphml {

enum class NodeKind { Module, Function, BasicBlock, Instruction, Value };
enum class ValueKind {
  Argument,
  ConstantInt,
  ConstantFP,
  ConstantPointerNull,
  ConstantTokenNone,
  ConstantArray,
  ConstantDataArray,
  UndefValue,
  InlineAsm,
  MetadataAsValue,
  BlockAddress,
  GlobalAlias,
  GlobalIFunc,
  GlobalVariable,
  ConstantExpr,
  ConstantStruct,
  ConstantVector,
  ConstantAggregateZero,
  ConstantDataVector,
};

class Node {
public:
  explicit Node(uint64_t id, NodeKind kind);

  Node &setModuleIdentifier(std::string identifier);
  Node &setName(std::string name);
  Node &setIsDeclaration(bool isDeclaration);
  Node &setIsVarArg(bool isVarArg);
  Node &setIsIntrinsic(bool isIntrinsic);
  Node &setNumOperands(uint64_t numOperands);
  Node &setArgSize(uint64_t argSize);
  Node &setInstructionCount(uint64_t instructionCount);
  Node &setBasicBlockCount(uint64_t basicBlockCount);
  Node &setInstructionOpcode(const char *opcodeName);
  Node &setValueKind(ValueKind valueKind);

  const Properties &getProperties() const;
  uint64_t getID() const;
  NodeKind getKind() const;

private:
  uint64_t id;
  NodeKind kind;
  Properties properties;
};

} // namespace llvm2graphml
