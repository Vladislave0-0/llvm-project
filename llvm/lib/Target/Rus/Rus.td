include "llvm/Target/Target.td"
include "RusRegisterInfo.td"
include "RusInstrInfo.td"
include "RusCallingConv.td"

class Proc<string Name, list<SubtargetFeature> Features>
 : Processor<Name, NoItineraries, Features>;

def : Proc<"generic", []>;

def RusInstrInfo : InstrInfo;
def Rus : Target {
  let InstructionSet = RusInstrInfo;
}
