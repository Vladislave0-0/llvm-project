emitc.func @foo() -> i32 {
    %hundred = emitc.literal "100" : i32

    %data = "emitc.variable"() { value = 42 : i32 } : () -> i32

    %result = emitc.div %hundred, %data : (i32, i32) -> i32

    emitc.return %result: i32
}
