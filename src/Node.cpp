#include "Node.h"
#include "Builder.h"
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
  case NodeKind::Type:
    return "type";
  }
}

static std::string valueKindToString(ValueKind kind) {
  switch (kind) {
  case ValueKind::Argument:
    return "argument";
  case ValueKind::ConstantInt:
    return "constantInt";
  case ValueKind::ConstantFP:
    return "constantFP";
  case ValueKind::ConstantPointerNull:
    return "constantPointerNull";
  case ValueKind::ConstantTokenNone:
    return "constantTokenNone";
  case ValueKind::UndefValue:
    return "undefValue";
  case ValueKind::ConstantArray:
    return "constantArray";
  case ValueKind::ConstantDataArray:
    return "constantDataArray";
  case ValueKind::InlineAsm:
    return "inlineAsm";
  case ValueKind::MetadataAsValue:
    return "metadataAsValue";
  case ValueKind::BlockAddress:
    return "blockAddress";
  case ValueKind::GlobalAlias:
    return "globalAlias";
  case ValueKind::GlobalIFunc:
    return "globalIFunc";
  case ValueKind::GlobalVariable:
    return "globalVariable";
  case ValueKind::ConstantExpr:
    return "constantExpr";
  case ValueKind::ConstantStruct:
    return "constantStruct";
  case ValueKind::ConstantVector:
    return "constantVector";
  case ValueKind::ConstantAggregateZero:
    return "constantAggregateZero";
  case ValueKind::ConstantDataVector:
    return "constantDataVector";
  }
}

static std::string typeKindToString(TypeKind kind) {
  switch (kind) {
  case TypeKind::Integer:
    return "integer";
  case TypeKind::Void:
    return "void";
  case TypeKind::Half:
    return "half";
  case TypeKind::Float:
    return "float";
  case TypeKind::Double:
    return "double";
  case TypeKind::X86_FP80:
    return "x86_fp80";
  case TypeKind::FP128:
    return "fp128";
  case TypeKind::PPC_FP128:
    return "ppc_fp128";
  case TypeKind::Metadata:
    return "metadata";
  case TypeKind::X86_MMX:
    return "x86_mmx";
  case TypeKind::Token:
    return "token";
  case TypeKind::Function:
    return "function";
  case TypeKind::Struct:
    return "struct";
  case TypeKind::Array:
    return "array";
  case TypeKind::Pointer:
    return "pointer";
  case TypeKind::Vector:
    return "vector";
  case TypeKind::Label:
    return "label";
  }
}

Node::Node(Builder &builder, uint64_t id, NodeKind kind) : builder(builder), id(id), kind(kind) {
  properties.setStringProperty("labelV", nodeKindToString(kind));
}

EdgeConnector Node::operator->() {
  return EdgeConnector(builder, *this);
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

Node &Node::setTypeKind(TypeKind typeKind) {
  properties.setStringProperty("typeID", typeKindToString(typeKind));
  return *this;
}

Node &Node::setBitwidth(uint64_t bitwidth) {
  properties.setLongProperty("bitwidth", bitwidth);
  return *this;
}
