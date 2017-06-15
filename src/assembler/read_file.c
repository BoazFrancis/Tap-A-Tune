#include "assemble.h"

/**
 * Count the number of lines in the input file
 * @param input - The pointer to the input file
 * @returns the number of the lines
 */
int count_lines(FILE *input) {
  char buff[LENGTH_OF_LINE];
  int count = 0;
  while(fgets(buff, LENGTH_OF_LINE, input) != NULL) {
    count++;
  }
  return count;
}

/**
 * Read the assembly file, and get each instruction one line at a time
 * @param input - The pointer to the input file
 * @param num_lines - The number of lines
 * @param instructions - The array of instructions
 * @returns the number of instructions
 */
int read_file(FILE *input, int num_lines, char **instructions) {

  for(int i=0; i<num_lines; i++) {
    instructions[i] = malloc(sizeof(char)*LENGTH_OF_LINE);
    if (instructions == NULL) {
      perror("Instructions malloc in assemble main");
      exit(EXIT_FAILURE);
    }
  }

  int j = 0;
  while (fgets(instructions[j], LENGTH_OF_LINE, input)) {
    instructions[j] = realloc(instructions[j], sizeof(char)*strlen(instructions[j]));
    if (instructions == NULL) {
      perror("Instructions calloc in assemble main");
      exit(EXIT_FAILURE);
    }
    j++;
  }



  // Close the file
  fclose(input);
  return j;

}
