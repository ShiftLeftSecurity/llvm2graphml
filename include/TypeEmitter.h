#pragma once

#include <llvm/IR/DerivedTypes.h>
#include <unordered_map>

namespace llvm {

class Type;

}

namespace llvm2graphml {

class Node;
class Builder;

class TypeEmitter {
public:
  explicit TypeEmitter(Builder &builder);
  Node *emitType(const llvm::Type *type);

private:
  Builder &builder;
  std::unordered_map<const llvm::Type *, Node *> emittedTypes;

  void dispatchType(const llvm::Type *type, Node *node);

  // Extension Points
  void fillIn(const llvm::IntegerType *type, Node *node);
  void fillIn(const llvm::FunctionType *type, Node *node);
  void fillIn(const llvm::StructType *type, Node *node);
  void fillIn(const llvm::ArrayType *type, Node *node);
  void fillIn(const llvm::PointerType *type, Node *node);
  void fillIn(const llvm::VectorType *type, Node *node);
};

} // namespace llvm2graphml
