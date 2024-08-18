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
