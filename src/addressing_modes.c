#include <addressing_modes.h>
#include <vm.h>
#include <cpu.h>

ADDRMODE(implied)
{
	return 0;
}

ADDRMODE(imm8)
{
	return vm_next_8(cpu);
}

ADDRMODE(imm16)
{
	return vm_next_16(cpu);
}

ADDRMODE(relative)
{
	signed char offset = (signed char)vm_next_8(cpu);
	return cpu->regs.pc + offset;
}


