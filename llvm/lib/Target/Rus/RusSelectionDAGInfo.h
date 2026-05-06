#ifndef LLVM_LIB_TARGET_RUS_RUSSELECTIONDAGINFO_H
#define LLVM_LIB_TARGET_RUS_RUSSELECTIONDAGINFO_H

#include "llvm/CodeGen/SelectionDAGTargetInfo.h"

namespace llvm {
class RusSelectionDAGInfo : public SelectionDAGTargetInfo {
public:
  SDValue EmitTargetCodeForMemset(SelectionDAG &DAG, const SDLoc &dl,
                                  SDValue Chain, SDValue Dst, SDValue Val,
                                  SDValue Size, Align Alignment,
                                  bool isVolatile, bool AlwaysInline,
                                  MachinePointerInfo DstPtrInfo) const override;

  SDValue EmitTargetCodeForMemcpy(SelectionDAG &DAG, const SDLoc &dl,
                                  SDValue Chain, SDValue Dst, SDValue Src,
                                  SDValue Size, Align Alignment,
                                  bool isVolatile, bool AlwaysInline,
                                  MachinePointerInfo DstPtrInfo,
                                  MachinePointerInfo SrcPtrInfo) const override;
};
} // namespace llvm

#endif // LLVM_LIB_TARGET_RUS_RUSSELECTIONDAGINFO_H
