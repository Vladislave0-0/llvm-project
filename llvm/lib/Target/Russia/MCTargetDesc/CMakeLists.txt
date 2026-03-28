add_llvm_component_library(LLVMRussiaDesc
  RussiaMCTargetDesc.cpp
  RussiaMCAsmInfo.cpp

  LINK_COMPONENTS
  MC
  Support
  RussiaInfo

  ADD_TO_COMPONENT
  Russia
 )
 