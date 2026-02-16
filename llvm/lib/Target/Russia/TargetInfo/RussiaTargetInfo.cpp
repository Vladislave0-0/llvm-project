#include "TargetInfo/RussiaTargetInfo.h"
#include "Russia.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

Target &llvm::getTheRussiaTarget() {
  RUSSIA_DUMP_YELLOW
  static Target TheRussiaTarget;
  return TheRussiaTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeRussiaTargetInfo() {
  RUSSIA_DUMP_YELLOW
  RegisterTarget<Triple::russia> X(getTheRussiaTarget(), "russia",
                                "Simulator target for LLVM course", "RUSSIA");
}
