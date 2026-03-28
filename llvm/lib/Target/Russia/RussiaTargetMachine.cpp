#include "RussiaTargetMachine.h"
#include "Russia.h"
#include "TargetInfo/RussiaTargetInfo.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/MC/TargetRegistry.h"
#include <optional>

using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeRussiaTarget() {
  // Register the target.
  RUSSIA_DUMP_CYAN
  RegisterTargetMachine<RussiaTargetMachine> A(getTheRussiaTarget());
}

RussiaTargetMachine::RussiaTargetMachine(const Target &T, const Triple &TT,
                                         StringRef CPU, StringRef FS,
                                         const TargetOptions &Options,
                                         std::optional<Reloc::Model> RM,
                                         std::optional<CodeModel::Model> CM,
                                         CodeGenOptLevel OL, bool JIT)
    : CodeGenTargetMachineImpl(
          T, "e-m:e-p:32:32-i8:8:32-i16:16:32-i64:64-n32", TT, CPU, FS, Options,
          Reloc::Static, getEffectiveCodeModel(CM, CodeModel::Small), OL) {
  RUSSIA_DUMP_CYAN
  initAsmInfo();
}

namespace {

/// Russia Code Generator Pass Configuration Options.
class RussiaPassConfig : public TargetPassConfig {
public:
  RussiaPassConfig(RussiaTargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  RussiaTargetMachine &getRussiaTargetMachine() const {
    return getTM<RussiaTargetMachine>();
  }

  bool addInstSelector() override {
    RUSSIA_DUMP_CYAN
    addPass(createRussiaISelDag(getRussiaTargetMachine(), getOptLevel()));
    return false;
  }
};

} // end anonymous namespace

TargetPassConfig *RussiaTargetMachine::createPassConfig(PassManagerBase &PM) {
  RUSSIA_DUMP_CYAN
  return new RussiaPassConfig(*this, PM);
}
