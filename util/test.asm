.segment "CODE"
	brk

	lda #$BE
	ldx #$EF

	nmi:
		rti
	reset:
		rti
	irq:
		lda #$DE
		ldx #$AD
		rti

.segment "VECTORS"
	.word nmi, reset, irq
