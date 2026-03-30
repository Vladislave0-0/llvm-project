//===----------------------------------------------------------------------===//
// This describes the calling conventions for Rus architecture.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Rus Return Value Calling Convention
//===----------------------------------------------------------------------===//
def RetCC_Rus : CallingConv<[
  // i32 return values
  CCIfType<[i32, i64], CCAssignToReg<[GUSLI, BALALAIKA, PLYAS, VODKA]>>,

  // Integer values get stored in stack slots that are 4 bytes in
  // size and 4-byte aligned.
  CCIfType<[i64], CCAssignToStack<8, 4>>,
  CCIfType<[i32], CCAssignToStack<4, 4>>
]>;

//===----------------------------------------------------------------------===//
// Rus Argument Calling Conventions
//===----------------------------------------------------------------------===//
def CC_Rus : CallingConv<[
  // Promote i8/i16 arguments to i32.
  CCIfType<[i8, i16], CCPromoteToType<i32>>,

  // The first 4 integer arguments are passed in integer registers.
  CCIfType<[i32, i64], CCAssignToReg<[GUSLI, BALALAIKA, PLYAS, VODKA]>>,

  // Integer values get stored in stack slots that are 4 bytes in
  // size and 4-byte aligned.
  CCIfType<[i64], CCAssignToStack<8, 4>>,
  CCIfType<[i32], CCAssignToStack<4, 4>>
]>;

def CSR_Rus : CalleeSavedRegs<(add LESHY, ZAKROM, SHALOPAY, YARILO, YAGA, VYAZ, DUB)>;
