#include "map.h"
#include "../defs.h"

void read_file(char* path, char** instructions);
void build_symbol_table(char** instructions, SymbolTable* st);
