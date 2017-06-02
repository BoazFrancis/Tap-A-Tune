#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "assemble.h"

void read_file(char* path, char** instructions) {

  // Open the input file
  FILE* input = fopen(path, "r");

  for(int i=0; i<100; i++) {
    instructions[i] = malloc(sizeof(char)*511);
  }

  int j = 0;
  while (fgets(instructions[j], 511, input)) {
    j++;
  }

  // Close the file
  fclose(input);

}
