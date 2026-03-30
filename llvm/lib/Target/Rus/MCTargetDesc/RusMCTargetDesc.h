#ifndef LLVM_LIB_TARGET_RUS_MCTARGETDESC_RUSMCTARGETDESC_H
#define LLVM_LIB_TARGET_RUS_MCTARGETDESC_RUSMCTARGETDESC_H

// Defines symbolic names for Rus registers.  This defines a mapping from
// register name to register number.
//
#define GET_REGINFO_ENUM
#include "RusGenRegisterInfo.inc"

namespace llvm {
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;
class MCAsmBackend;
class MCObjectTargetWriter;
class MCRegisterInfo;
class MCSubtargetInfo;
class MCTargetOptions;
class Target;

MCCodeEmitter *createRusMCCodeEmitter(const MCInstrInfo &MCII, MCContext &Ctx);
MCAsmBackend *createRusAsmBackend(const Target &T, const MCSubtargetInfo &STI,
                                  const MCRegisterInfo &MRI,
                                  const MCTargetOptions &Options);
} // namespace llvm


// Defines symbolic names for the Rus instructions.
#define GET_INSTRINFO_ENUM
#include "RusGenInstrInfo.inc"

#endif // LLVM_LIB_TARGET_RUS_MCTARGETDESC_RUSMCTARGETDESC_H
