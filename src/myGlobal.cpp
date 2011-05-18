/*
  This is a manually edited version of code generated by llc
  for global.c in my personal directory. This is to explore
  the reduction in instructions that still allows 
  changing a global variable.
  This is not used in the package, but just here for debugging
  and verification.
  The difference between the R code and this code was that 
  we used a new ExecutionEngine in each call in R but the
  same one here.

 Generated by llvm2cpp - DO NOT MODIFY!
 */

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Constants.h>
#include <llvm/GlobalVariable.h>
#include <llvm/Function.h>
#include <llvm/CallingConv.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>
#include <llvm/InlineAsm.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/MathExtras.h>
#include <llvm/Pass.h>
#include <llvm/PassManager.h>
#include <llvm/ADT/SmallVector.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/JIT.h>
#include "llvm/Target/TargetSelect.h"
#include <algorithm>
using namespace llvm;

Module* makeLLVMModule1(Function **a, Function **b);

extern "C"
void myMain() {
  Function *get, *foo;
  InitializeNativeTarget();
  Module* Mod = makeLLVMModule1(&foo, &get);
  verifyModule(*Mod, PrintMessageAction);
#if 1
  PassManager PM;
  PM.add(createPrintModulePass(&outs()));
  PM.run(*Mod);
#endif

  std::string errStr;
  ExecutionEngine *EE = EngineBuilder(Mod).setErrorStr(&errStr).setEngineKind(EngineKind::JIT).create();

  if (!EE) {
    errs() <<  ": Failed to construct ExecutionEngine: " << errStr << "\n";
    return ;
  }

  // Call the Fibonacci function with argument n:
  std::vector<GenericValue> Args(0);
  GenericValue GV = EE->runFunction(get, Args);
  outs() << "Result: " << GV.IntVal << "\n";
  GV = EE->runFunction(foo, Args);
  outs() << "foo: " << GV.IntVal << "\n";
  for(int i = 0; i < 10; i++)
     GV = EE->runFunction(foo, Args);
  GV = EE->runFunction(get, Args);
  outs() << "value: " << GV.IntVal << "\n";

}


Module* makeLLVMModule1(Function **fun1, Function **fun2) {

  // Module Construction
  Module* mod = new Module("global.bc", getGlobalContext());
 
  std::vector<const Type*>FuncTy_1_args;
  FunctionType* FuncTy_1 = FunctionType::get(
    /*Result=*/IntegerType::get(mod->getContext(), 32),
    /*Params=*/FuncTy_1_args,
    /*isVarArg=*/false);
  
  
  // Function Declarations
  
  Function* func_foo = Function::Create(
    /*Type=*/FuncTy_1,
    /*Linkage=*/GlobalValue::ExternalLinkage,
    /*Name=*/"foo", mod); 

  
  Function* func_get = Function::Create(
    /*Type=*/FuncTy_1,
    /*Linkage=*/GlobalValue::ExternalLinkage,
    /*Name=*/"get", mod); 


 // Constant Definitions
  ConstantInt* const_int32_2 = ConstantInt::get(mod->getContext(), APInt(32, StringRef("1"), 10));
  ConstantInt* const_int32_3 = ConstantInt::get(mod->getContext(), APInt(32, StringRef("0"), 10));
  
  GlobalVariable* gvar_int32_gv = new GlobalVariable(/*Module=*/*mod, 
  /*Type=*/IntegerType::get(mod->getContext(), 32),
  /*isConstant=*/false,
  /*Linkage=*/GlobalValue::ExternalLinkage,
  /*Initializer=*/const_int32_2, //0 // has initializer, specified below
  /*Name=*/"gv");
  
 
  // Function: increment (func_foo)
  {
    BasicBlock* label_entry = BasicBlock::Create(mod->getContext(), "entry",func_foo,0);

    LoadInst* int32_5 = new LoadInst(gvar_int32_gv, "", false, label_entry);
    BinaryOperator* int32_6 = BinaryOperator::Create(Instruction::Add, int32_5, const_int32_2, "", label_entry);
     new StoreInst(int32_6, gvar_int32_gv, false, label_entry);

    LoadInst* int32_retval1 = new LoadInst(gvar_int32_gv, "ret", false, label_entry);
    ReturnInst::Create(mod->getContext(), int32_retval1, label_entry);
  }
  
  // Function: get (func_get)
  {
    BasicBlock* label_return_15 = BasicBlock::Create(mod->getContext(), "return",func_get,0);
    
    // Block return (label_return_15)
    LoadInst* int32_retval1_24 = new LoadInst(gvar_int32_gv, "ret", false, label_return_15);
    ReturnInst::Create(mod->getContext(), int32_retval1_24, label_return_15);
  }

  *fun1 = func_foo;
  *fun2 = func_get;
  
  return mod;
}