#include "RusTargetMachine.h"
#include "Rus.h"
#include "TargetInfo/RusTargetInfo.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/MC/TargetRegistry.h"
#include <optional>

using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeRusTarget() {
  // Register the target.
  RUS_DUMP_CYAN
  RegisterTargetMachine<RusTargetMachine> A(getTheRusTarget());
}

RusTargetMachine::RusTargetMachine(const Target &T, const Triple &TT,
                                   StringRef CPU, StringRef FS,
                                   const TargetOptions &Options,
                                   std::optional<Reloc::Model> RM,
                                   std::optional<CodeModel::Model> CM,
                                   CodeGenOptLevel OL, bool JIT)
    : CodeGenTargetMachineImpl(T, "e-m:e-p:32:32-i8:8:32-i16:16:32-i64:64-n32",
                               TT, CPU, FS, Options, Reloc::Static,
                               getEffectiveCodeModel(CM, CodeModel::Small), OL),
      TLOF(std::make_unique<TargetLoweringObjectFileELF>()),
      Subtarget(TT, std::string(CPU), std::string(FS), *this) {
  RUS_DUMP_CYAN
  initAsmInfo();
}

namespace {

/// Rus Code Generator Pass Configuration Options.
class RusPassConfig : public TargetPassConfig {
public:
  RusPassConfig(RusTargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  RusTargetMachine &getRusTargetMachine() const {
    return getTM<RusTargetMachine>();
  }

  bool addInstSelector() override {
    RUS_DUMP_CYAN
    addPass(createRusISelDag(getRusTargetMachine(), getOptLevel()));
    return false;
  }
};

} // end anonymous namespace

TargetPassConfig *RusTargetMachine::createPassConfig(PassManagerBase &PM) {
  RUS_DUMP_CYAN
  return new RusPassConfig(*this, PM);
}

TargetLoweringObjectFile *RusTargetMachine::getObjFileLowering() const {
  RUS_DUMP_CYAN
  return TLOF.get();
}
