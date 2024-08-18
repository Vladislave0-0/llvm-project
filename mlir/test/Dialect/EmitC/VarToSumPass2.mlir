// RUN: mlir-opt %s --var-to-sum | FileCheck %s

emitc.func @foo() -> i32 {
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

// CHECK: emitc.func @foo() -> i32 {
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
