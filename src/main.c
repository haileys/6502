#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <cpu.h>
#include <vm.h>

#include <init_6502.h>

int main(int argc, char** argv)
{
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

	while(1)
	{
		vm_step(cpu);
	}
}
