#include <stdio.h>
#include <stdlib.h>
#include "assemble.h"

//maybe not void
void tokenize(char* line) {
  // delimiter is a space
  const char delim[2] = " ";

  char* first_exp = strtok(line, delim);
  enum instruction_type inst = identifyInstruction(first_exp);

  switch (inst) {
    case DATA_PROCESSING:

    case MULTIPLY:
    case SINGLE_DATA_TRANSFER:
    case BRANCH:
    case SPECIAL:
    default:
    return;
  }


}
