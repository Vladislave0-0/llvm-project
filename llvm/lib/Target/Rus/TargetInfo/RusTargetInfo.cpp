#include "TargetInfo/RusTargetInfo.h"
#include "Rus.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

Target &llvm::getTheRusTarget() {
  RUS_DUMP_YELLOW
  static Target TheRusTarget;
  return TheRusTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeRusTargetInfo() {
  RUS_DUMP_YELLOW
  RegisterTarget<Triple::rus> X(getTheRusTarget(), "rus",
                                "Simulator target for LLVM course", "RUS");
}
