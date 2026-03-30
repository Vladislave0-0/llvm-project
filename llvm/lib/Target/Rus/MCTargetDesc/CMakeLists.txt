add_llvm_component_library(LLVMRusDesc
  RusMCTargetDesc.cpp
  RusMCAsmInfo.cpp
  RusInstPrinter.cpp
  RusMCCodeEmitter.cpp
  RusAsmBackend.cpp
  RusELFObjectWriter.cpp

  LINK_COMPONENTS
  MC
  Support
  RusInfo

  ADD_TO_COMPONENT
  Rus
)
 