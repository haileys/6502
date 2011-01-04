#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <cpu.h>

typedef void(*ins_t)(cpu_t*, unsigned short);

#define INS(name) void ins_##name(cpu_t* cpu, unsigned short param)

INS(brk);
INS(lda);
INS(ldy);
INS(ldx);
INS(rti);
INS(jmp);
INS(beq);
INS(bne);
INS(bcc);
INS(bcs);
INS(bmi);
INS(sta);
INS(sty);
INS(inx);
INS(inc);
INS(iny);
INS(txa);
INS(tax);
INS(and);
INS(cmp);
INS(cpx);
INS(cpy);
INS(nop);
INS(adc);
INS(sbc);
INS(dey);
INS(dex);
INS(bpl);
INS(stx);
INS(txs);
INS(tya);
INS(tay);
INS(jsr);
INS(rts);
INS(cld);
INS(clc);
INS(sec);
INS(php);
INS(pha);
INS(pla);
INS(plp);
INS(bit);
INS(lsr_a);
INS(lsr);
INS(eor);

#endif
