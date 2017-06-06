#include "assemble.h"

/**
 * Count the number of lines in the input file
 * @param input - The pointer to the input file
 * @returns the number of the lines
 */
int count_lines(FILE* input) {
  int ch = 0;
  int lines = 0;
  while (!feof(input)) {
    ch = fgetc(input);
    if (ch == '\n') {
      lines++;
    }
  }
  return lines;
}

/**
 * Read the assembly file, and get each instruction one line at a time
 * @param input - The pointer to the input file
 * @param num_lines - The number of lines
 * @param instructions - The array of instructions
 * @returns the number of instructions
 */
int read_file(FILE* input, int num_lines, char** instructions) {

  for(int i=0; i<num_lines; i++) {
    instructions[i] = malloc(sizeof(char)*511);
  }

  int j = 0;
  while (fgets(instructions[j], 511, input)) {
    j++;
  }

  // Close the file
  fclose(input);

  return j;

}
