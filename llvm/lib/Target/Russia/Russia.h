#ifndef LLVM_LIB_TARGET_Russia_Russia_H
#define LLVM_LIB_TARGET_Russia_Russia_H

#include "MCTargetDesc/RussiaMCTargetDesc.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"

#define RUSSIA_DUMP(Color)                                                     \
  {                                                                            \
    llvm::errs().changeColor(Color)                                            \
        << __func__ << "\n\t\t" << __FILE__ << ":" << __LINE__ << "\n";        \
    llvm::errs().changeColor(llvm::raw_ostream::WHITE);                        \
  }
// #define RUSSIA_DUMP(Color) {}

#define RUSSIA_DUMP_RED RUSSIA_DUMP(llvm::raw_ostream::RED)
#define RUSSIA_DUMP_GREEN RUSSIA_DUMP(llvm::raw_ostream::GREEN)
#define RUSSIA_DUMP_YELLOW RUSSIA_DUMP(llvm::raw_ostream::YELLOW)
#define RUSSIA_DUMP_CYAN RUSSIA_DUMP(llvm::raw_ostream::CYAN)
#define RUSSIA_DUMP_MAGENTA RUSSIA_DUMP(llvm::raw_ostream::MAGENTA)
#define RUSSIA_DUMP_WHITE RUSSIA_DUMP(llvm::raw_ostream::WHITE)
namespace llvm {
class RussiaTargetMachine;
class FunctionPass;
class RussiaSubtarget;
class AsmPrinter;
class InstructionSelector;
class MCInst;
class MCOperand;
class MachineInstr;
class MachineOperand;
class PassRegistry;

bool lowerRussiaMachineInstrToMCInst(const MachineInstr *MI, MCInst &OutMI,
                                  AsmPrinter &AP);
bool LowerRussiaMachineOperandToMCOperand(const MachineOperand &MO,
                                       MCOperand &MCOp, const AsmPrinter &AP);

FunctionPass *createRussiaISelDag(RussiaTargetMachine &TM, CodeGenOptLevel OptLevel);

} // namespace llvm

#endif // LLVM_LIB_TARGET_Russia_Russia_H
