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
    SymbolTable st;
    st.size = 0;

    build_symbol_table(instructions, &st);

    return 0;

  }

}
