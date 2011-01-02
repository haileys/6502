#include <cpu.h>
#include <vm.h>
#include <opcodes.h>
#include <stdio.h>
#include <stdlib.h>
#include <instructions.h>
#include <addressing_modes.h>

unsigned char vm_next_8(cpu_t* cpu)
{
	return cpu_peek(cpu, cpu->regs.pc++);
}
unsigned short vm_next_16(cpu_t* cpu)
{
	unsigned char lsb = vm_next_8(cpu);
	unsigned char msb = vm_next_8(cpu);

	return msb << 8 | lsb;
}

void vm_step(cpu_t* cpu)
{
	unsigned char opcode = vm_next_8(cpu);

	addrmode_t addressing_mode = (addrmode_t)opcodes[opcode * 2 + 1];
	ins_t instruction = (ins_t)opcodes[opcode * 2];

	if(addressing_mode == NULL || instruction == NULL)
	{
		fprintf(stderr, "** Illegal opcode: %d\n** Emulation halted.", opcode);
		exit(1);
	}
}
