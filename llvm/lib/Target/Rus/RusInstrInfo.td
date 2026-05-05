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

let Defs = [ZAKROM], Uses = [ZAKROM] in {
def ADJCALLSTACKDOWN : RusPseudoInst<(outs), (ins i32imm:$amt1, i32imm:$amt2),
    "# ADJCALLSTACKDOWN $amt1, $amt2",
    [(callseq_start timm:$amt1, timm:$amt2)]>;

def ADJCALLSTACKUP : RusPseudoInst<(outs), (ins i32imm:$amt1, i32imm:$amt2),
    "# ADJCALLSTACKUP $amt1, $amt2",
    [(callseq_end timm:$amt1, timm:$amt2)]>;
}

// ADDi
let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
def ADDi : RusInst<0x2, (outs GPR:$r1), (ins GPR:$r2, simm32:$r3_imm),
           "ADDi $r1 $r2 $r3_imm",
           [(set GPR:$r1, (add GPR:$r2, simm32:$r3_imm))]>;

// ADD
let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
def ADD : RusInst<0x1, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
          "ADD $r1 $r2 $r3_imm",
          [(set GPR:$r1, (add GPR:$r2, GPR:$r3_imm))]>;

// SHL
let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
def SHL : RusInst<0x5, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
          "SHL $r1 $r2 $r3_imm",
          [(set GPR:$r1, (shl GPR:$r2, GPR:$r3_imm))]>;

// ANDi
let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
def ANDi : RusInst<0x8, (outs GPR:$r1), (ins GPR:$r2, simm32:$r3_imm),
           "ANDi $r1 $r2 $r3_imm",
           [(set GPR:$r1, (and GPR:$r2, simm32:$r3_imm))]>;

// AND
let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
def AND : RusInst<0x7, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
          "AND $r1 $r2 $r3_imm",
          [(set GPR:$r1, (and GPR:$r2, GPR:$r3_imm))]>;

// OR
let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
def OR : RusInst<0x6, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
         "OR $r1 $r2 $r3_imm",
         [(set GPR:$r1, (or GPR:$r2, GPR:$r3_imm))]>;

// MOVi
let isAsCheapAsAMove = 1, isCodeGenOnly = 1, isReMaterializable = 1, r2 = 0 in
def MOVi : RusInst<0x4, (outs GPR:$r1), (ins simm32:$r3_imm),
                  "MOVi $r1 $r3_imm",
                  [(set GPR:$r1, simm32:$r3_imm)]>;

// MOV
let isAsCheapAsAMove = 1, isCodeGenOnly = 1, isReMaterializable = 1, r3_imm = 0 in
def MOV : RusInst<0x3, (outs GPR:$r1), (ins GPR:$r2),
          "MOV $r1 $r2", []>;

// MUL!
let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
def MUL : RusInst<0x88, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
          "MUL $r1 $r2 $r3_imm",
          [(set GPR:$r1, (mul GPR:$r2, GPR:$r3_imm))]>;

// SREMi!
let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
def SREMi : RusInst<0x89, (outs GPR:$r1), (ins GPR:$r2, simm32:$r3_imm),
           "SREMi $r1 $r2 $r3_imm",
           [(set GPR:$r1, (srem GPR:$r2, simm32:$r3_imm))]>;

// INC_EQ
let Constraints = "$r2_tmp = $r2", hasSideEffects = 1, mayLoad = 0, mayStore = 0 in
def INC_EQ : RusInst<0x90, (outs GPR:$r1, GPR:$r2_tmp), (ins GPR:$r2, simm32:$r3_imm), 
             "INC_EQ $r1 $r2 $r3_imm", []>;

// FLUSH
let r1 = 0, r2 = 0, r3_imm = 0 in
def FLUSH : RusInst<0xFF, (outs), (ins), "FLUSH", [(int_rus_flush)]>;

// PUTPIXEL
def PUTPIXEL : RusInst<0xEE, (outs), (ins GPR:$r1, GPR:$r2, GPR:$r3_imm),
                      "PUTPIXEL $r1 $r2 $r3_imm", [(int_rus_putpixel GPR:$r1, GPR:$r2, GPR:$r3_imm)]>;

// RAND
let r2 = 0, r3_imm = 0 in
def RAND : RusInst<0xDD, (outs GPR:$r1), (ins), "RAND $r1", [(set GPR:$r1, (int_rus_rand))]>;


let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in {
// CMP_EQ
def CMP_EQ  : RusInst<0x09, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
                "CMP_EQ $r1 $r2 $r3_imm",
                [(set GPR:$r1, (seteq  GPR:$r2, GPR:$r3_imm))]>;

// CMP_LT
def CMP_LT  : RusInst<0x0A, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
                "CMP_LT $r1 $r2 $r3_imm",
                [(set GPR:$r1, (setlt  GPR:$r2, GPR:$r3_imm))]>;

// CMP_GE
def CMP_GE  : RusInst<0x0B, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
                "CMP_GE $r1 $r2 $r3_imm",
                [(set GPR:$r1, (setge  GPR:$r2, GPR:$r3_imm))]>;
}

// SELECT
let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
def SELECT : RusInst<0x91, (outs GPR:$r1), (ins GPR:$r2, simm32:$imm1, simm32:$imm2, simm32:$imm3),
    "SELECT $r1 $r2 $imm1 $imm2 $imm3",
    [(set GPR:$r1, (selectcc GPR:$r2, simm32:$imm1, simm32:$imm2, simm32:$imm3, SETEQ))]>;

// Load Word
let mayLoad = 1, hasSideEffects = 0 in
def LW : RusInst<0x10, (outs GPR:$r1), (ins GPR:$r2, simm32:$r3_imm),
         "LW $r1 $r2 $r3_imm",
         [(set GPR:$r1, (load (add GPR:$r2, simm32:$r3_imm)))]>;

// Store Word
let mayStore = 1, hasSideEffects = 0 in
def SW : RusInst<0x11, (outs), (ins GPR:$r1, GPR:$r2, simm32:$r3_imm),
         "SW $r1 $r2 $r3_imm",
         [(store (i32 GPR:$r1), (add GPR:$r2, simm32:$r3_imm))]>;

// Patterns for LW and SW
def : Pat<(i32 (load GPR:$r2)), (LW GPR:$r2, 0)>;
def : Pat<(store (i32 GPR:$r1), GPR:$r2), (SW GPR:$r1, GPR:$r2, 0)>;

// CALL
let isCall = 1, hasSideEffects = 1, mayLoad = 1, mayStore = 1, r1 = 0, r2 = 0 in
def CALL : RusInst<0x92, (outs), (ins btarget32:$func),
           "CALL $func", []>;

