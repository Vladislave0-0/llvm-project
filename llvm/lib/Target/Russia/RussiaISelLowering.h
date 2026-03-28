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

class RussiaTargetLowering : public TargetLowering {
public:
  explicit RussiaTargetLowering(const TargetMachine &TM, const RussiaSubtarget &STI);

  /// This method returns the name of a target specific DAG node.
  const char *getTargetNodeName(unsigned Opcode) const override;

  RussiaSubtarget const &getSubtarget() const { return STI; }

private:
  const RussiaSubtarget &STI;
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_RUSSIA_RUSSIAISELLOWERING_H