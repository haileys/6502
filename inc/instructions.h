#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <cpu.h>

typedef void(*ins_t)(cpu_t*, unsigned short);

#define INS(name) void ins_##name(cpu_t* cpu, unsigned short param)

INS(brk);
INS(lda);
INS(ldx);
INS(rti);
INS(jmp);
INS(beq);
INS(sta);
INS(inx);

#endif
