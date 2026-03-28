#ifndef LLVM_LIB_TARGET_RUSSIA_RUSSIATARGETMACHINE_H
#define LLVM_LIB_TARGET_RUSSIA_RUSSIATARGETMACHINE_H

#include "RussiaSubtarget.h"
#include "llvm/CodeGen/CodeGenTargetMachineImpl.h"
#include <optional>

namespace llvm {
extern Target TheRussiaTarget;

class RussiaTargetMachine : public CodeGenTargetMachineImpl {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  RussiaSubtarget Subtarget;

public:
  RussiaTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                      StringRef FS, const TargetOptions &Options,
                      std::optional<Reloc::Model> RM,
                      std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                      bool JIT);

  const RussiaSubtarget *getSubtargetImpl(const Function &) const override {
    RUSSIA_DUMP_CYAN
    return &Subtarget;
  }
  // Pass Pipeline Configuration
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;
  TargetLoweringObjectFile *getObjFileLowering() const override;
};
} // end namespace llvm

#endif // LLVM_LIB_TARGET_RUSSIA_RUSSIATARGETMACHINE_H
