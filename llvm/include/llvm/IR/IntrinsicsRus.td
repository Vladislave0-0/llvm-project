let TargetPrefix = "rus" in {  // All intrinsics start with "llvm.rus.".
  def int_rus_putpixel: ClangBuiltin<"simPutPixel">,
    Intrinsic<[], [llvm_i32_ty, llvm_i32_ty, llvm_i32_ty], [IntrNoMem, IntrHasSideEffects]>;
 
  def int_rus_flush:  ClangBuiltin<"simFlush">,
    Intrinsic<[], [], [IntrNoMem, IntrHasSideEffects]>;

  def int_rus_rand: ClangBuiltin<"simRand">,
    Intrinsic<[llvm_i32_ty], [], [IntrNoMem, IntrHasSideEffects]>;
 
} // TargetPrefix = "rus"
