add_llvm_component_library(LLVMRussiaDesc
  RussiaMCTargetDesc.cpp
  RussiaMCAsmInfo.cpp
  RussiaInstPrinter.cpp

  LINK_COMPONENTS
  MC
  Support
  RussiaInfo

  ADD_TO_COMPONENT
  Russia
 )
 