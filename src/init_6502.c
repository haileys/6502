#include <init_6502.h>
#include <stdlib.h>
#include <stdio.h>

void _char_out(cpu_t* cpu, void*, unsigned short addr, unsigned char val);


void init_6502(cpu_t* cpu)
{
	cpu->regs.pc = 0;

	// mmap 0x0201 to character out
	mmapseg_t mmap = {
		.address = 0x201,
		.length = 1,
		.set = _char_out,
		.get = NULL,
		.state = NULL,
	};
	cpu_mmap(cpu, &mmap);
}

void _char_out(cpu_t* cpu, void* state, unsigned short addr, unsigned char val)
{
	putchar(val);
	fflush(stdout);
}


