//===----------------------------------------------------------------------===//
// Rus profiles and nodes
//===----------------------------------------------------------------------===//

def rus_ret     : SDNode<"RusISD::RET", SDTNone,
                            [SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;

def SDT_rusBrCC : SDTypeProfile<0, 2, [SDTCisVT<0, i32>,
                                        SDTCisVT<1, OtherVT>]>;
def rus_brcc    : SDNode<"RusISD::BR_CC", SDT_rusBrCC,
                            [SDNPHasChain]>;

//===----------------------------------------------------------------------===//
// Instruction format superclass
//===----------------------------------------------------------------------===//

include "RusInstrFormats.td"

//===----------------------------------------------------------------------===//
// Rus Operand, Complex Patterns and Transformations Definitions.
//===----------------------------------------------------------------------===//

class SImmAsmOperand<int width> : AsmOperandClass {
  let Name = "SImm" # width;
  let RenderMethod = "addImmOperands";
  let DiagnosticType = !strconcat("Invalid", Name);
}

def simm32 : Operand<i32>, ImmLeaf<i32, [{return isInt<32>(Imm);}]> {
  let ParserMatchClass = SImmAsmOperand<32>;
  let EncoderMethod = "getSImm32OpValue";
  let DecoderMethod = "decodeSImmOperand<32>";
  let MCOperandPredicate = [{
    int64_t Imm;
    if (MCOp.evaluateAsConstantImm(Imm))
      return isInt<32>(Imm);
    return MCOp.isBareSymbolRef();
  }];
  let OperandType = "OPERAND_SIMM32";
  let OperandNamespace = "RusOp";
}

def btarget32 : Operand<OtherVT> {
  let ParserMatchClass = SImmAsmOperand<32>;
  let PrintMethod = "printBranchOperand";
  let EncoderMethod = "getBranchTarget32OpValue";
  let DecoderMethod = "decodeSImmOperand<32>";
  let MCOperandPredicate = [{
    int64_t Imm;
    if (MCOp.evaluateAsConstantImm(Imm))
      return isInt<32>(Imm);
    return MCOp.isBareSymbolRef();
  }];
  let OperandType = "OPERAND_PCREL";
}

//===----------------------------------------------------------------------===//
// Rus Instructions
//===----------------------------------------------------------------------===//

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, isBarrier = 1, isBranch = 1, isTerminator = 1, r1 = 0, r2 = 0 in
def B : RusInst<0xB0, (outs), (ins btarget32:$r3_imm), "B $r3_imm",
                [(br bb:$r3_imm)]>;

let isBranch = 1, isTerminator = 1, r2 = 0 in
def BR_COND : RusInst<0xBC, (outs), (ins GPR:$r1, btarget32:$r3_imm),
                      "BR_COND $r1 $r3_imm",
                      [(rus_brcc GPR:$r1, bb:$r3_imm)]>;

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, isCall = 1, isBranch = 1, isTerminator = 1, r2 = 0, r3_imm = 0 in
def BR : RusInst<0xBB, (outs), (ins GPR:$r1), "BR $r1",
                 [(brind GPR:$r1)]>;

let isBarrier = 1, isReturn = 1, isTerminator = 1 in
def PseudoRET : RusPseudoInst<(outs), (ins), "# PseudoRET",
                [(rus_ret)]>,
                PseudoInstExpansion<(BR LESHY)>;

// movi
let isAsCheapAsAMove = 1, isCodeGenOnly = 1, isReMaterializable = 1, r2 = 0 in
def MOVI : RusInst<0xAA, (outs GPR:$r1), (ins simm32:$r3_imm),
                  "MOVi $r1 $r3_imm",
                  [(set GPR:$r1, simm32:$r3_imm)]>;

// flush
let r1 = 0, r2 = 0, r3_imm = 0 in
def FLUSH : RusInst<0xFF, (outs), (ins), "FLUSH", [(int_rus_flush)]>;

// putpixel
def PUTPIXEL : RusInst<0xEE, (outs), (ins GPR:$r1, GPR:$r2, GPR:$r3_imm),
                      "PUTPIXEL $r1 $r2 $r3_imm", [(int_rus_putpixel GPR:$r1, GPR:$r2, GPR:$r3_imm)]>;

// rand
let r2 = 0, r3_imm = 0 in
def RAND : RusInst<0xDD, (outs GPR:$r1), (ins), "RAND $r1", [(set GPR:$r1, (int_rus_rand))]>;


let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in {
def CMP_EQ  : RusInst<0x09, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
                "CMP_EQ $r1 $r2 $r3_imm",
                [(set GPR:$r1, (seteq  GPR:$r2, GPR:$r3_imm))]>;

def CMP_LT  : RusInst<0x0A, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
                "CMP_LT $r1 $r2 $r3_imm",
                [(set GPR:$r1, (setlt  GPR:$r2, GPR:$r3_imm))]>;

def CMP_GE  : RusInst<0x0B, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
                "CMP_GE $r1 $r2 $r3_imm",
                [(set GPR:$r1, (setge  GPR:$r2, GPR:$r3_imm))]>;
} // hasSideEffects = 0
