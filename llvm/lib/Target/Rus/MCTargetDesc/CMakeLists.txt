add_llvm_component_library(LLVMRusDesc
  RusMCTargetDesc.cpp
  RusMCAsmInfo.cpp
  RusInstPrinter.cpp

  LINK_COMPONENTS
  MC
  Support
  RusInfo

  ADD_TO_COMPONENT
  Rus
)
 