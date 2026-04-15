	.file	"graphic.ll"
	.text
	.globl	app                             ; -- Begin function app
	.type	app,@function
app:                                    ; @app
; %bb.0:                                ; %entry
	MOVi LAPTI -1
	MOVi TROPKA 5
	PUTPIXEL TROPKA TROPKA LAPTI
	FLUSH
	RAND LAPTI
	BR LESHY
.Lfunc_end0:
	.size	app, .Lfunc_end0-app
                                        ; -- End function
	.section	".note.GNU-stack","",@progbits
