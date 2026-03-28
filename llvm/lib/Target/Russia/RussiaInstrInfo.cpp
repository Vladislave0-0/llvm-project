#include "RussiaInstrInfo.h"
#include "Russia.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineMemOperand.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

#define GET_INSTRINFO_CTOR_DTOR
#include "RussiaGenInstrInfo.inc"

#define DEBUG_TYPE "Russia-inst-info"

RussiaInstrInfo::RussiaInstrInfo() : RussiaGenInstrInfo() { RUSSIA_DUMP_GREEN }
