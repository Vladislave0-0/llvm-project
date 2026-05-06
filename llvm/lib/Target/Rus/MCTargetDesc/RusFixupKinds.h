#ifndef LLVM_LIB_TARGET_Rus_MCTARGETDESC_RusFIXUPKINDS_H
#define LLVM_LIB_TARGET_Rus_MCTARGETDESC_RusFIXUPKINDS_H

#include "llvm/MC/MCFixup.h"

namespace llvm {
namespace Rus {
enum Fixups {
  fixup_Rus_PC32 = FirstTargetFixupKind,
  // Marker
  LastTargetFixupKind,
  NumTargetFixupKinds = LastTargetFixupKind - FirstTargetFixupKind
};
} // namespace Rus
} // namespace llvm

#endif
