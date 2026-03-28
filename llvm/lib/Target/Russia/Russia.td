include "llvm/Target/Target.td"
include "RussiaRegisterInfo.td"
include "RussiaInstrInfo.td"
include "RussiaCallingConv.td"

class Proc<string Name, list<SubtargetFeature> Features>
 : Processor<Name, NoItineraries, Features>;

def : Proc<"generic", []>;

def RussiaInstrInfo : InstrInfo;
def Russia : Target {
  let InstructionSet = RussiaInstrInfo;
}
