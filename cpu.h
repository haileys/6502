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

typedef struct reg
{
	unsigned short pc;
	unsigned char sp;
	unsigned char a;
	unsigned char x;
	unsigned char y;
	unsigned char flags;
	
} reg_t;

typedef struct cpu
{
	unsigned char* mem;
	reg_t regs;
	
} cpu_t;

cpu_t*	new_cpu();
void	free_cpu(cpu_t* cpu);

void			cpu_push_8(cpu_t* cpu, unsigned char val);
void			cpu_push_16(cpu_t* cpu, unsigned short val);

unsigned char	cpu_pop_8(cpu_t* cpu);
unsigned short	cpu_pop_16(cpu_t* cpu);

void			cpu_nmi(cpu_t* cpu);
void			cpu_rst(cpu_t* cpu);
void			cpu_brk(cpu_t* cpu);

#endif
