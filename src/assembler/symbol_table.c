#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assemble.h"

void build_symbol_table(char** instructions, SymbolTable* st) {

  for (int i=0; i<100; i++) {

    char* tokens;
    const char space[1] = " ";

    tokens = strtok(instructions[i], space);

    while (tokens != NULL) {

      // Find the label by splitting at ':'
      char* pos = strchr(tokens, ':');

      if (pos != NULL) {

        int index = pos - tokens;
        printf("%d\n", index);
        char* label = malloc(index+1);
        strncpy(label, tokens, index);
        label[index] = '\0';

        // Found a label, store in symbol table
        int address = i * WORD_SIZE;
        printf("%s\n", label);
        add_label(st, label, address);

      }

      // Continue to next token
      tokens = strtok(NULL, space);

    }

  }

}
