#ifndef LLVM_LIB_TARGET_RUS_RUSINSTRINFO_H
#define LLVM_LIB_TARGET_RUS_RUSINSTRINFO_H

#include "MCTargetDesc/RusInfo.h"
#include "RusRegisterInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "RusGenInstrInfo.inc"

namespace llvm {

class RusSubtarget;

class RusInstrInfo : public RusGenInstrInfo {
public:
  RusInstrInfo();
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_RUS_RUSINSTRINFO_H
