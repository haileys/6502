#include <cpu.h>
#include <instructions.h>

INS(brk)
{
	cpu_brk(cpu);
}
