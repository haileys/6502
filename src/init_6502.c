#include <init_6502.h>
#include <stdlib.h>
#include <stdio.h>

static void writeport_set(cpu_t* cpu, void*, unsigned short addr, unsigned char val);
static unsigned char writeport_get(cpu_t* cpu, void*, unsigned short addr);

static void readport_set(cpu_t* cpu, void*, unsigned short addr, unsigned char val);
static unsigned char readport_get(cpu_t* cpu, void*, unsigned short addr);

void init_6502(cpu_t* cpu)
{
	cpu->regs.pc = 0xC000;

	mmapseg_t mmap = {
		.address = 0xF001,
		.length = 1,
		.state = NULL,
		.set = writeport_set,
		.get = writeport_get,
	};
	cpu_mmap(cpu, &mmap);
	
	mmap.address = 0xF004;
	mmap.set = readport_set;
	mmap.get = readport_get;
	
	cpu_mmap(cpu, &mmap);
}

static void writeport_set(cpu_t* cpu, void* state, unsigned short addr, unsigned char val)
{
	putchar(val);
	fflush(stdout);
}
static unsigned char writeport_get(cpu_t* cpu, void* state, unsigned short addr)
{
	printf("** Read from write-only port $F001\n");
	printf("** CPU halted\n");
	exit(1);
}

static void readport_set(cpu_t* cpu, void* state, unsigned short addr, unsigned char val)
{
	printf("** Write to read-only port $F004\n");
	printf("** CPU halted\n");
	exit(1);
}
static unsigned char readport_get(cpu_t* cpu, void* state, unsigned short addr)
{
	return (unsigned char)getchar();
}
