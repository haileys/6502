#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#include <cpu.h>
#include <vm.h>

#include <init_6502.h>

int send_rst = 0;

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

	while(1)
	{
		vm_step(cpu);

		if(send_rst)
		{
			// we can't call cpu_rst() directly from the signal handler, as a signal may fire mid-step.
			cpu_rst(cpu);
			send_rst = 0;
		}
	}
}
