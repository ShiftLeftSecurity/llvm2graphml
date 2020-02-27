#pragma once

#include "EdgeConnector.h"
#include "Properties.h"
#include <string>

namespace llvm2graphml {

enum class NodeKind { Module, Function, Argument, BasicBlock, Instruction, Value, Type };

enum class ValueKind {
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

enum class TypeKind {
  Integer,
  Void,
  Half,
  Float,
  Double,
  X86_FP80,
  FP128,
  PPC_FP128,
  Metadata,
  X86_MMX,
  Token,
  Function,
  Struct,
  Array,
  Pointer,
  Vector,
  Label
};

class Builder;

class Edge;
class Node;

class Node {
public:
  explicit Node(Builder &builder, uint64_t id, NodeKind kind);

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
  Node &setTypeKind(TypeKind typeKind);
  Node &setBitwidth(uint64_t bitwidth);

  const Properties &getProperties() const;
  uint64_t getID() const;
  NodeKind getKind() const;

  EdgeConnector operator->();

private:
  Builder &builder;
  uint64_t id;
  NodeKind kind;
  Properties properties;
};

} // namespace llvm2graphml
