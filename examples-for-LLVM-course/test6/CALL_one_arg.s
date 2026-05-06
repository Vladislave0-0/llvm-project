	.file	"CALL.c"
	.text
	.globl	foo                             ; -- Begin function foo
	.type	foo,@function
foo:                                    ; @foo
; %bb.0:                                ; %entry
	ADD ZAKROM ZAKROM -4
	SW GUSLI ZAKROM 0
	LW LAPTI ZAKROM 0
	ADD GUSLI LAPTI 42
	ADD ZAKROM ZAKROM 4
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
	MOVi GUSLI 5
	CALL foo
	SW GUSLI ZAKROM 0
	LW ZAKROM ZAKROM 4
	ADD ZAKROM ZAKROM 8
	BR LESHY
.Lfunc_end1:
	.size	app, .Lfunc_end1-app
                                        ; -- End function
	.ident	"clang version 20.1.0 (git@github.com:Vladislave0-0/llvm-project.git 7b06a79aac9a2332b56187097e752cccf5e2b364)"
	.section	".note.GNU-stack","",@progbits
