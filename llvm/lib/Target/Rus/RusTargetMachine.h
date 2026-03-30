#ifndef LLVM_LIB_TARGET_RUS_RUSTARGETMACHINE_H
#define LLVM_LIB_TARGET_RUS_RUSTARGETMACHINE_H

#include "RusSubtarget.h"
#include "llvm/CodeGen/CodeGenTargetMachineImpl.h"
#include <optional>

namespace llvm {
extern Target TheRusTarget;

class RusTargetMachine : public CodeGenTargetMachineImpl {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  RusSubtarget Subtarget;

public:
  RusTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                   StringRef FS, const TargetOptions &Options,
                   std::optional<Reloc::Model> RM,
                   std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                   bool JIT);

  const RusSubtarget *getSubtargetImpl(const Function &) const override {
    RUS_DUMP_CYAN
    return &Subtarget;
  }
  // Pass Pipeline Configuration
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;
  TargetLoweringObjectFile *getObjFileLowering() const override;
};
} // end namespace llvm

#endif // LLVM_LIB_TARGET_RUS_RUSTARGETMACHINE_H
