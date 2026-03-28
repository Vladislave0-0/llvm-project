#ifndef LLVM_LIB_TARGET_RUSSIA_MCTARGETDESC_RUSSIAINFO_H
#define LLVM_LIB_TARGET_RUSSIA_MCTARGETDESC_RUSSIAINFO_H

#include "llvm/MC/MCInstrDesc.h"

namespace llvm {

namespace RussiaOp {
enum OperandType : unsigned {
  OPERAND_SIMM16 = MCOI::OPERAND_FIRST_TARGET,
};
} // namespace RussiaOp

} // end namespace llvm

#endif
