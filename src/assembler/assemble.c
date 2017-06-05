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

    // Clear file and then open it for appending
    FILE* output = fopen(output_file, "wb");
    output = freopen(output_file, "ab", output);

    char** instructions = malloc(sizeof(char*)*100);
    int total_size = read_file(input_file, instructions);

    // Build the symbol table
    SymbolTable st;
    st.size = 0;

    int num_no_labels = build_symbol_table(total_size, instructions, &st);
    process_instructions(total_size, &num_no_labels, instructions, output, &st);

    fclose(output);

    return 0;

  }

}
