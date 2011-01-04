#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <termios.h>

#include <cpu.h>
#include <vm.h>
#include <init_6502.h>

int send_rst = 0;
int debug_mode = 0;

void sigint_handler(int n)
{
	send_rst = 1;
}

int main(int argc, char** argv)
{	
	printf("\em");

	if(argc < 2)
	{
		fprintf(stderr, "Usage: ./6502 <image>\n");
		return 1;
	}

	if(argc > 2 && strcmp(argv[2], "-debug") == 0)
		debug_mode = 1;

	printf("** Loading image: %s... ", argv[1]);
	FILE* img = fopen(argv[1], "r");
	if(img == NULL)
	{
		printf("failed.\n");
		return 1;
	}

	cpu_t* cpu = new_cpu();
	fread(cpu->mem, 65536, 1, img);
	fclose(img);

	printf("ok.\n");
	
	init_6502(cpu);

	signal(SIGINT, sigint_handler);

	// unbuffer stdin
	struct termios attr;
	tcgetattr(0, &attr);
	attr.c_lflag &= ~ICANON;
	attr.c_lflag &= ~ECHO;
	tcsetattr(0, TCSANOW, &attr);

	while(1)
	{
		vm_step(cpu);

		if(send_rst)
		{
			// we can't call cpu_rst() directly from the signal handler, as a signal may fire mid-step.
			cpu_rst(cpu);
			send_rst = 0;
		}

		if(debug_mode)
		{
			reg_t* r = &cpu->regs;
		
			printf(
			// push current cursor position, and go to (1,1)
			"\e[s\e[1;1H"
			// white on red
			"\e[1;37;41m"
			// print out status info, like registers
			" A: %02x  X: %02x  Y: %02x  PC: $%04x  SP: %02x  Flags: %x"
			// restore colour and pop cursor
			"\e[m\e[u", r->a & 255, r->x & 255, r->y & 255, r->pc & 65535, r->sp & 255, r->flags & 255);
		}
	}
}
