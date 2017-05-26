#include <stdio.h>
#include "emulate.h"

void read_binary_file(int* memory, char* path) {

  // Open the input file
  FILE* input = fopen(path, "rb");

  // Reading the input file
  int pos = 0;
  int read_success = -1;

  // Keep reading bytes into memory until nothing left to read
  while (read_success != 0) {
    read_success = fread(&memory[pos], sizeof(int), 1, input);
    pos++;
  }

  // Close the file
  fclose(input);

}
