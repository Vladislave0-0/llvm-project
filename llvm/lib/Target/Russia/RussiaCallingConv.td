//===----------------------------------------------------------------------===//
// This describes the calling conventions for Russia architecture.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Russia Return Value Calling Convention
//===----------------------------------------------------------------------===//
def RetCC_Russia : CallingConv<[
  // i32 return values
  CCIfType<[i32, i64], CCAssignToReg<[VODKA0, VODKA1, VODKA2, VODKA3]>>,

  // Integer values get stored in stack slots that are 4 bytes in
  // size and 4-byte aligned.
  CCIfType<[i64], CCAssignToStack<8, 4>>,
  CCIfType<[i32], CCAssignToStack<4, 4>>
]>;

//===----------------------------------------------------------------------===//
// Russia Argument Calling Conventions
//===----------------------------------------------------------------------===//
def CC_Russia : CallingConv<[
  // Promote i8/i16 arguments to i32.
  CCIfType<[i8, i16], CCPromoteToType<i32>>,

  // The first 4 integer arguments are passed in integer registers.
  CCIfType<[i32, i64], CCAssignToReg<[VODKA0, VODKA1, VODKA2, VODKA3]>>,

  // Integer values get stored in stack slots that are 4 bytes in
  // size and 4-byte aligned.
  CCIfType<[i64], CCAssignToStack<8, 4>>,
  CCIfType<[i32], CCAssignToStack<4, 4>>
]>;

def CSR_Russia : CalleeSavedRegs<(add VODKA7, VODKA8, VODKA9, VODKA10, VODKA11, VODKA12, VODKA13, VODKA14)>;
