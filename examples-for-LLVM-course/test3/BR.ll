define dso_local void @app() {
entry:
  call void @llvm.rus.putpixel(i32 5, i32 5, i32 -1)
  call void @llvm.rus.flush()
  call i32 @llvm.rus.rand()
  br label %check_branch

check_branch:
  ret void
}

declare void @llvm.rus.putpixel(i32, i32, i32)
declare void @llvm.rus.flush()
declare i32 @llvm.rus.rand()
