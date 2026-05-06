; ModuleID = '../examples-for-LLVM-course/test6/CALL_two_args.c'
source_filename = "../examples-for-LLVM-course/test6/CALL_two_args.c"
target datalayout = "e-m:e-p:32:32-i8:8:32-i16:16:32-i64:64-n32"
target triple = "rus"

; Function Attrs: noinline nounwind optnone
define dso_local i32 @foo(i32 noundef %a, i32 noundef %b) #0 {
entry:
  %a.addr = alloca i32, align 4
  %b.addr = alloca i32, align 4
  store i32 %a, ptr %a.addr, align 4
  store i32 %b, ptr %b.addr, align 4
  %0 = load i32, ptr %a.addr, align 4
  %add = add nsw i32 42, %0
  %1 = load i32, ptr %b.addr, align 4
  %add1 = add nsw i32 %add, %1
  ret i32 %add1
}

; Function Attrs: noinline nounwind optnone
define dso_local void @app() #0 {
entry:
  %x = alloca i32, align 4
  %call = call i32 @foo(i32 noundef 5, i32 noundef 6)
  store i32 %call, ptr %x, align 4
  ret void
}

attributes #0 = { noinline nounwind optnone "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 1}
!1 = !{i32 7, !"frame-pointer", i32 2}
!2 = !{!"clang version 20.1.0 (git@github.com:Vladislave0-0/llvm-project.git 6620bb4fbb87c020823b3322eeaf45fd98791713)"}
