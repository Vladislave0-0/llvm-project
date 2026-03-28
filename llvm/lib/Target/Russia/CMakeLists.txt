add_llvm_component_group(Russia)

set(LLVM_TARGET_DEFINITIONS Russia.td)

tablegen(LLVM RussiaGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM RussiaGenInstrInfo.inc -gen-instr-info)

add_public_tablegen_target(RussiaCommonTableGen)

add_llvm_target(RussiaCodeGen
  RussiaTargetMachine.cpp
  RussiaRegisterInfo.cpp
  RussiaInstrInfo.cpp

  LINK_COMPONENTS
  CodeGen
  Core
  Support
  Target
  RussiaInfo

  ADD_TO_COMPONENT
  Russia
  )

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
