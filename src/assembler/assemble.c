#include <stdio.h>
#include <stdlib.h>
#include "assemble.h"

int main(int argc, char **argv) {

  if (argc != 3) {
    printf("Error: Wrong number of arguments");
  }
  else {

    char* input_file  = argv[1];
    char* output_file = argv[2];

    char** instructions = malloc(sizeof(char*)*100);
    read_file(input_file, instructions);

    // Build the symbol table
    build_symbol_table(instructions);

    process_instructions(instructions);

    return 0;

  }

}
