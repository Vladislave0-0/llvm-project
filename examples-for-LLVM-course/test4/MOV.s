	.file	"MOV.c"
	.text
	.globl	app                             ; -- Begin function app
	.type	app,@function
app:                                    ; @app
; %bb.0:                                ; %entry
	ADDi ZAKROM ZAKROM -8
	MOVi LAPTI 10
	SW LAPTI ZAKROM 4
	LW LAPTI ZAKROM 4
	SW LAPTI ZAKROM 0
	ADDi ZAKROM ZAKROM 8
	BR LESHY
.Lfunc_end0:
	.size	app, .Lfunc_end0-app
                                        ; -- End function
	.ident	"clang version 20.1.0 (git@github.com:Vladislave0-0/llvm-project.git 4584822fcbbf706f672e2eeb3807eb730432727c)"
	.section	".note.GNU-stack","",@progbits
