#include <stdlib.h>

int main(int argc, char **argv) {

  if (argc != 3) {
    printf("Error: Wrong number of arguments");
    return EXIT_FAILURE;
  }
  else {
    struct ARM proc;

    char const *const input_file  = argv[1];
    char const *const output_file = argv[2];

    // Initialise size of memory
    for (int i = 0; i < MAX_MEMORY_SIZE; i++) {
      proc.memory[i] = 0;
    }

    for (int i = 0; i < NUM_REGISTERS; i++) {
      proc.registers[i] = 0;
    }

    read_file(&proc, input_file);


  }
}
