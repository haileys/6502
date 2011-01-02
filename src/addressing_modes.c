#include <addressing_modes.h>
#include <vm.h>
#include <cpu.h>

ADDRMODE(none)
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
