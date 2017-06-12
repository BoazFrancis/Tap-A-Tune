#include "emulate.h"

/**
 * Simulate the running of the emulator
 * @param argc - The number of arguments passed
 * @param argv - An array of string arguments
 * @returns 0 on no errors
 */
int main(int argc, char **argv) {

  // Check for correct number of arguments
  if (argc != 2) {
    printf("No file provided\n");
    return EXIT_FAILURE;
  }

  // Create the processor as type ARM
  struct ARM proc;

  // Initialise size of memory and registers
  for (int i = 0; i < MAX_MEMORY_SIZE; i++) {
    proc.memory[i] = 0;
  }

  for (int i = 0; i < NUM_REGISTERS; i++) {
    proc.registers[i] = 0;
  }

  // Read the file
  read_binary_file(&proc, argv[1]);

  // Process all the instructions
  fetch_decode_execute(&proc);

  // Print the registers
  print_registers(&proc);

  // Print the non-zero memory
  print_nonzeromemory(&proc);

  return 0;

}
