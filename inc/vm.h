#ifndef VM_H
#define VM_H

#include <cpu.h>

void vm_step(cpu_t* cpu);
unsigned char vm_next_8(cpu_t* cpu);
unsigned short vm_next_16(cpu_t* cpu);

#endif
