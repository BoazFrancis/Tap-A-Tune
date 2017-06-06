#include "assemble.h"

/**
 * Append a 32 bit instruction to the binary file
 * @param line - The 32-bit line to write
 * @param output - A file pointer to the output file
 * @returns void
 */
void write_to_file(unsigned int line, FILE* output) {
  fwrite(&line, WORD_SIZE, 1, output);
}
