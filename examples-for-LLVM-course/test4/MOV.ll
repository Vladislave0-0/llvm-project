; ModuleID = '../examples-for-LLVM-course/test4/MOV.c'
source_filename = "../examples-for-LLVM-course/test4/MOV.c"
target datalayout = "e-m:e-p:32:32-i8:8:32-i16:16:32-i64:64-n32"
target triple = "rus"

; Function Attrs: noinline nounwind optnone
define dso_local void @app() #0 {
entry:
  %x = alloca i32, align 4
  %y = alloca i32, align 4
  store i32 10, ptr %x, align 4
  %0 = load i32, ptr %x, align 4
  store i32 %0, ptr %y, align 4
  ret void
}

attributes #0 = { noinline nounwind optnone "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 1}
!1 = !{i32 7, !"frame-pointer", i32 2}
!2 = !{!"clang version 20.1.0 (git@github.com:Vladislave0-0/llvm-project.git 4584822fcbbf706f672e2eeb3807eb730432727c)"}
