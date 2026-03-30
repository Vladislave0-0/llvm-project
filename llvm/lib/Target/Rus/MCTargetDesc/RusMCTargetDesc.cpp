#include "MCTargetDesc/RusInfo.h"
#include "Rus.h"
#include "RusInstPrinter.h"
#include "RusMCAsmInfo.h"
#include "TargetInfo/RusTargetInfo.h"
#include "llvm/MC/MCDwarf.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

#define GET_REGINFO_MC_DESC
#include "RusGenRegisterInfo.inc"

#define GET_INSTRINFO_MC_DESC
#include "RusGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "RusGenSubtargetInfo.inc"

static MCRegisterInfo *createRusMCRegisterInfo(const Triple &TT) {
  RUS_DUMP_MAGENTA
  MCRegisterInfo *X = new MCRegisterInfo();
  InitRusMCRegisterInfo(X, Rus::LESHY);
  return X;
}

static MCInstrInfo *createRusMCInstrInfo() {
  RUS_DUMP_MAGENTA
  MCInstrInfo *X = new MCInstrInfo();
  InitRusMCInstrInfo(X);
  return X;
}

static MCSubtargetInfo *
createRusMCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
  RUS_DUMP_MAGENTA
  return createRusMCSubtargetInfoImpl(TT, CPU, /*TuneCPU*/ CPU, FS);
}

static MCAsmInfo *createRusMCAsmInfo(const MCRegisterInfo &MRI,
                                        const Triple &TT,
                                        const MCTargetOptions &Options) {
  RUS_DUMP_MAGENTA
  MCAsmInfo *MAI = new RusELFMCAsmInfo(TT);
  unsigned SP = MRI.getDwarfRegNum(Rus::ZAKROM, true);
  MCCFIInstruction Inst = MCCFIInstruction::cfiDefCfa(nullptr, SP, 0);
  MAI->addInitialFrameState(Inst);
  return MAI;
}

static MCInstPrinter *createRusMCInstPrinter(const Triple &T,
                                                unsigned SyntaxVariant,
                                                const MCAsmInfo &MAI,
                                                const MCInstrInfo &MII,
                                                const MCRegisterInfo &MRI) {
  RUS_DUMP_MAGENTA
  return new RusInstPrinter(MAI, MII, MRI);
}

// We need to define this function for linking succeed
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeRusTargetMC() {
  RUS_DUMP_MAGENTA
  Target &TheRusTarget = getTheRusTarget();
  RegisterMCAsmInfoFn X(TheRusTarget, createRusMCAsmInfo);
  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheRusTarget,
                                    createRusMCRegisterInfo);
  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheRusTarget, createRusMCInstrInfo);
  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheRusTarget,
                                          createRusMCSubtargetInfo);
  // Register the MCInstPrinter
  TargetRegistry::RegisterMCInstPrinter(TheRusTarget, createRusMCInstPrinter);
  // Register the MC Code Emitter.
  TargetRegistry::RegisterMCCodeEmitter(TheRusTarget, createRusMCCodeEmitter);
  // Register the asm backend.
  TargetRegistry::RegisterMCAsmBackend(TheRusTarget, createRusAsmBackend);
}
