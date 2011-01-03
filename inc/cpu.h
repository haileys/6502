#ifndef CPU_H
#define CPU_H

#define FCARRY	1
#define FZERO	2
#define FNOBRK	4
#define FBCD	8
#define FBRK	16
#define FPUSHED	32
#define FOFLOW	64
#define FNEG	128

#define GET_FLAG(state,flag)	((state)->regs.flags & (flag))
#define SET_FLAG(state,flag)	(state)->regs.flags |= (flag)
#define CLEAR_FLAG(state,flag)	(state)->regs.flags &= ~(flag);

#define FLAG_IF(state,flag,condition) if(condition) { SET_FLAG(state,flag); } else { CLEAR_FLAG(state,flag); }

typedef struct reg
{
	unsigned short pc;
	unsigned char sp;
	unsigned char a;
	unsigned char x;
	unsigned char y;
	unsigned char flags;
	
} reg_t;

struct mmapseg;

typedef struct cpu
{
	unsigned char* mem;
	reg_t regs;
	
	struct mmapseg* mmapped_chain_head;
	struct mmapseg* mmapped_chain_tail;
	
} cpu_t;

typedef struct mmapseg
{
	unsigned short address;
	unsigned short length;

	void* state;

	unsigned char(*get)(cpu_t*, void*, unsigned short);
	void(*set)(cpu_t*, void*, unsigned short, unsigned char);

	struct mmapseg* next;
	
} mmapseg_t;

cpu_t*	new_cpu();
void	free_cpu(cpu_t* cpu);

void			cpu_push_8(cpu_t* cpu, unsigned char val);
void			cpu_push_16(cpu_t* cpu, unsigned short val);

unsigned char	cpu_pop_8(cpu_t* cpu);
unsigned short	cpu_pop_16(cpu_t* cpu);

void			cpu_nmi(cpu_t* cpu);
void			cpu_rst(cpu_t* cpu);
void			cpu_brk(cpu_t* cpu);

void			cpu_mmap(cpu_t* cpu, mmapseg_t* segment);

unsigned char	cpu_peek(cpu_t* cpu, unsigned short address);
void			cpu_poke(cpu_t* cpu, unsigned short address, unsigned char val);

unsigned short	cpu_peek_16(cpu_t* cpu, unsigned short address);
void			cpu_poke_16(cpu_t* cpu, unsigned short address, unsigned short val);

#endif
