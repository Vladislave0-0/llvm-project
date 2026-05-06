	.file	"call.c"
	.text
	.globl	foo                             ; -- Begin function foo
	.type	foo,@function
foo:                                    ; @foo
; %bb.0:                                ; %entry
	MOVi GUSLI 42
	BR LESHY
.Lfunc_end0:
	.size	foo, .Lfunc_end0-foo
                                        ; -- End function
	.globl	app                             ; -- Begin function app
	.type	app,@function
app:                                    ; @app
; %bb.0:                                ; %entry
	ADD ZAKROM ZAKROM -8
	SW ZAKROM ZAKROM 4
	CALL foo
	SW GUSLI ZAKROM 0
	LW ZAKROM ZAKROM 4
	ADD ZAKROM ZAKROM 8
	BR LESHY
.Lfunc_end1:
	.size	app, .Lfunc_end1-app
                                        ; -- End function
	.ident	"clang version 20.1.0 (git@github.com:Vladislave0-0/llvm-project.git 4584822fcbbf706f672e2eeb3807eb730432727c)"
	.section	".note.GNU-stack","",@progbits
