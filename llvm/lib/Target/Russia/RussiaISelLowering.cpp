#include "RussiaISelLowering.h"
#include "Russia.h"
#include "RussiaRegisterInfo.h"
#include "RussiaSubtarget.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/MachineFunction.h"

#define DEBUG_TYPE "Russia-lower"

using namespace llvm;

RussiaTargetLowering::RussiaTargetLowering(const TargetMachine &TM,
                                     const RussiaSubtarget &STI)
    : TargetLowering(TM), STI(STI) {
  RUSSIA_DUMP_RED
  addRegisterClass(MVT::i32, &Russia::GPRRegClass);
}

const char *RussiaTargetLowering::getTargetNodeName(unsigned Opcode) const {
  RUSSIA_DUMP_RED
  switch (Opcode) {
  case RussiaISD::CALL:
    return "RussiaISD::CALL";
  case RussiaISD::RET:
    return "RussiaISD::RET";
  }
  return nullptr;
}
