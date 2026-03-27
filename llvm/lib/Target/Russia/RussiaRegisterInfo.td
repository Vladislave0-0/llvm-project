// Russia Register file declaration
class RussiaReg<bits<16> Enc, string n> : Register<n>{
    let HWEncoding = Enc;
    let Namespace = "Russia";
}

// Registers
foreach I = 0-15 in {
    def VODKA#I : RussiaReg<I, "vodka"#I>;
}

// Classes
def GPR : RegisterClass<"Russia", [i32], 32, (add
  VODKA0, VODKA1, VODKA2, VODKA3, VODKA4, VODKA5, VODKA6, VODKA7, VODKA8, VODKA9, VODKA10, VODKA11, VODKA12, VODKA13, VODKA14, VODKA15)>;
  