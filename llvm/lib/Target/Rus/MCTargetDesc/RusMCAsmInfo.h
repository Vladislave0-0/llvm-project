#ifndef LLVM_LIB_TARGET_RUS_MCTARGETDESC_RUSMCASMINFO_H
#define LLVM_LIB_TARGET_RUS_MCTARGETDESC_RUSMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {

class Triple;

class RusELFMCAsmInfo : public MCAsmInfoELF {
public:
  explicit RusELFMCAsmInfo(const Triple &TheTriple);
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_RUS_MCTARGETDESC_RUSMCASMINFO_H
