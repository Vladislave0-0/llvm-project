#ifndef LLVM_LIB_TARGET_RUSSIA_MCTARGETDESC_RUSSIAMCTARGETDESC_H
#define LLVM_LIB_TARGET_RUSSIA_MCTARGETDESC_RUSSIAMCTARGETDESC_H

// Defines symbolic names for Russia registers.  This defines a mapping from
// register name to register number.
//
#define GET_REGINFO_ENUM
#include "RussiaGenRegisterInfo.inc"

// Defines symbolic names for the Russia instructions.
#define GET_INSTRINFO_ENUM
#include "RussiaGenInstrInfo.inc"

#endif // LLVM_LIB_TARGET_RUSSIA_MCTARGETDESC_RUSSIAMCTARGETDESC_H
