.segment "CODE"

	ldx #0
	loop:
		lda msg,x
		beq end
		sta $201 ; mmapped character out
		inx
		jmp loop

	end:
		jmp end

	isr:
		rti

	msg: .byt "Hello, World!", $0

.segment "VECTORS"
	.word isr, isr, isr
