#include "defs.h"

// Create the ARM struct
struct ARM {
   int memory[MAX_MEMORY_SIZE];
   int registers[NUM_REGISTERS];
   int pc;
   int ir;
};

// Reading binary files
void read_binary_file(int* memory, char* path);

// Bit-utils
int extract_bits(int* n, int start, int length);
int extract_bit(int* n, int start);

// Fetch-execute cycle
void fetch_decode_execute(struct ARM proc);
int check_condition_bits(struct ARM proc);
