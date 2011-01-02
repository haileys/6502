#include <stdlib.h>
#include "cpu.h"

cpu_t* new_cpu()
{
	cpu_t* cpu = (cpu_t*)malloc(sizeof(cpu_t));
	cpu->mem = (unsigned char*)calloc(1, 65536);
	cpu->regs.sp = 255;
	return cpu;
}

void free_cpu(cpu_t* cpu)
{
	free(cpu->mem);
	free(cpu);
}

void cpu_push_8(cpu_t* cpu, unsigned char val)
{
	cpu->mem[256 + cpu->regs.sp] = val;
	cpu->regs.sp--;
}
void cpu_push_16(cpu_t* cpu, unsigned short val)
{
	cpu_push_8(cpu, (val >> 8) & 255);
	cpu_push_8(cpu, val & 255);
}

unsigned char cpu_pop_8(cpu_t* cpu)
{
	cpu->regs.sp++;
	return cpu->mem[256 + cpu->regs.sp];
}
unsigned short cpu_pop_16(cpu_t* cpu)
{
	char lsb = cpu_pop_8(cpu);
	char msb = cpu_pop_8(cpu);

	return msb << 8 | lsb;
}

void cpu_nmi(cpu_t* cpu)
{
	cpu_push_16(cpu, cpu->regs.pc + 1);
	cpu_push_8(cpu, cpu->regs.flags | FPUSHED);

	cpu->regs.pc = cpu->mem[0xFFFA] | (cpu->mem[0xFFFB] << 8);
}

void cpu_rst(cpu_t* cpu)
{
	cpu_push_16(cpu, cpu->regs.pc + 1);
	cpu_push_8(cpu, cpu->regs.flags | FPUSHED);

	cpu->regs.pc = cpu->mem[0xFFFC] | (cpu->mem[0xFFFD] << 8);
}

void cpu_brk(cpu_t* cpu)
{
	if(GET_FLAG(cpu, FNOBRK))
		return;

	cpu_push_16(cpu, cpu->regs.pc + 1);
	cpu_push_8(cpu, cpu->regs.flags | FPUSHED | FBRK);

	cpu->regs.pc = cpu->mem[0xFFFE] | (cpu->mem[0xFFFF] << 8);
}

