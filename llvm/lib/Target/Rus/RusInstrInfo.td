//===----------------------------------------------------------------------===//
// Rus profiles and nodes
//===----------------------------------------------------------------------===//

def rus_ret     : SDNode<"RusISD::RET", SDTNone,
                            [SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;

def SDT_RusBrCC : SDTypeProfile<0, 2, [SDTCisVT<0, i32>,
                                        SDTCisVT<1, OtherVT>]>;
def rus_brcc    : SDNode<"RusISD::BR_CC", SDT_RusBrCC,
                            [SDNPHasChain]>;

def SDT_CallSeqStart : SDCallSeqStart<[SDTCisVT<0, i32>, SDTCisVT<1, i32>]>;
def SDT_CallSeqEnd   : SDCallSeqEnd<[SDTCisVT<0, i32>, SDTCisVT<1, i32>]>;

def callseq_start : SDNode<"ISD::CALLSEQ_START", SDT_CallSeqStart,
                            [SDNPHasChain, SDNPOutGlue]>;
def callseq_end   : SDNode<"ISD::CALLSEQ_END",   SDT_CallSeqEnd,
                            [SDNPHasChain, SDNPOptInGlue, SDNPOutGlue]>;

def SDT_RusCall : SDTypeProfile<0, 1, [SDTCisVT<0, i32>]>;
def Rus_call    : SDNode<"RusISD::CALL", SDT_RusCall,
                              [SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;

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

// BRANCH (direct)
let hasSideEffects = 0, mayLoad = 0, mayStore = 0, isBarrier = 1, isBranch = 1, isTerminator = 1, r1 = 0, r2 = 0 in
def B : RusInstB<0xB0, (outs), (ins btarget32:$btarget), "B $btarget",
                [(br bb:$btarget)]>;

// BR_COND
let isBranch = 1, isTerminator = 1, r2 = 0 in
def BR_COND : RusInstB<0xBC, (outs), (ins GPR:$r1, btarget32:$btarget),
                      "BR_COND $r1 $btarget",
                      [(rus_brcc GPR:$r1, bb:$btarget)]>;

// BRANCH (indirect)
let hasSideEffects = 0, mayLoad = 0, mayStore = 0, isCall = 1, isBranch = 1, isTerminator = 1, r2 = 0, r3_imm = 0 in
def BR : RusInst<0xBB, (outs), (ins GPR:$r1), "BR $r1",
                 [(brind GPR:$r1)]>;

// CALL
let isCall = 1, hasSideEffects = 1, mayLoad = 1, mayStore = 1, r1 = 0, r2 = 0 in
def CALL : RusInstB<0x92, (outs), (ins btarget32:$btarget),
           "CALL $btarget", []>;

let isBarrier = 1, isReturn = 1, isTerminator = 1 in
def PseudoRET : RusPseudoInst<(outs), (ins), "# PseudoRET",
                [(rus_ret)]>,
                PseudoInstExpansion<(BR LESHY)>;

let Defs = [ZAKROM], Uses = [ZAKROM] in {
def ADJCALLSTACKDOWN : RusPseudoInst<(outs), (ins i32imm:$amt1, i32imm:$amt2),
    "# ADJCALLSTACKDOWN $amt1, $amt2",
    [(callseq_start timm:$amt1, timm:$amt2)]>;

def ADJCALLSTACKUP : RusPseudoInst<(outs), (ins i32imm:$amt1, i32imm:$amt2),
    "# ADJCALLSTACKUP $amt1, $amt2",
    [(callseq_end timm:$amt1, timm:$amt2)]>;
}

multiclass Arith<bits<8> opcode, SDPatternOperator op> {
    def NAME : RusInstR<opcode, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3),
               NAME#" $r1 $r2 $r3",
               [(set GPR:$r1, (op GPR:$r2, GPR:$r3))]>;

    def NAME#i : RusInstI<!add(opcode, 0x10), (outs GPR:$r1), (ins GPR:$r2, simm32:$imm32),
                 NAME#" $r1 $r2 $imm32",
                 [(set GPR:$r1, (op GPR:$r2, simm32:$imm32))]>;
}

defm ADD  : Arith<0x01, add>;
defm SUB  : Arith<0x02, sub>;
defm MUL  : Arith<0x03, mul>;
defm DIV  : Arith<0x04, sdiv>;
defm UDIV : Arith<0x05, udiv>;
defm AND  : Arith<0x06, and>;
defm OR   : Arith<0x07, or>;
defm XOR  : Arith<0x08, xor>;
defm SREM : Arith<0x09, srem>;
defm UREM : Arith<0x0a, urem>;
defm SHL  : Arith<0x0b, shl>;
defm SRL  : Arith<0x0d, srl>;
defm SRA  : Arith<0x0e, sra>;

// MOVi
let isAsCheapAsAMove = 1, isCodeGenOnly = 1, isReMaterializable = 1, r2 = 0 in
def MOVi : RusInstI<0x40, (outs GPR:$r1), (ins simm32:$imm32),
                  "MOVi $r1 $imm32",
                  [(set GPR:$r1, simm32:$imm32)]>;

// MOV
let isAsCheapAsAMove = 1, isCodeGenOnly = 1, isReMaterializable = 1, r3_imm = 0 in
def MOV : RusInst<0x41, (outs GPR:$r1), (ins GPR:$r2),
          "MOV $r1 $r2", []>;

// FLUSH
let r1 = 0, r2 = 0, r3_imm = 0 in
def FLUSH : RusInst<0xFF, (outs), (ins), "FLUSH", [(int_rus_flush)]>;

// PUTPIXEL
def PUTPIXEL : RusInstR<0xEE, (outs), (ins GPR:$r1, GPR:$r2, GPR:$r3),
                      "PUTPIXEL $r1 $r2 $r3", [(int_rus_putpixel GPR:$r1, GPR:$r2, GPR:$r3)]>;

// RAND
let r2 = 0, r3_imm = 0 in
def RAND : RusInst<0xDD, (outs GPR:$r1), (ins), "RAND $r1", [(set GPR:$r1, (int_rus_rand))]>;

// MEMSET
let hasSideEffects = 1, mayLoad = 0, mayStore = 1 in
def MEMSET : RusInstR<0x93, (outs), (ins GPR:$r1, GPR:$r2, GPR:$r3),
             "MEMSET $r1 $r2 $r3", []>;

//MEMCPY
let hasSideEffects = 1, mayLoad = 1, mayStore = 1 in
def MEMCPY : RusInstR<0x94, (outs), (ins GPR:$r1, GPR:$r2, GPR:$r3),
             "MEMCPY $r1 $r2 $r3", []>;

// INC_EQ
let Constraints = "$r2_tmp = $r2", hasSideEffects = 1, mayLoad = 0, mayStore = 0 in
def INC_EQ : RusInstI<0x90, (outs GPR:$r1, GPR:$r2_tmp), (ins GPR:$r2, simm32:$imm32), 
             "INC_EQ $r1 $r2 $imm32", []>;

// let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in {
// // CMP_EQ
// def CMP_EQ  : RusInstR<0x09, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3),
//                 "CMP_EQ $r1 $r2 $r3",
//                 [(set GPR:$r1, (seteq  GPR:$r2, GPR:$r3))]>;

// // CMP_LT
// def CMP_LT  : RusInstR<0x0A, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3),
//                 "CMP_LT $r1 $r2 $r3",
//                 [(set GPR:$r1, (setlt  GPR:$r2, GPR:$r3))]>;

// // CMP_GE
// def CMP_GE  : RusInstR<0x0B, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3),
//                 "CMP_GE $r1 $r2 $r3",
//                 [(set GPR:$r1, (setge  GPR:$r2, GPR:$r3))]>;
// }

multiclass CmpInst<bits<8> opcode, string Name, CondCode cc> {
  // Reg-Reg
  def "" : RusInstR<opcode, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3),
           Name#" $r1 $r2 $r3",
           [(set GPR:$r1, (setcc GPR:$r2, GPR:$r3, cc))]>;

  // Reg-Imm
  def "i" : RusInstI<opcode, (outs GPR:$r1), (ins GPR:$r2, simm32:$imm32),
            Name#"i $r1 $r2 $imm32",
            [(set GPR:$r1, (setcc GPR:$r2, simm32:$imm32, cc))]>;
}

let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in {
  defm CMP_EQ  : CmpInst<0x20, "CMP_EQ",  SETEQ>;
  defm CMP_NE  : CmpInst<0x21, "CMP_NE",  SETNE>;
  defm CMP_LT  : CmpInst<0x22, "CMP_LT",  SETLT>;
  defm CMP_LE  : CmpInst<0x23, "CMP_LE",  SETLE>;
  defm CMP_GT  : CmpInst<0x24, "CMP_GT",  SETGT>;
  defm CMP_GE  : CmpInst<0x25, "CMP_GE",  SETGE>;

  defm CMP_ULT : CmpInst<0x30, "CMP_ULT", SETULT>;
  defm CMP_ULE : CmpInst<0x31, "CMP_ULE", SETULE>;
  defm CMP_UGT : CmpInst<0x32, "CMP_UGT", SETUGT>;
  defm CMP_UGE : CmpInst<0x33, "CMP_UGE", SETUGE>;
}

// SELECT
let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
def SELECT : RusInst<0x91, (outs GPR:$r1), (ins GPR:$r2, simm32:$imm1, simm32:$imm2, simm32:$imm3),
    "SELECT $r1 $r2 $imm1 $imm2 $imm3",
    [(set GPR:$r1, (selectcc GPR:$r2, simm32:$imm1, simm32:$imm2, simm32:$imm3, SETEQ))]>;

// Load Word
let mayLoad = 1, hasSideEffects = 0 in
def LW : RusInstI<0x10, (outs GPR:$r1), (ins GPR:$r2, simm32:$imm32),
         "LW $r1 $r2 $imm32",
         [(set GPR:$r1, (load (add GPR:$r2, simm32:$imm32)))]>;

// Store Word
let mayStore = 1, hasSideEffects = 0 in
def SW : RusInstI<0x11, (outs), (ins GPR:$r1, GPR:$r2, simm32:$imm32),
         "SW $r1 $r2 $imm32",
         [(store (i32 GPR:$r1), (add GPR:$r2, simm32:$imm32))]>;

// Patterns for LW and SW
def : Pat<(i32 (load GPR:$r2)), (LW GPR:$r2, 0)>;
def : Pat<(store (i32 GPR:$r1), GPR:$r2), (SW GPR:$r1, GPR:$r2, 0)>;
