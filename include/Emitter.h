#pragma once

#include <llvm/IR/Instructions.h>
#include <unordered_map>

namespace llvm {

class Module;
class Function;
class BasicBlock;
class Instruction;
class ReturnInst;

} // namespace llvm

namespace llvm2graphml {

class Builder;
class Node;
class TypeEmitter;

class Emitter {
public:
  Emitter(Builder &builder, TypeEmitter &typeEmitter);
  void emit(const llvm::Module *module);

private:
  Builder &builder;
  TypeEmitter &typeEmitter;
  std::unordered_map<const llvm::Value *, Node *> emittedValues;

  void dispatchInstruction(const llvm::Instruction *instruction, Node *node);
  Node *emit(const llvm::Value *value);

  /// Extension points

  void fillIn(const llvm::Module *module, Node *node);
  void fillIn(const llvm::Function *function, Node *node);
  void fillIn(const llvm::BasicBlock *basicBlock, Node *node);

  void fillIn(const llvm::Argument *argument, Node *node);
  void fillIn(const llvm::ConstantInt *constant, Node *node);
  void fillIn(const llvm::ConstantFP *constant, Node *node);
  void fillIn(const llvm::ConstantPointerNull *constant, Node *node);
  void fillIn(const llvm::ConstantTokenNone *constant, Node *node);
  void fillIn(const llvm::UndefValue *undefValue, Node *node);
  void fillIn(const llvm::InlineAsm *inlineAsm, Node *node);
  void fillIn(const llvm::MetadataAsValue *metadataAsValue, llvm2graphml::Node *node);
  void fillIn(const llvm::BlockAddress *blockAddress, llvm2graphml::Node *node);
  void fillIn(const llvm::ConstantArray *constantArray, llvm2graphml::Node *node);
  void fillIn(const llvm::ConstantDataArray *constantArray, llvm2graphml::Node *node);
  void fillIn(const llvm::GlobalAlias *globalAlias, llvm2graphml::Node *node);
  void fillIn(const llvm::GlobalIFunc *globalIFunc, llvm2graphml::Node *node);
  void fillIn(const llvm::GlobalVariable *globalVariable, llvm2graphml::Node *node);
  void fillIn(const llvm::ConstantExpr *constantExpr, llvm2graphml::Node *node);
  void fillIn(const llvm::ConstantStruct *constantStruct, llvm2graphml::Node *node);
  void fillIn(const llvm::ConstantVector *constantVector, llvm2graphml::Node *node);
  void fillIn(const llvm::ConstantAggregateZero *constantZero, llvm2graphml::Node *node);
  void fillIn(const llvm::ConstantDataVector *constantVector, llvm2graphml::Node *node);

  void fillIn(const llvm::Instruction *instruction, Node *node);
  void fillIn(const llvm::ReturnInst *instruction, Node *node);
  void fillIn(const llvm::BranchInst *instruction, Node *node);
  void fillIn(const llvm::SwitchInst *instruction, Node *node);
  void fillIn(const llvm::IndirectBrInst *instruction, Node *node);
  void fillIn(const llvm::InvokeInst *instruction, Node *node);
  void fillIn(const llvm::ResumeInst *instruction, Node *node);
  void fillIn(const llvm::UnreachableInst *instruction, Node *node);
  void fillIn(const llvm::CleanupReturnInst *instruction, Node *node);
  void fillIn(const llvm::CatchReturnInst *instruction, Node *node);
  void fillIn(const llvm::CatchSwitchInst *instruction, Node *node);
  void fillIn(const llvm::CallBrInst *instruction, Node *node);
  void fillIn(const llvm::UnaryOperator *instruction, Node *node);
  void fillIn(const llvm::BinaryOperator *instruction, Node *node);
  void fillIn(const llvm::AllocaInst *instruction, Node *node);
  void fillIn(const llvm::LoadInst *instruction, Node *node);
  void fillIn(const llvm::StoreInst *instruction, Node *node);
  void fillIn(const llvm::GetElementPtrInst *instruction, Node *node);
  void fillIn(const llvm::FenceInst *instruction, Node *node);
  void fillIn(const llvm::AtomicCmpXchgInst *instruction, Node *node);
  void fillIn(const llvm::AtomicRMWInst *instruction, Node *node);
  void fillIn(const llvm::TruncInst *instruction, Node *node);
  void fillIn(const llvm::ZExtInst *instruction, Node *node);
  void fillIn(const llvm::SExtInst *instruction, Node *node);
  void fillIn(const llvm::FPToUIInst *instruction, Node *node);
  void fillIn(const llvm::FPToSIInst *instruction, Node *node);
  void fillIn(const llvm::UIToFPInst *instruction, Node *node);
  void fillIn(const llvm::SIToFPInst *instruction, Node *node);
  void fillIn(const llvm::FPTruncInst *instruction, Node *node);
  void fillIn(const llvm::FPExtInst *instruction, Node *node);
  void fillIn(const llvm::PtrToIntInst *instruction, Node *node);
  void fillIn(const llvm::IntToPtrInst *instruction, Node *node);
  void fillIn(const llvm::BitCastInst *instruction, Node *node);
  void fillIn(const llvm::AddrSpaceCastInst *instruction, Node *node);
  void fillIn(const llvm::CleanupPadInst *instruction, Node *node);
  void fillIn(const llvm::CatchPadInst *instruction, Node *node);
  void fillIn(const llvm::ICmpInst *instruction, Node *node);
  void fillIn(const llvm::FCmpInst *instruction, Node *node);
  void fillIn(const llvm::PHINode *instruction, Node *node);
  void fillIn(const llvm::CallInst *instruction, Node *node);
  void fillIn(const llvm::SelectInst *instruction, Node *node);
  void fillIn(const llvm::VAArgInst *instruction, Node *node);
  void fillIn(const llvm::ExtractElementInst *instruction, Node *node);
  void fillIn(const llvm::InsertElementInst *instruction, Node *node);
  void fillIn(const llvm::ShuffleVectorInst *instruction, Node *node);
  void fillIn(const llvm::ExtractValueInst *instruction, Node *node);
  void fillIn(const llvm::InsertValueInst *instruction, Node *node);
  void fillIn(const llvm::LandingPadInst *instruction, Node *node);
};

} // namespace llvm2graphml
