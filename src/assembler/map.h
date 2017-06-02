#include "../defs.h"

typedef struct {
   char* label;
   int address;
} Map;

typedef struct {
   Map table[100];
   int size;
} SymbolTable;

int get_address(SymbolTable* st, char* label);
void add_label(SymbolTable* st, char* label, int address);
