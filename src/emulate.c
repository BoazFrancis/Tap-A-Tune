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
  for (int i = 0; i < MAX_MEMORY_SIZE; i++) {
    proc.memory[i] = 0;
  }

  for (int i = 0; i < NUM_REGISTERS; i++) {
    proc.registers[i] = 0;
  }

  read_binary_file(proc.memory, argv[1]);

  // Print out memory (for testing only)
  for (int i=0; i<sizeof(proc.memory)/sizeof(int); i++) {
    printf("%x\n", proc.memory[i]);
  }
  printf("%i", arithmeticShiftRight(-10, 5));
  fetch_decode_execute(proc);

  return 0;

}
