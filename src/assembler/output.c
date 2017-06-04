#include <stdio.h>
#include <string.h>
#include "assemble.h"

void write_to_file(unsigned int line, FILE* output) {
  fwrite(&line, WORD_SIZE, 1, output);
}
