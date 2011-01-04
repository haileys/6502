#ifndef OPCODES_H
#define OPCODES_H

#define OP(i,a) (ins_##i), (addrmode_##a)
#define ILLEGAL NULL, NULL

extern void* opcodes[];

#endif
