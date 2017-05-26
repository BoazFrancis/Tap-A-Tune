#include <stdio.h>
#include <stdlib.h>
#include "emulate.h"

int main(int argc, char** argv) {

  // Check for correct number of arguments
  if (argc != 2) {
    printf("No file provided\n");
    return EXIT_FAILURE;
  }

  struct ARM proc;

  // Initialise size of memory
  for (int i = 0; i < max_memory_size; i++) {
    proc.memory[i] = 0;
  }

  for (int i = 0; i < number_of_registers; i++) {
    proc.registers[i] = 0;
  }

  read_binary_file(proc.memory, argv[1]);

  // Print out memory (for testing only)
  for (int i=0; i<sizeof(proc.memory)/sizeof(int); i++) {
    printf("%x\n", proc.memory[i]);
  }

  fetch_decode_execute(proc);

  return 0;

}
