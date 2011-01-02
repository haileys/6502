#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <string.h>

#include <cpu.h>
#include <vm.h>

int main(int argc, char** argv)
{
	if(argc < 3)
	{
		fprintf(stderr, "Usage: ./6502 <profile> <image>\n");
		return 1;
	}

	printf("** Loading image: %s... ", argv[2]);
	FILE* img = fopen(argv[2], "r");
	if(img == NULL)
	{
		printf("failed.\n");
		return 1;
	}

	cpu_t* cpu = new_cpu();
	fread(cpu->mem, 65536, 1, img);
	fclose(img);

	printf("ok.\n");

	printf("** Loading profile: %s.profile.so... ", argv[1]);
	char* profile_so = (char*)malloc(strlen(argv[1]) + 10);
	strcpy(profile_so, argv[1]);
	strcat(profile_so, ".profile.so");

	void* profile = dlopen(profile_so, RTLD_LAZY);
	if(profile == NULL)
	{
		printf("failed: %s\n", dlerror());
		return 1;
	}
	void(*init_6502)(cpu_t*) = dlsym("init_6502", profile);
	if(init_6502 == NULL)
	{
		printf("failed: could not initialize profile\n");
		return 1;
	}

	init_6502(cpu);

	while(1)
	{
		vm_step(cpu);
	}
}
