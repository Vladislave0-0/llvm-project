#ifndef LLVM_LIB_TARGET_RUS_MCTARGETDESC_RUSFIXUPKINDS_H
#define LLVM_LIB_TARGET_RUS_MCTARGETDESC_RUSFIXUPKINDS_H

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

#endif // LLVM_LIB_TARGET_RUS_MCTARGETDESC_RUSFIXUPKINDS_H
