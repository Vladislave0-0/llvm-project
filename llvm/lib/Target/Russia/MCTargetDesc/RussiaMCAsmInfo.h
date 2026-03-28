#ifndef LLVM_LIB_TARGET_RUSSIA_MCTARGETDESC_RUSSIAMCASMINFO_H
#define LLVM_LIB_TARGET_RUSSIA_MCTARGETDESC_RUSSIAMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {

class Triple;

class RussiaELFMCAsmInfo : public MCAsmInfoELF {
public:
  explicit RussiaELFMCAsmInfo(const Triple &TheTriple);
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_RUSSIA_MCTARGETDESC_RUSSIAMCASMINFO_H
