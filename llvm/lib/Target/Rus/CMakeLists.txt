add_llvm_component_group(Rus)

set(LLVM_TARGET_DEFINITIONS Rus.td)

tablegen(LLVM RusGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM RusGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM RusGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM RusGenMCPseudoLowering.inc -gen-pseudo-lowering)
tablegen(LLVM RusGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM RusGenCallingConv.inc -gen-callingconv)
tablegen(LLVM RusGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM RusGenMCCodeEmitter.inc -gen-emitter)

add_public_tablegen_target(RusCommonTableGen)

add_llvm_target(RusCodeGen
  RusTargetMachine.cpp
  RusRegisterInfo.cpp
  RusInstrInfo.cpp
  RusSubtarget.cpp
  RusAsmPrinter.cpp
  RusISelDagToDag.cpp
  RusISelLowering.cpp
  RusMCInstLower.cpp
  RusFrameLowering.cpp

  LINK_COMPONENTS
  CodeGen
  Core
  Support
  Target
  RusInfo
  AsmPrinter
  SelectionDAG

  ADD_TO_COMPONENT
  Rus
)

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
