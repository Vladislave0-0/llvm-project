// RUN: mlir-opt %s --var-to-sum | FileCheck %s
emitc.func @foo1() -> i32 {
  %hundred = emitc.literal "100" : i32
  %data = "emitc.variable"() { value = 42 : i32 } : () -> i32
  %result = emitc.div %hundred, %data : (i32, i32) -> i32
  emitc.return %result: i32
}

// CHECK: emitc.func @foo1() -> i32 {
// CHECK:     %0 = emitc.literal "100" : i32
// CHECK:     %1 = "emitc.variable"() <{value = 21 : i32}> : () -> i32
// CHECK:     %2 = "emitc.variable"() <{value = 21 : i32}> : () -> i32
// CHECK:     %3 = emitc.expression : i32 {
// CHECK:         %4 = emitc.add %1, %2 : (i32, i32) -> i32
// CHECK:         %5 = emitc.div %0, %4 : (i32, i32) -> i32
// CHECK:         emitc.yield %5 : i32
// CHECK:     }
// CHECK:     emitc.return %3 : i32
// CHECK: }


emitc.func @foo2() -> i32 {
    %0 = emitc.literal "100" : i32
    %1 = "emitc.variable"() { value = 42 : i32 } : () -> i32
    %2 = "emitc.variable"() { value = 42 : i32 } : () -> i32
    %3 = emitc.expression : i32 {
        %4 = emitc.add %1, %2 : (i32, i32) -> i32
        %5 = emitc.div %0, %4 : (i32, i32) -> i32
        emitc.yield %5 : i32
    }
    emitc.return %3 : i32
}

// CHECK: emitc.func @foo2() -> i32 {
// CHECK:     %0 = emitc.literal "100" : i32
// CHECK:     %1 = "emitc.variable"() <{value = 21 : i32}> : () -> i32
// CHECK:     %2 = "emitc.variable"() <{value = 21 : i32}> : () -> i32
// CHECK:     %3 = "emitc.variable"() <{value = 21 : i32}> : () -> i32
// CHECK:     %4 = "emitc.variable"() <{value = 21 : i32}> : () -> i32
// CHECK:     %5 = emitc.expression : i32 {
// CHECK:         %6 = emitc.add %1, %2 : (i32, i32) -> i32
// CHECK:         %7 = emitc.add %3, %4 : (i32, i32) -> i32
// CHECK:         %8 = emitc.add %6, %7 : (i32, i32) -> i32
// CHECK:         %9 = emitc.div %0, %8 : (i32, i32) -> i32
// CHECK:         emitc.yield %9 : i32
// CHECK:     }
// CHECK:     emitc.return %5 : i32
// CHECK: }


emitc.func @test_cmp() -> i1 {
  %data1 = "emitc.variable"() { value = 22 : i32 } : () -> i32
  %data2 = "emitc.variable"() { value = 22 : i32 } : () -> i32
  %result = emitc.cmp eq, %data1, %data2 : (i32, i32) -> i1
  emitc.return %result : i1
}

// CHECK: emitc.func @test_cmp() -> i1 {
// CHECK:   %0 = "emitc.variable"() <{value = 11 : i32}> : () -> i32
// CHECK:   %1 = "emitc.variable"() <{value = 11 : i32}> : () -> i32
// CHECK:   %2 = "emitc.variable"() <{value = 11 : i32}> : () -> i32
// CHECK:   %3 = "emitc.variable"() <{value = 11 : i32}> : () -> i32
// CHECK:   %4 = emitc.expression : i1 {
// CHECK:     %5 = emitc.add %0, %1 : (i32, i32) -> i32
// CHECK:     %6 = emitc.add %2, %3 : (i32, i32) -> i32
// CHECK:     %7 = emitc.cmp eq, %5, %6 : (i32, i32) -> i1
// CHECK:     emitc.yield %7 : i1
// CHECK:   }
// CHECK:   emitc.return %4 : i1
// CHECK: }


emitc.func @test_if(%arg0: i1, %arg1: f32) {
  emitc.if %arg0 {
    %hundred = emitc.literal "100" : i32
    %data = "emitc.variable"() { value = 42 : i32 } : () -> i32
    %result = emitc.div %hundred, %data : (i32, i32) -> i32
  }
  emitc.return
}

// CHECK: emitc.func @test_if(%arg0: i1, %arg1: f32) {
// CHECK:   emitc.if %arg0 {
// CHECK:     %0 = emitc.literal "100" : i32
// CHECK:     %1 = "emitc.variable"() <{value = 21 : i32}> : () -> i32
// CHECK:     %2 = "emitc.variable"() <{value = 21 : i32}> : () -> i32
// CHECK:     %3 = emitc.expression : i32 {
// CHECK:       %4 = emitc.add %1, %2 : (i32, i32) -> i32
// CHECK:       %5 = emitc.div %0, %4 : (i32, i32) -> i32
// CHECK:       emitc.yield %5 : i32
// CHECK:     }
// CHECK:   }
// CHECK:   emitc.return
// CHECK: }


emitc.func @test_double_use(%arg0: i1, %arg1: f32) {
    %0 = emitc.literal "100" : i32
    %1 = "emitc.variable"() <{value = 21 : i32}> : () -> i32
    %2 = "emitc.variable"() <{value = 21 : i32}> : () -> i32
    %3 = emitc.div %0, %1 : (i32, i32) -> i32
    %4 = emitc.expression : i32 {
        %5 = emitc.add %1, %2 : (i32, i32) -> i32
        %6 = emitc.div %0, %5 : (i32, i32) -> i32
        emitc.yield %6 : i32
    }
  emitc.return
}

// CHECK: emitc.func @test_double_use(%arg0: i1, %arg1: f32) {
// CHECK:   %0 = emitc.literal "100" : i32
// CHECK:   %1 = "emitc.variable"() <{value = 10 : i32}> : () -> i32
// CHECK:   %2 = "emitc.variable"() <{value = 11 : i32}> : () -> i32
// CHECK:   %3 = "emitc.variable"() <{value = 10 : i32}> : () -> i32
// CHECK:   %4 = "emitc.variable"() <{value = 11 : i32}> : () -> i32
// CHECK:   %5 = emitc.expression : i32 {
// CHECK:     %7 = emitc.add %1, %2 : (i32, i32) -> i32
// CHECK:     %8 = emitc.div %0, %7 : (i32, i32) -> i32
// CHECK:     emitc.yield %8 : i32
// CHECK:   }
// CHECK:   %6 = emitc.expression : i32 {
// CHECK:     %7 = emitc.add %1, %2 : (i32, i32) -> i32
// CHECK:     %8 = emitc.add %3, %4 : (i32, i32) -> i32
// CHECK:     %9 = emitc.add %7, %8 : (i32, i32) -> i32
// CHECK:     %10 = emitc.div %0, %9 : (i32, i32) -> i32
// CHECK:     emitc.yield %10 : i32
// CHECK:   }
// CHECK:   emitc.return
// CHECK: }


emitc.global @myglobal_int : i32 = 4
emitc.func @test_assign(%arg0: i32, %arg1: i32) {
  %data1 = "emitc.variable"() <{value = 50 : i32}> : () -> i32
  %data2 = emitc.get_global @myglobal_int : i32
  emitc.assign %data1 : i32 to %data2 : i32
  emitc.return
}

// CHECK: emitc.global @myglobal_int : i32 = 4
// CHECK: emitc.func @test_assign(%arg0: i32, %arg1: i32) {
// CHECK:   %0 = "emitc.variable"() <{value = 25 : i32}> : () -> i32
// CHECK:   %1 = "emitc.variable"() <{value = 25 : i32}> : () -> i32
// CHECK:   %2 = emitc.get_global @myglobal_int : i32
// CHECK:   %3 = emitc.add %0, %1 : (i32, i32) -> i32
// CHECK:   emitc.assign %3 : i32 to %2 : i32
// CHECK:   emitc.return
// CHECK: }


emitc.func @test_cast() {
  %data = "emitc.variable"() <{value = 50 : i32}> : () -> i32
  %cast = emitc.cast %data : i32 to f32
  emitc.return
}

// CHECK: emitc.func @test_cast() {
// CHECK:   %0 = "emitc.variable"() <{value = 25 : i32}> : () -> i32
// CHECK:   %1 = "emitc.variable"() <{value = 25 : i32}> : () -> i32
// CHECK:   %2 = emitc.expression : f32 {
// CHECK:     %3 = emitc.add %0, %1 : (i32, i32) -> i32
// CHECK:     %4 = emitc.cast %3 : i32 to f32
// CHECK:     emitc.yield %4 : f32
// CHECK:   }
// CHECK:   emitc.return
// CHECK: }


emitc.func @foo3(%arg0: i32) -> i32 {
  %var = "emitc.variable"() { value = 42 : i32 } : () -> i32
  emitc.return %var : i32
}
emitc.func @test_func_call(%arg0: i32) -> i32 {
    %var = "emitc.variable"() { value = 42 : i32 } : () -> i32
    %call_result = emitc.call @foo3(%var) : (i32) -> i32
    emitc.return %call_result : i32
}

// CHECK: emitc.func @foo3(%arg0: i32) -> i32 {
// CHECK:   %0 = "emitc.variable"() <{value = 21 : i32}> : () -> i32
// CHECK:   %1 = "emitc.variable"() <{value = 21 : i32}> : () -> i32
// CHECK:   %2 = emitc.add %0, %1 : (i32, i32) -> i32
// CHECK:   emitc.return %2 : i32
// CHECK: }
// CHECK: emitc.func @test_func_call(%arg0: i32) -> i32 {
// CHECK:   %0 = "emitc.variable"() <{value = 21 : i32}> : () -> i32
// CHECK:   %1 = "emitc.variable"() <{value = 21 : i32}> : () -> i32
// CHECK:   %2 = emitc.expression : i32 {
// CHECK:     %3 = emitc.add %0, %1 : (i32, i32) -> i32
// CHECK:     %4 = emitc.call @foo3(%3) : (i32) -> i32
// CHECK:     emitc.yield %4 : i32
// CHECK:   }
// CHECK:   emitc.return %2 : i32
// CHECK: }
