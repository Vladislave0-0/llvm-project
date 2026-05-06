#include "RusSelectionDAGInfo.h"
#include "RusISelLowering.h"
#include "llvm/CodeGen/SelectionDAG.h"

using namespace llvm;

SDValue RusSelectionDAGInfo::EmitTargetCodeForMemset(
    SelectionDAG &DAG, const SDLoc &dl, SDValue Chain, SDValue Dst, SDValue Val,
    SDValue Size, Align Alignment, bool isVolatile, bool AlwaysInline,
    MachinePointerInfo DstPtrInfo) const {
  SDValue FillVal = DAG.getNode(ISD::ZERO_EXTEND, dl, MVT::i32, Val);

  if (Size.getValueType() != MVT::i32)
    Size = DAG.getNode(ISD::TRUNCATE, dl, MVT::i32, Size);

  SDValue Ops[] = {Chain, Dst, FillVal, Size};
  return DAG.getNode(RusISD::MEMSET, dl, MVT::Other, Ops);
}

SDValue RusSelectionDAGInfo::EmitTargetCodeForMemcpy(
    SelectionDAG &DAG, const SDLoc &dl, SDValue Chain, SDValue Dst, SDValue Src,
    SDValue Size, Align Alignment, bool isVolatile, bool AlwaysInline,
    MachinePointerInfo DstPtrInfo, MachinePointerInfo SrcPtrInfo) const {
  SDValue Ops[] = {Chain, Dst, Src, Size};
  return DAG.getNode(RusISD::MEMCPY, dl, MVT::Other, Ops);
}
