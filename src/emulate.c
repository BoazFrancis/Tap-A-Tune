#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  // Get filename from command line
  char* name = argv[1];

  FILE *file;
	unsigned char *buffer;
	unsigned long fileLen;

	//Open file
	file = fopen(name, "rb");
	if (!file) {
		fprintf(stderr, "Unable to open file %s", name);
		return 0;
	}

	//Get file length
	fseek(file, 0, SEEK_END);
	fileLen = ftell(file);
	fseek(file, 0, SEEK_SET);

	// Allocate memory
	buffer = (unsigned char *)malloc(fileLen);
	if (!buffer) {
		fprintf(stderr, "Memory error!");
    fclose(file);
		return 0;
	}

	// Read file contents into buffer
  int memory_size = 4;

  for (int i=0; i<fileLen/memory_size; i++) {
    fread(buffer, memory_size, 1, file);
    for (int j=0; j<memory_size; j++) {
      printf("%02x", buffer[j]);
    }
    printf("\n");
  }

	fclose(file);

	free(buffer);

  return 0;

}

/*
Building a binary file loader.
Writing the emulator loop, comprising:
– Simulation of the ARM pipeline, with an execute, decode, fetch cycle.
– Simulated execution of the four types of instruction (data processing, multiply, single data
transfer, branch) given above. Note that there are no opcodes for the different instruction
types, so you will have to find a pattern to distinguish between instructions.
– The emulator should terminate when it executes an all-0 instruction.
– Upon termination, output the state of the registers.
*/
