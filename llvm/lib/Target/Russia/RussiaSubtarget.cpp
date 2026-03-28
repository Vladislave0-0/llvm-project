#include "RussiaSubtarget.h"
#include "Russia.h"
#include "llvm/Target/TargetMachine.h"

using namespace llvm;

#define DEBUG_TYPE "russia-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "RussiaGenSubtargetInfo.inc"

RussiaSubtarget::RussiaSubtarget(const StringRef &CPU, const StringRef &TuneCPU,
                           const StringRef &FS, const TargetMachine &TM)
    : RussiaGenSubtargetInfo(TM.getTargetTriple(), CPU, TuneCPU, FS) {
  RUSSIA_DUMP_CYAN
}
