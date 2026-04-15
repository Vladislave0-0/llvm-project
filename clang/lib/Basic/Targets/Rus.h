//===--- Rus.h - Declare Rus target feature support -------------*- C++ -*-===//
//
// Part of the Sergey Lisitsyn's LLVM course.
//
//===----------------------------------------------------------------------===//
//
// This file declares Rus TargetInfo objects.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_LIB_BASIC_TARGETS_RUS_H
#define LLVM_CLANG_LIB_BASIC_TARGETS_RUS_H
#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/TargetOptions.h"
#include "llvm/Support/Compiler.h"
#include "llvm/TargetParser/Triple.h"
namespace clang {
namespace targets {

class LLVM_LIBRARY_VISIBILITY RusTargetInfo : public TargetInfo {
public:
  RusTargetInfo(const llvm::Triple &Triple, const TargetOptions &Opts)
      : TargetInfo(Triple) {
    NoAsmVariants = true;
    LongLongAlign = 32;
    SuitableAlign = 32;
    DoubleAlign = LongDoubleAlign = 32;
    SizeType = UnsignedInt;
    PtrDiffType = SignedInt;
    IntPtrType = SignedInt;
    WCharType = UnsignedChar;
    WIntType = UnsignedInt;
    resetDataLayout("e-m:e-p:32:32-i8:8:32-i16:16:32-i64:64-n32");
  }

  void getTargetDefines(const LangOptions &Opts,
                        MacroBuilder &Builder) const override;

  ArrayRef<Builtin::Info> getTargetBuiltins() const override;

  BuiltinVaListKind getBuiltinVaListKind() const override {
    return TargetInfo::VoidPtrBuiltinVaList;
  }

  std::string_view getClobbers() const override { return ""; }

  ArrayRef<const char *> getGCCRegNames() const override {
    static const char *const GCCRegNames[] = {
        "LESHY", "ZAKROM",  "LAPTI",    "SHALOPAY", "TROPKA",    "YARILO",
        "YAGA",  "VYAZ",    "DUB",      "GUSLI",    "BALALAIKA", "PLYAS",
        "VODKA", "SAMOVAR", "MATUSHKA", "GOYDA"};
    return llvm::ArrayRef(GCCRegNames);
  }

  ArrayRef<TargetInfo::GCCRegAlias> getGCCRegAliases() const override {
    return std::nullopt;
  }

  bool validateAsmConstraint(const char *&Name,
                             TargetInfo::ConstraintInfo &Info) const override {
    return false;
  }
};
} // namespace targets
} // namespace clang

#endif // LLVM_CLANG_LIB_BASIC_TARGETS_RUS_H
