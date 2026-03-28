include "llvm/Target/Target.td"
include "RussiaRegisterInfo.td"
include "RussiaInstrInfo.td"

def RussiaInstrInfo : InstrInfo;
def Russia : Target {
  let InstructionSet = RussiaInstrInfo;
}
