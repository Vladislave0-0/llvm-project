#include "RusFrameLowering.h"
#include "Rus.h"
#include "RusInstrInfo.h"
#include "RusSubtarget.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"

using namespace llvm;

void RusFrameLowering::emitPrologue(MachineFunction &MF,
                                    MachineBasicBlock &MBB) const {
  int FrameSize = (int)MF.getFrameInfo().getStackSize();
  if (FrameSize == 0)
    return;

  const RusInstrInfo *TII =
      static_cast<const RusInstrInfo *>(MF.getSubtarget().getInstrInfo());
  MachineBasicBlock::iterator MBBI = MBB.begin();

  BuildMI(MBB, MBBI, DebugLoc(), TII->get(Rus::ADDi), Rus::ZAKROM)
      .addReg(Rus::ZAKROM)
      .addImm(-FrameSize);
}

void RusFrameLowering::emitEpilogue(MachineFunction &MF,
                                    MachineBasicBlock &MBB) const {
  int FrameSize = (int)MF.getFrameInfo().getStackSize();
  if (FrameSize == 0)
    return;

  const RusInstrInfo *TII =
      static_cast<const RusInstrInfo *>(MF.getSubtarget().getInstrInfo());
  MachineBasicBlock::iterator MBBI = MBB.getLastNonDebugInstr();

  BuildMI(MBB, MBBI, DebugLoc(), TII->get(Rus::ADDi), Rus::ZAKROM)
      .addReg(Rus::ZAKROM)
      .addImm(FrameSize);
}

StackOffset RusFrameLowering::getFrameIndexReference(const MachineFunction &MF,
                                                     int FI,
                                                     Register &FrameReg) const {
  FrameReg = Rus::ZAKROM;
  const MachineFrameInfo &MFI = MF.getFrameInfo();
  return StackOffset::getFixed(MFI.getObjectOffset(FI) +
                               (int64_t)MFI.getStackSize());
}
