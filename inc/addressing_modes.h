#ifndef ADDRESSING_MODES_H
#define ADDRESSING_MODES_H

#include <cpu.h>

typedef unsigned short(*addrmode_t)(cpu_t*);

#define ADDRMODE(mode) unsigned short addrmode_##mode(cpu_t* cpu)

ADDRMODE(implied);
ADDRMODE(imm8);
ADDRMODE(imm16);
ADDRMODE(relative);
ADDRMODE(abs);
ADDRMODE(abs_deref);
ADDRMODE(absx);
ADDRMODE(absx_deref);
ADDRMODE(absy);
ADDRMODE(absy_deref);
ADDRMODE(zp);
ADDRMODE(zp_deref);
ADDRMODE(zpx);
ADDRMODE(zpx_deref);
ADDRMODE(indirect);
ADDRMODE(indy);
ADDRMODE(indy_deref);
ADDRMODE(indx);
ADDRMODE(indx_deref);

#endif
