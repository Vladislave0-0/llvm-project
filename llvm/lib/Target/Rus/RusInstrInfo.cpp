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

RusInstrInfo::RusInstrInfo() : RusGenInstrInfo() { RUS_DUMP_GREEN }
