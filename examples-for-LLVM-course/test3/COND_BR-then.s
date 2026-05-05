	.file	"COND_BR-then.ll"
	.text
	.globl	app                             ; -- Begin function app
	.type	app,@function
app:                                    ; @app
; %bb.0:                                ; %entry
	MOVli LAPTI -1
	MOVli TROPKA 5
	PUTPIXEL TROPKA TROPKA LAPTI
	FLUSH
	BR LESHY
.Lfunc_end0:
	.size	app, .Lfunc_end0-app
                                        ; -- End function
	.section	".note.GNU-stack","",@progbits
