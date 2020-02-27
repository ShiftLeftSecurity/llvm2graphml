#include "TypeEmitter.h"
#include "Builder.h"
#include <llvm/IR/Type.h>

using namespace llvm2graphml;

static TypeKind typeIdToTypeKind(llvm::Type::TypeID typeId) {
  switch (typeId) {
#define HANDLE_TYPE(Name)                                                                          \
  case llvm::Type::Name##TyID:                                                                     \
    return TypeKind::Name;
#include "Types.def"
  }
}

TypeEmitter::TypeEmitter(Builder &builder) : builder(builder) {}

Node &TypeEmitter::emitType(const llvm::Type *type) {
  if (emittedTypes.count(type)) {
    return *emittedTypes[type];
  }
  Node &typeNode = builder.newTypeNode();
  emittedTypes[type] = &typeNode;
  typeNode.setTypeKind(typeIdToTypeKind(type->getTypeID()));

  switch (type->getTypeID()) {
  case llvm::Type::VoidTyID:
  case llvm::Type::HalfTyID:
  case llvm::Type::FloatTyID:
  case llvm::Type::DoubleTyID:
  case llvm::Type::X86_FP80TyID:
  case llvm::Type::FP128TyID:
  case llvm::Type::PPC_FP128TyID:
  case llvm::Type::LabelTyID:
  case llvm::Type::MetadataTyID:
  case llvm::Type::X86_MMXTyID:
  case llvm::Type::TokenTyID:
  case llvm::Type::IntegerTyID:
    break;
  case llvm::Type::FunctionTyID: {
    auto functionType = llvm::cast<llvm::FunctionType>(type);
    Node &returnType = emitType(functionType->getReturnType());
    typeNode->returnType(returnType);

    for (unsigned i = 0; i < functionType->getFunctionNumParams(); i++) {
      Node &parameterType = emitType(functionType->getFunctionParamType(i));
      typeNode->parameterType(parameterType).setOrder(i);
    }
  } break;
  case llvm::Type::StructTyID: {
    for (unsigned i = 0; i < type->getStructNumElements(); i++) {
      Node &elementType = emitType(type->getStructElementType(i));
      typeNode->elementType(elementType).setOrder(i);
    }
  } break;
  case llvm::Type::ArrayTyID: {
    Node &elementType = emitType(type->getArrayElementType());
    typeNode->elementType(elementType);
  } break;
  case llvm::Type::PointerTyID: {
    Node &pointeeNode = emitType(type->getPointerElementType());
    typeNode->pointeeType(pointeeNode);
  } break;
  case llvm::Type::VectorTyID: {
    Node &elementType = emitType(type->getVectorElementType());
    typeNode->elementType(elementType);
  } break;
  }

  dispatchType(type, typeNode);

  return typeNode;
}

void TypeEmitter::dispatchType(const llvm::Type *type, Node &node) {
  switch (type->getTypeID()) {
#define HANDLE_DERIVED_TYPE(Name)                                                                  \
  case llvm::Type::Name##TyID:                                                                     \
    fillIn(llvm::cast<llvm::Name##Type>(type), node);                                              \
    break;
#include "Types.def"
  default:
    break;
  }
}

// Extension points

void TypeEmitter::fillIn(const llvm::IntegerType *type, Node &node) {
  node.setBitwidth(type->getBitWidth());
}

void TypeEmitter::fillIn(const llvm::StructType *type, Node &node) {
  if (type->hasName()) {
    node.setName(type->getName());
  }
}

void TypeEmitter::fillIn(const llvm::FunctionType *type, Node &node) {}
void TypeEmitter::fillIn(const llvm::ArrayType *type, Node &node) {}
void TypeEmitter::fillIn(const llvm::PointerType *type, Node &node) {}
void TypeEmitter::fillIn(const llvm::VectorType *type, Node &node) {}
