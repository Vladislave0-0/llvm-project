#include "MCTargetDesc/RussiaInfo.h"
#include "Russia.h"
#include "TargetInfo/RussiaTargetInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define GET_REGINFO_MC_DESC
#include "RussiaGenRegisterInfo.inc"

#define GET_INSTRINFO_MC_DESC
#include "RussiaGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "RussiaGenSubtargetInfo.inc"

static MCRegisterInfo *createRussiaMCRegisterInfo(const Triple &TT) {
  RUSSIA_DUMP_MAGENTA
  MCRegisterInfo *X = new MCRegisterInfo();
  InitRussiaMCRegisterInfo(X, Russia::VODKA0);
  return X;
}

static MCInstrInfo *createRussiaMCInstrInfo() {
  RUSSIA_DUMP_MAGENTA
  MCInstrInfo *X = new MCInstrInfo();
  InitRussiaMCInstrInfo(X);
  return X;
}

static MCSubtargetInfo *
createRussiaMCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
  RUSSIA_DUMP_MAGENTA
  return createRussiaMCSubtargetInfoImpl(TT, CPU, /*TuneCPU*/ CPU, FS);
}

// We need to define this function for linking succeed
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeRussiaTargetMC() {
  RUSSIA_DUMP_MAGENTA
  Target &TheRussiaTarget = getTheRussiaTarget();
  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheRussiaTarget,
                                    createRussiaMCRegisterInfo);
  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheRussiaTarget, createRussiaMCInstrInfo);
  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheRussiaTarget,
                                          createRussiaMCSubtargetInfo);
}
