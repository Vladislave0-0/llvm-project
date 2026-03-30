// Rus Register file declaration
class RusReg<bits<16> Enc, string n> : Register<n>{
    let HWEncoding = Enc;
    let Namespace = "Rus";
}

// Registers
def LESHY     : RusReg<0, "LESHY">;         // Zero register; CalleeSavedReg
def ZAKROM    : RusReg<1, "ZAKROM">;        // Stack Pointer (SP); CalleeSavedReg
def LAPTI     : RusReg<2, "LAPTI">;         // Frame Pointer (FP)
def SHALOPAY  : RusReg<3, "SHALOPAY">;      // CalleeSavedReg
def TROPKA    : RusReg<4, "TROPKA">;        // 
def YARILO    : RusReg<5, "YARILO">;        // CalleeSavedReg
def YAGA      : RusReg<6, "YAGA">;          // CalleeSavedReg
def VYAZ      : RusReg<7, "VYAZ">;          // CalleeSavedReg
def DUB       : RusReg<8, "DUB">;           // CalleeSavedReg
def GUSLI     : RusReg<9, "GUSLI">;         // Return Value Calling Convention
def BALALAIKA : RusReg<10, "BALALAIKA">;    // Return Value Calling Convention
def PLYAS     : RusReg<11, "PLYAS">;        // Return Value Calling Convention
def VODKA     : RusReg<12, "VODKA">;        // Return Value Calling Convention
def SAMOVAR   : RusReg<13, "SAMOVAR">;      // 
def MATUSHKA  : RusReg<14, "MATUSHKA">;     // 
def GOYDA     : RusReg<15, "GOYDA">;        // 

def GPR : RegisterClass<"Rus", [i32], 32, (add
  LESHY,   
  ZAKROM,
  LAPTI,
  SHALOPAY,
  TROPKA,
  YARILO,
  YAGA,
  VYAZ,
  DUB,
  GUSLI,
  BALALAIKA,
  PLYAS,
  VODKA,
  SAMOVAR,
  MATUSHKA,
  GOYDA
)>;
