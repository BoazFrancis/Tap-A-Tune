#include <stdio.h>
#include <stdlib.h>

void read_binary_file(int* mem, char* path);

int main(int argc, char** argv) {

  // Check for correct number of arguments
	if (argc != 2) {
		printf("No file provided\n");
		return EXIT_FAILURE;
	}

  // Memory store
  int max_memory_size = (1 << 4);
  int memory[max_memory_size];

  // Initialise size of memory
  for (int i = 0; i < max_memory_size; i++) {
		memory[i] = 0;
	}

  read_binary_file(memory, argv[1]);

  // Print out file
  for (int i=0; i<sizeof(memory)/sizeof(int); i++) {
    printf("%x\n", memory[i]);
  }

  return 0;

}

void read_binary_file(int* mem, char* path) {
	
  // Open the input file
	FILE* input = fopen(path, "rb");

	// Reading the input file
	int pos = 0;
  int read_success = 0;

	// Keep reading bytes into memory until nothing left to read
  do {
		read_success = fread(&mem[pos], sizeof(int), 1, input);
		pos++;
	}
  while (read_success != 0);

  // Close the file
	fclose(input);

}