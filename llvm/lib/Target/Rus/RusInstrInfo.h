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

  void copyPhysReg(MachineBasicBlock &MBB, MachineBasicBlock::iterator MBBI,
                   const DebugLoc &DL, MCRegister DestReg, MCRegister SrcReg,
                   bool KillSrc, bool RenamableDest = false,
                   bool RenamableSrc = false) const override;
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_RUS_RUSINSTRINFO_H
