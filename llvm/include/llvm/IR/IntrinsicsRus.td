let TargetPrefix = "rus" in {  // All intrinsics start with "llvm.rus.".
  def int_rus_putpixel:
    Intrinsic<[], [llvm_i32_ty, llvm_i32_ty, llvm_i32_ty], [IntrNoMem, IntrHasSideEffects]>;
 
  def int_rus_flush:
    Intrinsic<[], [], [IntrNoMem, IntrHasSideEffects]>;

  def int_rus_rand:
    Intrinsic<[llvm_i32_ty], [], [IntrNoMem, IntrHasSideEffects]>;
 
} // TargetPrefix = "rus"
