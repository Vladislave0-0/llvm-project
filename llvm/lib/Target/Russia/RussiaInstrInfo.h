#ifndef LLVM_LIB_TARGET_RUSSIA_RUSSIAINSTRINFO_H
#define LLVM_LIB_TARGET_RUSSIA_RUSSIAINSTRINFO_H

#include "RussiaRegisterInfo.h"
#include "MCTargetDesc/RussiaInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "RussiaGenInstrInfo.inc"

namespace llvm {

class RussiaSubtarget;

class RussiaInstrInfo : public RussiaGenInstrInfo {
public:
  RussiaInstrInfo();

};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_RUSSIA_RUSSIAINSTRINFO_H
