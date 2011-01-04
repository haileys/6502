#include <cpu.h>
#include <instructions.h>
#include <stdio.h>
#include <stdlib.h>

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

INS(ldy)
{
	cpu->regs.y = param & 255;

	FLAG_IF(cpu, FZERO, cpu->regs.y == 0);
	FLAG_IF(cpu, FNEG, cpu->regs.y & 128);
}

INS(rti)
{
	cpu->regs.flags = cpu_pop_8(cpu);
	cpu->regs.pc = cpu_pop_16(cpu);
}

INS(jmp)
{
	cpu->regs.pc = param;
}

INS(beq)
{
	if(GET_FLAG(cpu, FZERO))
		cpu->regs.pc = param;
}

INS(bne)
{
	if(!GET_FLAG(cpu, FZERO))
		cpu->regs.pc = param;
}

INS(bcc)
{
	if(!GET_FLAG(cpu, FCARRY))
		cpu->regs.pc = param;
}

INS(bcs)
{
	if(GET_FLAG(cpu, FCARRY))
		cpu->regs.pc = param;
}

INS(bmi)
{
	if(GET_FLAG(cpu, FNEG))
		cpu->regs.pc = param;
}

INS(bpl)
{
	if(!GET_FLAG(cpu, FNEG))
		cpu->regs.pc = param;
}

INS(sta)
{
	cpu_poke(cpu, param, cpu->regs.a);
}

INS(sty)
{
	cpu_poke(cpu, param, cpu->regs.y);
}

INS(stx)
{
	cpu_poke(cpu, param, cpu->regs.x);
}

INS(dex)
{
	cpu->regs.x--;

	FLAG_IF(cpu, FZERO, cpu->regs.x == 0);
	FLAG_IF(cpu, FNEG, cpu->regs.x & 128);	
}

INS(dey)
{
	cpu->regs.y--;

	FLAG_IF(cpu, FZERO, cpu->regs.y == 0);
	FLAG_IF(cpu, FNEG, cpu->regs.y & 128);	
}

INS(inx)
{
	cpu->regs.x++;

	FLAG_IF(cpu, FZERO, cpu->regs.x == 0);
	FLAG_IF(cpu, FNEG, cpu->regs.x & 128);	
}

INS(iny)
{
	cpu->regs.y++;

	FLAG_IF(cpu, FZERO, cpu->regs.y == 0);
	FLAG_IF(cpu, FNEG, cpu->regs.y & 128);	
}

INS(inc)
{
	unsigned char n = cpu_peek(cpu, param) + 1;
	cpu_poke(cpu, param, n);	

	FLAG_IF(cpu, FZERO, n == 0);
	FLAG_IF(cpu, FNEG, n & 128);	
}

INS(txa)
{
	cpu->regs.a = cpu->regs.x;

	FLAG_IF(cpu, FZERO, cpu->regs.a == 0);
	FLAG_IF(cpu, FNEG, cpu->regs.a & 128);	
}

INS(tax)
{
	cpu->regs.x = cpu->regs.a;

	FLAG_IF(cpu, FZERO, cpu->regs.x == 0);
	FLAG_IF(cpu, FNEG, cpu->regs.x & 128);	
}

INS(txs)
{
	cpu->regs.sp = cpu->regs.x;
}

INS(tya)
{
	cpu->regs.a = cpu->regs.y;
}

INS(tay)
{
	cpu->regs.y = cpu->regs.a;
}

INS(and)
{
	cpu->regs.a = cpu->regs.a & param;

	FLAG_IF(cpu, FZERO, cpu->regs.a == 0);
	FLAG_IF(cpu, FNEG, cpu->regs.a & 128);	
}

INS(cmp)
{
	FLAG_IF(cpu, FCARRY, cpu->regs.a >= param);
	FLAG_IF(cpu, FZERO, cpu->regs.a == param);
	FLAG_IF(cpu, FNEG, cpu->regs.a & 128);	
}

INS(cpx)
{
	FLAG_IF(cpu, FCARRY, cpu->regs.x >= param);
	FLAG_IF(cpu, FZERO, cpu->regs.x == param);
	FLAG_IF(cpu, FNEG, cpu->regs.x & 128);	
}

INS(cpy)
{
	FLAG_IF(cpu, FCARRY, cpu->regs.y >= param);
	FLAG_IF(cpu, FZERO, cpu->regs.y == param);
	FLAG_IF(cpu, FNEG, cpu->regs.y & 128);	
}

INS(nop)
{
}

INS(adc)
{		
	if(!GET_FLAG(cpu, FBCD))
	{
		unsigned short total = cpu->regs.a + param + (GET_FLAG(cpu, FCARRY) ? 1 : 0);

		CLEAR_FLAG(cpu, FCARRY);
		CLEAR_FLAG(cpu, FOFLOW);
		CLEAR_FLAG(cpu, FNEG);
		CLEAR_FLAG(cpu, FZERO);

		if(total > 255)
		{
			SET_FLAG(cpu, FOFLOW);
			SET_FLAG(cpu, FCARRY);

			total &= 255;
		}

		if(total == 0)
			SET_FLAG(cpu, FZERO);
			
		if(total & 128)
			SET_FLAG(cpu, FNEG);

		cpu->regs.a = (unsigned char)total;
	}
	else
	{
		fprintf(stderr, "bcd adc!\n");
		exit(1);
	}
}

INS(sbc)
{
		
	if(!GET_FLAG(cpu, FBCD))
	{
		unsigned short total = cpu->regs.a - param - (GET_FLAG(cpu, FCARRY) ? 0 : 1);

		CLEAR_FLAG(cpu, FCARRY);
		CLEAR_FLAG(cpu, FOFLOW);
		CLEAR_FLAG(cpu, FNEG);
		CLEAR_FLAG(cpu, FZERO);

		if(total == 0)
		{
			SET_FLAG(cpu, FZERO);
			SET_FLAG(cpu, FCARRY);
		}
		else if(total > 0)
			SET_FLAG(cpu, FCARRY);
		else
			SET_FLAG(cpu, FOFLOW);

		if(total & 128)
			SET_FLAG(cpu, FNEG);

		cpu->regs.a = total & 255;
	}
	else
	{
		fprintf(stderr, "bcd sbc! Flags: %x  BCD Flag is %x\n", cpu->regs.flags, FBCD);
		exit(1);
	}
}

INS(jsr)
{
	cpu_push_16(cpu, cpu->regs.pc - 1);
	cpu->regs.pc = param;
}

INS(rts)
{
	cpu->regs.pc = cpu_pop_16(cpu) + 1;
}

INS(cld)
{
	CLEAR_FLAG(cpu, FBCD);
}

INS(clc)
{
	CLEAR_FLAG(cpu, FCARRY);
}

INS(sec)
{
	SET_FLAG(cpu, FCARRY);
}

INS(php)
{
	cpu_push_8(cpu, cpu->regs.flags | FPUSHED);
}

INS(pha)
{
	cpu_push_8(cpu, cpu->regs.a);
}

INS(pla)
{
	cpu->regs.a = cpu_pop_8(cpu);
}

INS(plp)
{
	cpu->regs.flags = cpu_pop_8(cpu);
}

INS(bit)
{
	unsigned char result = cpu->regs.a & param;

	FLAG_IF(cpu, FZERO, result == 0);
	FLAG_IF(cpu, FOFLOW, result & 64);
	FLAG_IF(cpu, FNEG, result & 128);
}

INS(lsr_a)
{
	FLAG_IF(cpu, FCARRY, cpu->regs.a & 1);
	cpu->regs.a >>= 1;
}

INS(lsr)
{
	unsigned char val = cpu_peek(cpu, param);
	FLAG_IF(cpu, FCARRY, val & 1);
	val >>= 1;
	cpu_poke(cpu, param, val);
}

INS(eor)
{
	
}


