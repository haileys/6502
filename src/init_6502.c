#include <init_6502.h>
#include <stdlib.h>
#include <stdio.h>

static void f000_set(cpu_t* cpu, void*, unsigned short addr, unsigned char val);
static unsigned char f000_get(cpu_t* cpu, void*, unsigned short addr);

void init_6502(cpu_t* cpu)
{
	cpu->regs.pc = 0xC000;

	mmapseg_t mmap = {
		.address = 0xF000,
		.length = 0x1000,
		.state = cpu->mem,
		.set = f000_set,
		.get = f000_get,
	};
	cpu_mmap(cpu, &mmap);
}

static void f000_set(cpu_t* cpu, void* state, unsigned short addr, unsigned char val)
{
	printf("write: addr %x value %x\n", addr, val);
	((unsigned char*)state)[addr] = val;
}
static unsigned char f000_get(cpu_t* cpu, void* state, unsigned short addr)
{
	printf(" read: addr %x value %x\n", addr, ((unsigned char*)state)[addr]);
	return ((unsigned char*)state)[addr];
}
