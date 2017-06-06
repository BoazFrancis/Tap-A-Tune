// Define the Map object to have a string label and int address
typedef struct {
   char* label;
   int address;
} Map;

// A symbol table is an array of Maps
typedef struct {
   Map table[100];
   int size;
} SymbolTable;

// Map utility functions
int get_address(SymbolTable* st, char* label);
void add_label(SymbolTable* st, char* label, int address);
