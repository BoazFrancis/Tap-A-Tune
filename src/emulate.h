#include "defs.h"

// Create the ARM struct
struct ARM {
   int memory[MAX_MEMORY_SIZE];
   int registers[NUM_REGISTERS];
   int pc;
   int ir;
};

// Reading binary files
void read_binary_file(struct ARM* proc, char* path);

// Bit-utils
int extract_bits(int* n, int start, int length);
int extract_bit(int* n, int start);
int is_bit_set(int* n, int bit);
unsigned int binary_to_decimal(unsigned int bin);
unsigned int base_to_base(int from, int to, unsigned int n);
signed int sign_extension(signed int n, int sbits, int ebits);

// Type of instruction
enum instruction_type {
  DATA_PROCESSING,
  MULTIPLY,
  SINGLE_DATA_TRANSFER,
  BRANCH
};

// Fetch-execute cycle
void fetch_decode_execute(struct ARM* proc);
int check_condition_bits(struct ARM* proc);
enum instruction_type get_instruction_type(int* ir);

// Data processing instructions
void data_processing(struct ARM* proc);

// Mutliply instructions
void multiply(struct ARM* proc);
void multiply_with_accumulate(struct ARM* proc, unsigned int d, unsigned int m, unsigned int s, unsigned int n);
void multiply_regular(struct ARM* proc, unsigned int d, unsigned int m, unsigned int s);

// Single data transfer instructions
void single_data_transfer(struct ARM* proc);

// Branch instructions
void branch(struct ARM* proc);
