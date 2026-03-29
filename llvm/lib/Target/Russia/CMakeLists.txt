add_llvm_component_group(Russia)

set(LLVM_TARGET_DEFINITIONS Russia.td)

tablegen(LLVM RussiaGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM RussiaGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM RussiaGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM RussiaGenMCPseudoLowering.inc -gen-pseudo-lowering)
tablegen(LLVM RussiaGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM RussiaGenCallingConv.inc -gen-callingconv)
tablegen(LLVM RussiaGenAsmWriter.inc -gen-asm-writer)

add_public_tablegen_target(RussiaCommonTableGen)

add_llvm_target(RussiaCodeGen
  RussiaTargetMachine.cpp
  RussiaRegisterInfo.cpp
  RussiaInstrInfo.cpp
  RussiaSubtarget.cpp
  RussiaAsmPrinter.cpp
  RussiaISelDagToDag.cpp
  RussiaISelLowering.cpp

  LINK_COMPONENTS
  CodeGen
  Core
  Support
  Target
  RussiaInfo
  AsmPrinter
  SelectionDAG

  ADD_TO_COMPONENT
  Russia
  )

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
