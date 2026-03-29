#include "RussiaRegisterInfo.h"
#include "Russia.h"
#include "RussiaFrameLowering.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

using namespace llvm;

#define GET_REGINFO_TARGET_DESC
#include "RussiaGenRegisterInfo.inc"

RussiaRegisterInfo::RussiaRegisterInfo() : RussiaGenRegisterInfo(Russia::VODKA0) {
  RUSSIA_DUMP_GREEN
}

const MCPhysReg *
RussiaRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  RUSSIA_DUMP_GREEN
  return CSR_Russia_SaveList;
}

BitVector RussiaRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  RUSSIA_DUMP_GREEN
  RussiaFrameLowering const *TFI = getFrameLowering(MF);

  BitVector Reserved(getNumRegs());
  Reserved.set(Russia::VODKA8);

  if (TFI->hasFP(MF)) {
    Reserved.set(Russia::VODKA9);
  }
  return Reserved;
}

bool RussiaRegisterInfo::requiresRegisterScavenging(
    const MachineFunction &MF) const {
  return false;
}

bool RussiaRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                          int SPAdj, unsigned FIOperandNum,
                                          RegScavenger *RS) const {
  RUSSIA_DUMP_GREEN
  assert(SPAdj == 0 && "Unexpected non-zero SPAdj value");

  MachineInstr &MI = *II;
  MachineFunction &MF = *MI.getParent()->getParent();
  DebugLoc DL = MI.getDebugLoc();

  int FrameIndex = MI.getOperand(FIOperandNum).getIndex();
  Register FrameReg;
  int Offset = getFrameLowering(MF)
                   ->getFrameIndexReference(MF, FrameIndex, FrameReg)
                   .getFixed();
  Offset += MI.getOperand(FIOperandNum + 1).getImm();

  if (!isInt<16>(Offset)) {
    llvm_unreachable("");
  }

  MI.getOperand(FIOperandNum).ChangeToRegister(FrameReg, false, false, false);
  MI.getOperand(FIOperandNum + 1).ChangeToImmediate(Offset);
  return false;
}

Register RussiaRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  RUSSIA_DUMP_GREEN
  const TargetFrameLowering *TFI = getFrameLowering(MF);
  return TFI->hasFP(MF) ? Russia::VODKA9 : Russia::VODKA8;
}

const uint32_t *
RussiaRegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                      CallingConv::ID CC) const {
  RUSSIA_DUMP_GREEN
  return CSR_Russia_RegMask;
}
