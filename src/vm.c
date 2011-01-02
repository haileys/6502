#include <cpu.h>
#include <vm.h>

#define NEXT() (cpu_peek(cpu, cpu->regs.pc++))

void vm_step(cpu_t* cpu)
{
	unsigned char opcode = NEXT();

	switch(opcode)
	{
	// ADC
		case 0x69: // imm
			cpu->regs.a += NEXT();
			break;
		case 0x65: // zpage
	}
}
