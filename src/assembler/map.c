#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assemble.h"

/**
 * Lookup the label in the symbol table and returns its address
 * @param st - The pointer to the symbol table
 * @param label - The label to find
 * @returns the address
 */
int get_address(SymbolTable* st, char* label) {
  for (int i=0; i<st->size; i++) {
    if (strcmp(st->table[i].label, label) == 0) {
      return st->table[i].address;
    }
  }
}


/**
 * Adds a label and address to the symbol table
 * @param st - A pointer to the symbol table
 * @param label - The new label to add
 * @param address - The address in memory
 * @returns void
 */
void add_label(SymbolTable* st, char* label, int address) {
  Map m;
  m.label = label;
  m.address = address;
  st->table[st->size] = m;
  st->size++;
}
