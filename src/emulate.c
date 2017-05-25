#include <stdio.h>
#include <stdlib.h>

// Definitions - need to go in .h file
void read_binary_file(int* m, char* path);
void fetch_decode_execute(int* m);

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

  // Print out memory (for testing only)
  for (int i=0; i<sizeof(memory)/sizeof(int); i++) {
    printf("%x\n", memory[i]);
  }

  fetch_decode_execute(memory);

  return 0;

}

void read_binary_file(int* m, char* path) {
  
  // Open the input file
  FILE* input = fopen(path, "rb");

  // Reading the input file
  int pos = 0;
  int read_success = 0;

  // Keep reading bytes into memory until nothing left to read
  do {
    read_success = fread(&m[pos], sizeof(int), 1, input);
    pos++;
  }
  while (read_success != 0);

  // Close the file
  fclose(input);

}

void fetch_decode_execute(int* m) {
  
  int pc = 0;
  int ir = 0;

  do {
    
    ir = m[pc];
    pc++;

    // Need to check the "Cond" part of the instruction,
    // first 4 bits on page 4

    /*
      switch (get_instruction_type(&ir)) {
        
        case DATA_PROCESSING:
        data_processing(&ir);
        break;

        case BRANCH:
        branch(&ir);
        break;

        case MULTIPLY:
        multiply(&ir);
        break;

        case SINGLE_DATA_TRANSFER:
        single_data_transfer(&ir);
        break;
      }

    */

  }
  while (ir != 0);

}