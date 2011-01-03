#ifndef ADDRESSING_MODES_H
#define ADDRESSING_MODES_H

#include <cpu.h>

typedef unsigned short(*addrmode_t)(cpu_t*);

#define ADDRMODE(mode) unsigned short addrmode_##mode(cpu_t* cpu)

ADDRMODE(implied);
ADDRMODE(imm8);
ADDRMODE(imm16);
ADDRMODE(relative);

#endif
