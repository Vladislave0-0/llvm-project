#ifndef LLVM_LIB_TARGET_RUS_MCTARGETDESC_RUSMCTARGETDESC_H
#define LLVM_LIB_TARGET_RUS_MCTARGETDESC_RUSMCTARGETDESC_H

// Defines symbolic names for Rus registers.  This defines a mapping from
// register name to register number.
//
#define GET_REGINFO_ENUM
#include "RusGenRegisterInfo.inc"

// Defines symbolic names for the Rus instructions.
#define GET_INSTRINFO_ENUM
#include "RusGenInstrInfo.inc"

#endif // LLVM_LIB_TARGET_RUS_MCTARGETDESC_RUSMCTARGETDESC_H
