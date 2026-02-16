add_llvm_component_group(Russia)

add_llvm_target(RussiaCodeGen
  RussiaTargetMachine.cpp

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
