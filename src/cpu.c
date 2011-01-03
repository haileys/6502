#include <stdlib.h>
#include <string.h>

#include <cpu.h>

cpu_t* new_cpu()
{
	cpu_t* cpu = (cpu_t*)calloc(1, sizeof(cpu_t));
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
	cpu_poke(cpu, 256 + cpu->regs.sp, val);
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
	return cpu_peek(cpu, 256 + cpu->regs.sp);
}
unsigned short cpu_pop_16(cpu_t* cpu)
{
	unsigned char lsb = cpu_pop_8(cpu);
	unsigned char msb = cpu_pop_8(cpu);

	return msb << 8 | lsb;
}

void cpu_nmi(cpu_t* cpu)
{
	cpu_push_16(cpu, cpu->regs.pc);
	cpu_push_8(cpu, cpu->regs.flags | FPUSHED);

	cpu->regs.pc = cpu_peek(cpu, 0xFFFA) | (cpu_peek(cpu, 0xFFFB) << 8);
}

void cpu_rst(cpu_t* cpu)
{
	cpu_push_16(cpu, cpu->regs.pc);
	cpu_push_8(cpu, cpu->regs.flags | FPUSHED);

	cpu->regs.pc = cpu_peek(cpu, 0xFFFC) | (cpu_peek(cpu, 0xFFFD) << 8);
}

void cpu_brk(cpu_t* cpu)
{
	if(GET_FLAG(cpu, FNOBRK))
		return;

	cpu_push_16(cpu, cpu->regs.pc);
	cpu_push_8(cpu, cpu->regs.flags | FPUSHED | FBRK);

	cpu->regs.pc = cpu_peek(cpu, 0xFFFE) | (cpu_peek(cpu, 0xFFFF) << 8);
}

void cpu_mmap(cpu_t* cpu, mmapseg_t* segment)
{
	mmapseg_t* new_segment = (mmapseg_t*)malloc(sizeof(mmapseg_t));
	memcpy(new_segment, segment, sizeof(mmapseg_t));

	new_segment->next = NULL;
	if(cpu->mmapped_chain_tail != NULL)
		cpu->mmapped_chain_tail->next = new_segment;
	cpu->mmapped_chain_tail = new_segment;
}

unsigned char cpu_peek(cpu_t* cpu, unsigned short address)
{
	for(mmapseg_t* node = cpu->mmapped_chain_head; node != NULL; node = node->next)
	{
		if(node->address <= address && node->address + node->length > address)
		{
			return node->get(cpu, node->state, address);
		}
	}

	return cpu->mem[address];
}

void cpu_poke(cpu_t* cpu, unsigned short address, unsigned char val)
{
	for(mmapseg_t* node = cpu->mmapped_chain_head; node != NULL; node = node->next)
	{
		if(node->address <= address && node->address + node->length > address)
		{
			node->set(cpu, node->state, address, val);
			return;
		}
	}

	cpu->mem[address] = val;
}

unsigned short cpu_peek_16(cpu_t* cpu, unsigned short address)
{
	unsigned char lsb = cpu_peek(cpu, address);
	unsigned char msb = cpu_peek(cpu, address + 1);

	return msb << 8 | lsb;
}

void cpu_poke_16(cpu_t* cpu, unsigned short address, unsigned short val)
{
	cpu_poke(cpu, address, val & 255);
	cpu_poke(cpu, address + 1, val >> 8);
}

