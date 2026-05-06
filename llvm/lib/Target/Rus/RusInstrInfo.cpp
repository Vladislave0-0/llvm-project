#include "RusInstrInfo.h"
#include "Rus.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineMemOperand.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

#define GET_INSTRINFO_CTOR_DTOR
#include "RusGenInstrInfo.inc"

#define DEBUG_TYPE "Rus-inst-info"

RusInstrInfo::RusInstrInfo()
    : RusGenInstrInfo(Rus::ADJCALLSTACKDOWN, Rus::ADJCALLSTACKUP) {
  RUS_DUMP_GREEN
}

void RusInstrInfo::copyPhysReg(MachineBasicBlock &MBB,
                               MachineBasicBlock::iterator MBBI,
                               const DebugLoc &DL, MCRegister DstReg,
                               MCRegister SrcReg, bool KillSrc,
                               bool RenamableDest, bool RenamableSrc) const {
  if (Rus::GPRRegClass.contains(DstReg, SrcReg)) {
    BuildMI(MBB, MBBI, DL, get(Rus::MOV), DstReg)
        .addReg(SrcReg, getKillRegState(KillSrc));
    return;
  }

  llvm_unreachable("can't copyPhysReg");
}

void RusInstrInfo::storeRegToStackSlot(
    MachineBasicBlock &MBB, MachineBasicBlock::iterator MI, Register SrcReg,
    bool IsKill, int FrameIndex, const TargetRegisterClass *RC,
    const TargetRegisterInfo *TRI, Register VReg,
    MachineInstr::MIFlag Flags) const {
  DebugLoc DL = MI->getDebugLoc();
  BuildMI(MBB, MI, DL, get(Rus::SW))
      .addReg(SrcReg, getKillRegState(IsKill))
      .addFrameIndex(FrameIndex)
      .addImm(0);
}

void RusInstrInfo::loadRegFromStackSlot(MachineBasicBlock &MBB,
                                        MachineBasicBlock::iterator MI,
                                        Register DestReg, int FrameIndex,
                                        const TargetRegisterClass *RC,
                                        const TargetRegisterInfo *TRI,
                                        Register VReg,
                                        MachineInstr::MIFlag Flags) const {
  DebugLoc DL = MI->getDebugLoc();
  BuildMI(MBB, MI, DL, get(Rus::LW))
      .addReg(DestReg, RegState::Define)
      .addFrameIndex(FrameIndex)
      .addImm(0);
}

bool RusInstrInfo::analyzeBranch(MachineBasicBlock &MBB,
                                 MachineBasicBlock *&TBB,
                                 MachineBasicBlock *&FBB,
                                 SmallVectorImpl<MachineOperand> &Cond,
                                 bool AllowModify) const {
  TBB = FBB = nullptr;
  Cond.clear();

  MachineBasicBlock::iterator I = MBB.end();
  while (I != MBB.begin()) {
    --I;

    if (I->isDebugInstr())
      continue;

    if (!I->isTerminator())
      break;

    unsigned Opc = I->getOpcode();
    if (Opc == Rus::B) {
      TBB = I->getOperand(0).getMBB();
    } else if (Opc == Rus::BR_COND) {
      FBB = TBB;
      TBB = I->getOperand(1).getMBB();
      Cond.push_back(I->getOperand(0));
    } else {
      return true;
    }
  }
  return false;
}

unsigned RusInstrInfo::insertBranch(MachineBasicBlock &MBB,
                                    MachineBasicBlock *TBB,
                                    MachineBasicBlock *FBB,
                                    ArrayRef<MachineOperand> Cond,
                                    const DebugLoc &DL, int *BytesAdded) const {
  assert(TBB && "insertBranch must not be told to insert a fallthrough");
  assert(Cond.size() <= 1);

  if (Cond.empty()) {
    BuildMI(&MBB, DL, get(Rus::B)).addMBB(TBB);
    if (BytesAdded)
      *BytesAdded = 8;

    return 1;
  }

  BuildMI(&MBB, DL, get(Rus::BR_COND)).add(Cond[0]).addMBB(TBB);
  if (!FBB) {
    if (BytesAdded)
      *BytesAdded = 8;

    return 1;
  }

  BuildMI(&MBB, DL, get(Rus::B)).addMBB(FBB);
  if (BytesAdded)
    *BytesAdded = 16;

  return 2;
}

unsigned RusInstrInfo::removeBranch(MachineBasicBlock &MBB,
                                    int *BytesRemoved) const {
  MachineBasicBlock::iterator I = MBB.end();
  unsigned Count = 0;

  while (I != MBB.begin()) {
    --I;

    if (I->isDebugInstr())
      continue;

    unsigned Opc = I->getOpcode();
    if (Opc != Rus::B && Opc != Rus::BR_COND)
      break;

    I->eraseFromParent();
    I = MBB.end();
    ++Count;
  }

  if (BytesRemoved)
    *BytesRemoved = Count * 8;

  return Count;
}
