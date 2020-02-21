#include "Node.h"
#include <utility>

using namespace llvm2graphml;

static std::string nodeKindToString(NodeKind kind) {
  switch (kind) {
  case NodeKind::Module:
    return "module";
  case NodeKind::Function:
    return "function";
  case NodeKind::BasicBlock:
    return "basicBlock";
  case NodeKind::Instruction:
    return "instruction";
  case NodeKind::Value:
    return "value";
  }
}

static std::string valueKindToString(ValueKind kind) {
  switch (kind) {
  case ValueKind::Argument:
    return "argument";
  case ValueKind::ConstantInt:
    return "constant_int";
  case ValueKind::ConstantFP:
    return "constant_fp";
  case ValueKind::ConstantPointerNull:
    return "constant_pointer_null";
  case ValueKind::ConstantTokenNone:
    return "constant_token_none";
  case ValueKind::UndefValue:
    return "undef_value";
  case ValueKind::ConstantArray:
    return "constant_array";
  case ValueKind::ConstantDataArray:
    return "constant_data_array";
  case ValueKind::InlineAsm:
    return "inline_asm";
  case ValueKind::MetadataAsValue:
    return "metadata_as_value";
  case ValueKind::BlockAddress:
    return "block_address";
  case ValueKind::GlobalAlias:
    return "global_alias";
  case ValueKind::GlobalIFunc:
    return "global_ifunc";
  case ValueKind::GlobalVariable:
    return "global_variable";
  case ValueKind::ConstantExpr:
    return "constant_expr";
  case ValueKind::ConstantStruct:
    return "constant_struct";
  case ValueKind::ConstantVector:
    return "constant_vector";
  case ValueKind::ConstantAggregateZero:
    return "constant_aggregate_zero";
  case ValueKind::ConstantDataVector:
    return "block_constant_data_vector";
  }
}

Node::Node(uint64_t id, NodeKind kind) : id(id), kind(kind) {
  properties.setStringProperty("labelV", nodeKindToString(kind));
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

Node &Node::setModuleIdentifier(std::string identifier) {
  properties.setStringProperty("moduleIdentifier", std::move(identifier));
  return *this;
}

Node &Node::setName(std::string name) {
  properties.setStringProperty("name", std::move(name));
  return *this;
}

Node &Node::setIsDeclaration(bool isDeclaration) {
  properties.setBooleanProperty("isDeclaration", isDeclaration);
  return *this;
}

Node &Node::setIsVarArg(bool isVarArg) {
  properties.setBooleanProperty("isVarArg", isVarArg);
  return *this;
}

Node &Node::setIsIntrinsic(bool isIntrinsic) {
  properties.setBooleanProperty("isIntrinsic", isIntrinsic);
  return *this;
}

Node &Node::setNumOperands(uint64_t numOperands) {
  properties.setLongProperty("numOperands", numOperands);
  return *this;
}

Node &Node::setArgSize(uint64_t argSize) {
  properties.setLongProperty("argSize", argSize);
  return *this;
}

Node &Node::setInstructionCount(uint64_t instructionCount) {
  properties.setLongProperty("instructionCount", instructionCount);
  return *this;
}

Node &Node::setBasicBlockCount(uint64_t basicBlockCount) {
  properties.setLongProperty("basicBlockCount", basicBlockCount);
  return *this;
}

Node &Node::setInstructionOpcode(const char *opcodeName) {
  properties.setStringProperty("opcode", opcodeName);
  return *this;
}

Node &Node::setValueKind(llvm2graphml::ValueKind valueKind) {
  properties.setStringProperty("kind", valueKindToString(valueKind));
  return *this;
}
