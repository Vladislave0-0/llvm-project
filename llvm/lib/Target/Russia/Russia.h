#ifndef LLVM_LIB_TARGET_Russia_Russia_H
#define LLVM_LIB_TARGET_Russia_Russia_H

#include "llvm/Support/raw_ostream.h"

#define RUSSIA_DUMP(Color)                                                     \
  {                                                                            \
    llvm::errs().changeColor(Color)                                            \
        << __func__ << "\n\t\t" << __FILE__ << ":" << __LINE__ << "\n";        \
    llvm::errs().changeColor(llvm::raw_ostream::WHITE);                        \
  }
// #define RUSSIA_DUMP(Color) {}

#define RUSSIA_DUMP_RED RUSSIA_DUMP(llvm::raw_ostream::RED)
#define RUSSIA_DUMP_GREEN RUSSIA_DUMP(llvm::raw_ostream::GREEN)
#define RUSSIA_DUMP_YELLOW RUSSIA_DUMP(llvm::raw_ostream::YELLOW)
#define RUSSIA_DUMP_CYAN RUSSIA_DUMP(llvm::raw_ostream::CYAN)
#define RUSSIA_DUMP_MAGENTA RUSSIA_DUMP(llvm::raw_ostream::MAGENTA)

#endif // LLVM_LIB_TARGET_Russia_Russia_H
