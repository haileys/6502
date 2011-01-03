#include <cpu.h>
#include <instructions.h>

INS(brk)
{
	cpu_brk(cpu);
}

INS(lda)
{
	cpu->regs.a = param & 255;

	FLAG_IF(cpu, FZERO, cpu->regs.a == 0);
	FLAG_IF(cpu, FNEG, cpu->regs.a & 128);
}

INS(ldx)
{
	cpu->regs.x = param & 255;

	FLAG_IF(cpu, FZERO, cpu->regs.x == 0);
	FLAG_IF(cpu, FNEG, cpu->regs.x & 128);
}

INS(rti)
{
	cpu->regs.flags = cpu_pop_8(cpu);
	cpu->regs.pc = cpu_pop_16(cpu);
}
