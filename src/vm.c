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
	unsigned short pc = cpu->regs.pc;
	
	unsigned char opcode = vm_next_8(cpu);

	addrmode_t addressing_mode = (addrmode_t)opcodes[opcode * 2 + 1];
	ins_t instruction = (ins_t)opcodes[opcode * 2];

	if(addressing_mode == NULL || instruction == NULL)
	{
		fprintf(stderr, "** Illegal opcode: $%X at address %xh\n", opcode, pc);
		fprintf(stderr, "   A: %x\n   X: %x\n   Y: %x\n** CPU halted.\n", cpu->regs.a, cpu->regs.x, cpu->regs.y);
		exit(1);
	}

	instruction(cpu, addressing_mode(cpu));
}
