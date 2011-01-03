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
INS(sta);
INS(inx);
INS(iny);
INS(txa);
INS(tax);
INS(and);
INS(cmp);
INS(nop);
INS(adc);
INS(dey);
INS(dex);
INS(bpl);
INS(stx);
INS(txs);
INS(jsr);
INS(rts);

#endif
