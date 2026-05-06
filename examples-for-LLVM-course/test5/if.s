	.file	"if.c"
	.text
	.globl	app                             ; -- Begin function app
	.type	app,@function
app:                                    ; @app
; %bb.0:                                ; %entry
	ADDi ZAKROM ZAKROM -4
	MOVi LAPTI 10
	SW LAPTI ZAKROM 0
	LW LAPTI ZAKROM 0
	MOVi TROPKA 6
	CMP_LT LAPTI LAPTI TROPKA
	BR_COND LAPTI .LBB0_2
	B .LBB0_1
.LBB0_1:                                ; %if.then
	MOVi LAPTI 42
	SW LAPTI ZAKROM 0
	B .LBB0_2
.LBB0_2:                                ; %if.end
	ADDi ZAKROM ZAKROM 4
	BR LESHY
.Lfunc_end0:
	.size	app, .Lfunc_end0-app
                                        ; -- End function
	.ident	"clang version 20.1.0 (git@github.com:Vladislave0-0/llvm-project.git 4584822fcbbf706f672e2eeb3807eb730432727c)"
	.section	".note.GNU-stack","",@progbits

// Если теперь этот код попытаться перевести в C-эквивалент, то получится что-то типа:
// void app() {
//   int x = 10;
//   if (!(x < 6)) { // или просто if (x >= 6), что равносильно изначальной программе на C
//     x = 42;
//   }
// }
