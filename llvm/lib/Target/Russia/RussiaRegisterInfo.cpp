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
