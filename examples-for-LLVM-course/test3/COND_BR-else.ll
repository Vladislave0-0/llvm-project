define dso_local void @app() {
entry:
  call void @llvm.rus.putpixel(i32 5, i32 5, i32 -1)
  br i1 42, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  call void @llvm.rus.flush()
  br label %if.end

if.else:                                          ; preds = %entry
  call i32 @llvm.rus.rand()
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret void
}

declare void @llvm.rus.putpixel(i32, i32, i32)
declare void @llvm.rus.flush()
declare i32 @llvm.rus.rand()
