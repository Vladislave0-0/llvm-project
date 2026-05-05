#include "RusRegisterInfo.h"
#include "Rus.h"
#include "RusFrameLowering.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

using namespace llvm;

#define GET_REGINFO_TARGET_DESC
#include "RusGenRegisterInfo.inc"

RusRegisterInfo::RusRegisterInfo() : RusGenRegisterInfo(Rus::LESHY) {
  RUS_DUMP_GREEN
}

const MCPhysReg *
RusRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  RUS_DUMP_GREEN
  return CSR_Rus_SaveList;
}

BitVector RusRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  RUS_DUMP_GREEN
  RusFrameLowering const *TFI = getFrameLowering(MF);

  BitVector Reserved(getNumRegs());
  Reserved.set(Rus::ZAKROM);

  if (TFI->hasFP(MF)) {
    Reserved.set(Rus::LAPTI);
  }
  return Reserved;
}

bool RusRegisterInfo::requiresRegisterScavenging(
    const MachineFunction &MF) const {
  return false;
}

bool RusRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                          int SPAdj, unsigned FIOperandNum,
                                          RegScavenger *RS) const {
  RUS_DUMP_GREEN
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

  if (!isInt<32>(Offset)) {
    llvm_unreachable("");
  }

  MI.getOperand(FIOperandNum).ChangeToRegister(FrameReg, false, false, false);
  MI.getOperand(FIOperandNum + 1).ChangeToImmediate(Offset);
  return false;
}

Register RusRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  RUS_DUMP_GREEN
  const TargetFrameLowering *TFI = getFrameLowering(MF);
  return TFI->hasFP(MF) ? Rus::LAPTI : Rus::ZAKROM;
}

const uint32_t *
RusRegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                      CallingConv::ID CC) const {
  RUS_DUMP_GREEN
  return CSR_Rus_RegMask;
}
