// RUN: mlir-opt %s --var-to-sum | FileCheck %s

emitc.func @foo() -> i32 {
  %hundred = emitc.literal "100" : i32
  %data = "emitc.variable"() { value = 42 : i32 } : () -> i32
  %result = emitc.div %hundred, %data : (i32, i32) -> i32
  emitc.return %result: i32
}

// CHECK: emitc.func @foo() -> i32 {
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
