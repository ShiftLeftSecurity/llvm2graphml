#include "Emitter.h"
#include "Builder.h"
#include "TypeEmitter.h"
#include <llvm/IR/CFG.h>
#include <llvm/IR/InstIterator.h>
#include <llvm/IR/Module.h>

using namespace llvm2graphml;

Emitter::Emitter(Builder &builder, TypeEmitter &typeEmitter)
    : builder(builder), typeEmitter(typeEmitter) {}

void Emitter::emit(const llvm::Module *module) {
  Node *moduleNode = builder.newModuleNode();
  fillIn(module, moduleNode);
  for (const llvm::Function &function : module->getFunctionList()) {
    /// Emission
    Node *functionNode = emit(&function);
    builder.connectFunction(functionNode, moduleNode);
    builder.connectModule(moduleNode, functionNode);

    unsigned argumentIndex = 0;
    for (const llvm::Argument &argument : function.args()) {
      Node *argumentNode = emit(&argument);
      builder.connectArgument(functionNode, argumentNode, argumentIndex++);
    }

    for (const llvm::BasicBlock &basicBlock : function.getBasicBlockList()) {
      Node *basicBlockNode = emit(&basicBlock);
      builder.connectFunction(functionNode, basicBlockNode);
      builder.connectModule(moduleNode, basicBlockNode);

      for (const llvm::Instruction &instruction : basicBlock.getInstList()) {
        Node *instructionNode = emit(&instruction);
        builder.connectInstruction(instructionNode, basicBlockNode);
      }
    }

    /// Connection
    for (const llvm::BasicBlock &block : function.getBasicBlockList()) {
      Node *blockNode = emittedValues[&block];
      for (const llvm::BasicBlock *predecessor : llvm::predecessors(&block)) {
        Node *predecessorNode = emittedValues[predecessor];
        builder.connectBasicBlocks(blockNode, predecessorNode);
      }
    }
    for (const llvm::Instruction &instruction : llvm::instructions(function)) {
      Node *instructionNode = emittedValues[&instruction];
      assert(instructionNode && "Instruction should be emitted by this time");
      for (unsigned i = 0; i < instruction.getNumOperands(); i++) {
        Node *operandNode = emittedValues[instruction.getOperand(i)];
        assert(operandNode);
        builder.connectOperand(instructionNode, operandNode, i);
      }
    }
  }
}

void Emitter::dispatchInstruction(const llvm::Instruction *instruction, Node *node) {
  using namespace llvm;
  switch (instruction->getOpcode()) {
  default:
    llvm_unreachable("Unknown instruction type encountered!");
    // Build the switch statement using the Instruction.def file...
#define HANDLE_INST(NUM, OPCODE, CLASS)                                                            \
  case Instruction::OPCODE:                                                                        \
    fillIn(llvm::cast<CLASS>(instruction), node);                                                  \
    break;
#include "llvm/IR/Instruction.def"
#undef HANDLE_INST
  }
}

Node *Emitter::emit(const llvm::Value *value) {
  if (emittedValues.count(value)) {
    return emittedValues[value];
  }

  Node *emittedNode = nullptr;

  if (const auto *instruction = llvm::dyn_cast<llvm::Instruction>(value)) {
    emittedNode = builder.newInstructionNode();
    fillIn(instruction, emittedNode);
    dispatchInstruction(instruction, emittedNode);
    for (unsigned i = 0; i < instruction->getNumOperands(); i++) {
      emit(instruction->getOperand(i));
    }
  } else {
    switch (value->getValueID()) {
    case llvm::Value::FunctionVal: {
      emittedNode = builder.newFunctionNode();
      fillIn(llvm::cast<llvm::Function>(value), emittedNode);
    } break;
    case llvm::Value::BasicBlockVal: {
      emittedNode = builder.newBasicBlockNode();
      fillIn(llvm::cast<llvm::BasicBlock>(value), emittedNode);
    } break;

#define GRAPHML_HANDLE_VALUE(Name)                                                                 \
  case Value::Name##Val: {                                                                         \
    emittedNode = builder.newValueNode();                                                          \
    emittedNode->setValueKind(ValueKind::Name);                                                    \
    fillIn(llvm::cast<Name>(value), emittedNode);                                                  \
  } break;

#define HANDLE_CONSTANT(Name) GRAPHML_HANDLE_VALUE(Name)
#define HANDLE_METADATA_VALUE(Name) GRAPHML_HANDLE_VALUE(Name)
#define HANDLE_INLINE_ASM_VALUE(Name) GRAPHML_HANDLE_VALUE(Name)
#define HANDLE_GLOBAL_VALUE(Name) /* handled above explicitly */

      using namespace llvm;
      GRAPHML_HANDLE_VALUE(GlobalAlias)
      GRAPHML_HANDLE_VALUE(GlobalIFunc)
      GRAPHML_HANDLE_VALUE(GlobalVariable)
      GRAPHML_HANDLE_VALUE(Argument)
#include "llvm/IR/Value.def"
#undef GRAPHML_HANDLE_VALUE
    default:
      llvm::errs() << *value << " " << value->getValueID() << "\n";
      llvm_unreachable("Unhandled value");
    }
  }

  if (value->hasName() && emittedNode) {
    emittedNode->setName(value->getName());
  }
  emittedValues[value] = emittedNode;
  Node *typeNode = typeEmitter.emitType(value->getType());
  builder.connectType(typeNode, emittedNode);

  return emittedNode;
}

/// Extension Points

void Emitter::fillIn(const llvm::Module *module, llvm2graphml::Node *node) {
  (*node) //
      .setModuleIdentifier(module->getModuleIdentifier());
}

void Emitter::fillIn(const llvm::Function *function, llvm2graphml::Node *node) {
  (*node) //
      .setName(function->getName())
      .setIsDeclaration(function->isDeclaration())
      .setIsVarArg(function->isVarArg())
      .setNumOperands(function->getNumOperands())
      .setArgSize(function->arg_size())
      .setIsIntrinsic(function->isIntrinsic())
      .setInstructionCount(function->getInstructionCount())
      .setBasicBlockCount(function->size());
}

void Emitter::fillIn(const llvm::BasicBlock *basicBlock, llvm2graphml::Node *node) {
  (*node) //
      .setName(basicBlock->getName())
      .setInstructionCount(basicBlock->size());
}

void Emitter::fillIn(const llvm::Instruction *instruction, llvm2graphml::Node *node) {
  (*node) //
      .setInstructionOpcode(instruction->getOpcodeName())
      .setNumOperands(instruction->getNumOperands());
}

void Emitter::fillIn(const llvm::Argument *argument, llvm2graphml::Node *node) {}
void Emitter::fillIn(const llvm::ConstantInt *constant, llvm2graphml::Node *node) {}
void Emitter::fillIn(const llvm::ConstantFP *constant, llvm2graphml::Node *node) {}
void Emitter::fillIn(const llvm::ConstantPointerNull *constant, llvm2graphml::Node *node) {}
void Emitter::fillIn(const llvm::ConstantTokenNone *constant, llvm2graphml::Node *node) {}
void Emitter::fillIn(const llvm::UndefValue *undefValue, llvm2graphml::Node *node) {}
void Emitter::fillIn(const llvm::InlineAsm *inlineAsm, llvm2graphml::Node *node) {}
void Emitter::fillIn(const llvm::MetadataAsValue *metadataAsValue, llvm2graphml::Node *node) {}
void Emitter::fillIn(const llvm::BlockAddress *blockAddress, llvm2graphml::Node *node) {}
void Emitter::fillIn(const llvm::ConstantArray *constantArray, llvm2graphml::Node *node) {}
void Emitter::fillIn(const llvm::ConstantDataArray *constantArray, llvm2graphml::Node *node) {}
void Emitter::fillIn(const llvm::GlobalAlias *globalAlias, llvm2graphml::Node *node) {}
void Emitter::fillIn(const llvm::GlobalIFunc *globalIFunc, llvm2graphml::Node *node) {}
void Emitter::fillIn(const llvm::GlobalVariable *globalVariable, llvm2graphml::Node *node) {}
void Emitter::fillIn(const llvm::ConstantExpr *constantExpr, llvm2graphml::Node *node) {}
void Emitter::fillIn(const llvm::ConstantStruct *constantStruct, llvm2graphml::Node *node) {}
void Emitter::fillIn(const llvm::ConstantVector *constantVector, llvm2graphml::Node *node) {}
void Emitter::fillIn(const llvm::ConstantAggregateZero *constantZero, llvm2graphml::Node *node) {}
void Emitter::fillIn(const llvm::ConstantDataVector *constantVector, llvm2graphml::Node *node) {}
void Emitter::fillIn(const llvm::ReturnInst *inst, Node *node) {}
void Emitter::fillIn(const llvm::BranchInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::SwitchInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::IndirectBrInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::InvokeInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::ResumeInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::UnreachableInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::CleanupReturnInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::CatchReturnInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::CatchSwitchInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::CallBrInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::UnaryOperator *instruction, Node *node) {}
void Emitter::fillIn(const llvm::BinaryOperator *instruction, Node *node) {}
void Emitter::fillIn(const llvm::AllocaInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::LoadInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::StoreInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::GetElementPtrInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::FenceInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::AtomicCmpXchgInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::AtomicRMWInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::TruncInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::ZExtInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::SExtInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::FPToUIInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::FPToSIInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::UIToFPInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::SIToFPInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::FPTruncInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::FPExtInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::PtrToIntInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::IntToPtrInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::BitCastInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::AddrSpaceCastInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::CleanupPadInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::CatchPadInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::ICmpInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::FCmpInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::PHINode *instruction, Node *node) {}
void Emitter::fillIn(const llvm::CallInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::SelectInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::VAArgInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::ExtractElementInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::InsertElementInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::ShuffleVectorInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::ExtractValueInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::InsertValueInst *instruction, Node *node) {}
void Emitter::fillIn(const llvm::LandingPadInst *instruction, Node *node) {}
