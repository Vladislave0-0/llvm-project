#include "Rus.h"
#include "clang/Basic/Builtins.h"
#include "clang/Basic/MacroBuilder.h"

using namespace clang;
using namespace clang::targets;

void RusTargetInfo::getTargetDefines(const LangOptions &Opts,
                                     MacroBuilder &Builder) const {
  Builder.defineMacro("__rus__");
}

ArrayRef<Builtin::Info> RusTargetInfo::getTargetBuiltins() const {
  return std::nullopt;
}