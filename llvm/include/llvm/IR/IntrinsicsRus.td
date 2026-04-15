let TargetPrefix = "rus" in {  // All intrinsics start with "llvm.rus.".
  def int_rus_putpixel: ClangBuiltin<"rusPutPixel">,
    Intrinsic<[], [llvm_i32_ty, llvm_i32_ty, llvm_i32_ty], [IntrNoMem, IntrHasSideEffects]>;
 
  def int_rus_flush:  ClangBuiltin<"rusFlush">,
    Intrinsic<[], [], [IntrNoMem, IntrHasSideEffects]>;

  def int_rus_rand: ClangBuiltin<"rusRand">,
    Intrinsic<[llvm_i32_ty], [], [IntrNoMem, IntrHasSideEffects]>;
 
} // TargetPrefix = "rus"
