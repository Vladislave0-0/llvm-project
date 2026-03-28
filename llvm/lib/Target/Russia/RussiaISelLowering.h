#ifndef LLVM_LIB_TARGET_RUSSIA_RUSSIAISELLOWERING_H
#define LLVM_LIB_TARGET_RUSSIA_RUSSIAISELLOWERING_H

#include "Russia.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/TargetLowering.h"

namespace llvm {

class RussiaSubtarget;
class RussiaTargetMachine;

namespace RussiaISD {

enum NodeType : unsigned {
  // Start the numbering where the builtin ops and target ops leave off.
  FIRST_NUMBER = ISD::BUILTIN_OP_END,
  RET,
  CALL,
  BR_CC,
};

} // namespace RussiaISD

} // end namespace llvm

#endif // LLVM_LIB_TARGET_RUSSIA_RUSSIAISELLOWERING_H