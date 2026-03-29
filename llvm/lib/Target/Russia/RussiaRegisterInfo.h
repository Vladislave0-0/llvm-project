#ifndef LLVM_LIB_TARGET_RUSSIA_RUSSIAREGISTERINFO_H
#define LLVM_LIB_TARGET_RUSSIA_RUSSIAREGISTERINFO_H

#define GET_REGINFO_HEADER
#include "RussiaGenRegisterInfo.inc"

namespace llvm {

class TargetInstrInfo;
class RussiaSubtarget;

struct RussiaRegisterInfo : public RussiaGenRegisterInfo {
public:
  RussiaRegisterInfo();

  const MCPhysReg *getCalleeSavedRegs(const MachineFunction *MF) const override;

  const uint32_t *getCallPreservedMask(const MachineFunction &MF,
                                       CallingConv::ID CC) const override;

  BitVector getReservedRegs(const MachineFunction &MF) const override;

  bool requiresRegisterScavenging(const MachineFunction &MF) const override;

  bool eliminateFrameIndex(MachineBasicBlock::iterator II, int SPAdj,
                           unsigned FIOperandNum,
                           RegScavenger *RS = nullptr) const override;

  // Debug information queries.
  Register getFrameRegister(const MachineFunction &MF) const override;
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_RUSSIA_RUSSIAREGISTERINFO_H
