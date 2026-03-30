#ifndef LLVM_LIB_TARGET_Rus_Rus_H
#define LLVM_LIB_TARGET_Rus_Rus_H

#include "MCTargetDesc/RusMCTargetDesc.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"

#define RUS_DUMP(Color)                                                     \
  {                                                                            \
    llvm::errs().changeColor(Color)                                            \
        << __func__ << "\n\t\t" << __FILE__ << ":" << __LINE__ << "\n";        \
    llvm::errs().changeColor(llvm::raw_ostream::WHITE);                        \
  }
// #define RUS_DUMP(Color) {}

#define RUS_DUMP_RED RUS_DUMP(llvm::raw_ostream::RED)
#define RUS_DUMP_GREEN RUS_DUMP(llvm::raw_ostream::GREEN)
#define RUS_DUMP_YELLOW RUS_DUMP(llvm::raw_ostream::YELLOW)
#define RUS_DUMP_CYAN RUS_DUMP(llvm::raw_ostream::CYAN)
#define RUS_DUMP_MAGENTA RUS_DUMP(llvm::raw_ostream::MAGENTA)
#define RUS_DUMP_WHITE RUS_DUMP(llvm::raw_ostream::WHITE)
namespace llvm {
class RusTargetMachine;
class FunctionPass;
class RusSubtarget;
class AsmPrinter;
class InstructionSelector;
class MCInst;
class MCOperand;
class MachineInstr;
class MachineOperand;
class PassRegistry;

bool lowerRusMachineInstrToMCInst(const MachineInstr *MI, MCInst &OutMI,
                                  AsmPrinter &AP);
bool LowerRusMachineOperandToMCOperand(const MachineOperand &MO,
                                       MCOperand &MCOp, const AsmPrinter &AP);

FunctionPass *createRusISelDag(RusTargetMachine &TM, CodeGenOptLevel OptLevel);

} // namespace llvm

#endif // LLVM_LIB_TARGET_Rus_Rus_H
