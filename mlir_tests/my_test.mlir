emitc.func @foo(%arg0: i32) -> i32 {
  %var = "emitc.variable"() { value = 42 : i32 } : () -> i32
  emitc.return %var : i32
}

emitc.func @test_func_calls(%arg0: i32) -> i32 {
    %var = "emitc.variable"() { value = 42 : i32 } : () -> i32
    %call_result = emitc.call @foo(%var) : (i32) -> i32
    emitc.return %call_result : i32
}
