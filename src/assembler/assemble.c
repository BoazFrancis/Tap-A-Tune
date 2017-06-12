#include "assemble.h"

/**
 * Assemble an ARM assembly program into a binary file
 * @param argc - The number of arguments passed
 * @param argv - An array of string arguments
 * @returns 0 on no errors
 */
int main(int argc, char **argv) {

  if (argc != 3) {
    printf("Error: Wrong number of arguments");
  }
  else {

    char *input_file  = argv[1];
    char *output_file = argv[2];

    // Open the input file
    FILE *input = fopen(input_file, "r+");
    int input_lines = count_lines(input);
    rewind(input);

    // Clear file and then open it for appending
    FILE *output = fopen(output_file, "wb");
    output = freopen(output_file, "ab", output);

    char** instructions = malloc(sizeof(char*) * input_lines);

    if (instructions == NULL) {
      perror("Instructions malloc in assemble main");
      exit(EXIT_FAILURE);
    }

    int total_size = read_file(input, input_lines, instructions);

    // Build the symbol table
    SymbolTable st;
    st.size = 0;

    // Create label pointer
    char* label = NULL;

    // Returns the number of actual instructions
    // i.e. every instruction except a jump label
    int num_no_labels = build_symbol_table(total_size, instructions, &st, label);

    // Process all these instructions
    process_instructions(total_size, &num_no_labels, instructions, output, &st);

    fclose(output);
    // Free the memory of all instructions
    for (int i = 0; i < input_lines; i++) {
      free(instructions[i]);
    }
    free(instructions);
    for (int i = 0; i < (total_size - num_no_labels); i++) {
      free(st.table[i].label);
    }

    return 0;

  }

}
