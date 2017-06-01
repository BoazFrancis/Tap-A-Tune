#include <stdio.h>
#include "emulate.h"

/**
 * Reads the file into memory
 * @param proc - The pointer to the ARM processor
 * @param path - The string of the filename
 * @returns void
*/
void read_file(struct ARM* proc, char* path) {

  // Open the input file
  FILE* input = fopen(path, "r");

  // Reading the input file
  int pos = 0;
  int read_success = -1;

  // Keep reading bytes into memory until nothing left to read
  while (read_success != 0) {
    read_success = fread(&proc->memory[pos], sizeof(int), 1, input);
    pos++;
  }

  // Close the file
  fclose(input);

}
