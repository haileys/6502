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

ADDRMODE(imm16) // also works for jmp's absolute addressing
{
	return vm_next_16(cpu);
}

ADDRMODE(relative)
{
	signed char offset = (signed char)vm_next_8(cpu);
	return cpu->regs.pc + offset;
}

ADDRMODE(abs)
{
	return vm_next_16(cpu);
}

ADDRMODE(abs_deref)
{
	return cpu_peek(cpu, vm_next_16(cpu));
}

ADDRMODE(absx)
{
	return vm_next_16(cpu) + cpu->regs.x;
}

ADDRMODE(absx_deref)
{
	return cpu_peek(cpu, vm_next_16(cpu) + cpu->regs.x);
}

ADDRMODE(absy)
{
	return vm_next_16(cpu) + cpu->regs.y;
}

ADDRMODE(absy_deref)
{
	return cpu_peek(cpu, vm_next_16(cpu) + cpu->regs.y);
}

ADDRMODE(zp)
{
	return vm_next_8(cpu);
}

ADDRMODE(zp_deref)
{
	return cpu_peek(cpu, vm_next_8(cpu));
}

ADDRMODE(zpx)
{
	return (vm_next_8(cpu) + (cpu->regs.x & 255)) & 255;
}

ADDRMODE(zpx_deref)
{
	return cpu_peek(cpu, (vm_next_8(cpu) + (cpu->regs.x & 255)) & 255);
}

ADDRMODE(indirect)
{
	return cpu_peek_16(cpu, vm_next_16(cpu));
}

ADDRMODE(indy)
{
	return cpu_peek_16(cpu, vm_next_8(cpu)) + cpu->regs.y;
}

ADDRMODE(indy_deref)
{
	return cpu_peek(cpu, cpu_peek_16(cpu, vm_next_8(cpu)) + cpu->regs.y);
}

ADDRMODE(indx)
{
	return cpu_peek_16(cpu, vm_next_8(cpu) + cpu->regs.x);
}

ADDRMODE(indx_deref)
{
	return cpu_peek(cpu, cpu_peek_16(cpu, vm_next_8(cpu) + cpu->regs.x));
}

