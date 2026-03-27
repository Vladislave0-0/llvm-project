#ifndef LLVM_LIB_TARGET_RUSSIA_RUSSIAREGISTERINFO_H
#define LLVM_LIB_TARGET_RUSSIA_RUSSIAREGISTERINFO_H

#define GET_REGINFO_HEADER
#include "RussiaGenRegisterInfo.inc"

namespace llvm {

struct RussiaRegisterInfo : public RussiaGenRegisterInfo {
public:
  RussiaRegisterInfo();
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_RUSSIA_RUSSIAREGISTERINFO_H
