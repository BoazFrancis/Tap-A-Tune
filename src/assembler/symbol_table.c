#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assemble.h"

void build_symbol_table(char** instructions, SymbolTable* st) {

  for (int i=0; i<100; i++) {

    char* token;
    const char space[1] = " ";

    char *rest = instructions[i];

    while (token = strtok_r(rest, space, &rest)) {

      // Find the label by splitting at ':'
      char* pos = strchr(token, ':');

      if (pos != NULL) {

        int index = pos - token;
        printf("%d\n", index);
        char* label = malloc(index+1);
        strncpy(label, token, index);
        label[index] = '\0';

        // Found a label, store in symbol table
        int address = i * WORD_SIZE;
        printf("%s\n", label);
        add_label(st, label, address);

      }

    }

  }

}
