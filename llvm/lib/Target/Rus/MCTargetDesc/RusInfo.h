#ifndef LLVM_LIB_TARGET_RUS_MCTARGETDESC_RUSINFO_H
#define LLVM_LIB_TARGET_RUS_MCTARGETDESC_RUSINFO_H

#include "llvm/MC/MCInstrDesc.h"

namespace llvm {

namespace RusOp {
enum OperandType : unsigned {
  OPERAND_SIMM16 = MCOI::OPERAND_FIRST_TARGET,
  OPERAND_SIMM32,
};
} // namespace RusOp

} // end namespace llvm

#endif
