; ModuleID = '../examples-for-LLVM-course/test6/CALL.c'
source_filename = "../examples-for-LLVM-course/test6/CALL.c"
target datalayout = "e-m:e-p:32:32-i8:8:32-i16:16:32-i64:64-n32"
target triple = "rus"

; Function Attrs: noinline nounwind optnone
define dso_local i32 @foo(i32 noundef %a) #0 {
entry:
  %a.addr = alloca i32, align 4
  store i32 %a, ptr %a.addr, align 4
  %0 = load i32, ptr %a.addr, align 4
  %add = add nsw i32 42, %0
  ret i32 %add
}

; Function Attrs: noinline nounwind optnone
define dso_local void @app() #0 {
entry:
  %x = alloca i32, align 4
  %call = call i32 @foo(i32 noundef 5)
  store i32 %call, ptr %x, align 4
  ret void
}

attributes #0 = { noinline nounwind optnone "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 1}
!1 = !{i32 7, !"frame-pointer", i32 2}
!2 = !{!"clang version 20.1.0 (git@github.com:Vladislave0-0/llvm-project.git 7b06a79aac9a2332b56187097e752cccf5e2b364)"}
