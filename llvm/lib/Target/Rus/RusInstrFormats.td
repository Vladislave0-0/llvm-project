//===----------------------------------------------------------------------===//
//  Describe Rus instructions format
//
//  CPU INSTRUCTION FORMATS
//
//  FF F F 0000 FFFFFFFF
//  ^  ^ ^    ^        ^
//  |  | |    |        +-- [31:0]  r3_imm  - third reg or 32-bit immediate
//  |  | |    +----------- [47:32] padding - reserved (zeros)
//  |  | +---------------- [51:48] r2      - second register (4 bits)
//  |  +------------------ [55:52] r1      - first register (4 bits)
//  +--------------------- [63:56] opcode  - operation code (8 bits)
//
//===----------------------------------------------------------------------===//

// Generic Rus Format
class RusInst<bits<8> op, dag outs, dag ins, string asmstr, list<dag> pattern>: Instruction
{
  // Inst and Size: for tablegen(... -gen-emitter) and
  // tablegen(... -gen-disassembler) in CMakeLists.txt
  let Namespace = "Rus";
  let DecoderNamespace = "Rus";
  let Size = 8;

  field bits<64> Inst;

  bits<8>  Opcode = op;
  bits<4>  r1;
  bits<4>  r2;
  bits<32> r3_imm = 0;

  let Inst{63-56} = Opcode;
  let Inst{55-52} = r1;
  let Inst{51-48} = r2;
  let Inst{47-32} = 0;
  let Inst{31-0}  = 0;

  let OutOperandList = outs;
  let InOperandList  = ins;
  let AsmString   = asmstr;
  let Pattern     = pattern;
}

// R-type: Register-to-register operations.
// Used for computations where all operands are registers (e.g., ADD, MUL).
class RusInstR<bits<8> op, dag outs, dag ins, string asmstr, list<dag> pattern>
    : RusInst<op, outs, ins, asmstr, pattern> {
  bits<4> r3;
  let Inst{3-0} = r3;
}

// I-type: Immediate operations.
// Used for instructions that include a 32-bit constant value (e.g., ADDi, LW, SW).
class RusInstI<bits<8> op, dag outs, dag ins, string asmstr, list<dag> pattern>
    : RusInst<op, outs, ins, asmstr, pattern> {
  bits<32> imm32;
  let Inst{31-0} = imm32;
}

// B-type: Branch and Call operations.
// A specialized format for jump targets, supporting PC-relative addressing.
class RusInstB<bits<8> op, dag outs, dag ins, string asmstr, list<dag> pattern>
    : RusInst<op, outs, ins, asmstr, pattern> {
  bits<32> btarget;
  let Inst{31-0} = btarget;
}

// Pseudo instructions format
class RusPseudoInst<dag outs, dag ins, string asmstr, list<dag> pattern>
   : RusInst<0, outs, ins, asmstr, pattern> {
  let isPseudo = 1;
  let isCodeGenOnly = 1;
}
