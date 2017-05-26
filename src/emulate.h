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
int is_bit_set(int* n, int bit);
unsigned int binary_to_decimal(unsigned int bin);
unsigned int base_to_base(int from, int to, unsigned int n);
unsigned int rotate_left(const unsigned int val, int shiftBy);
unsigned int rotate_right(const unsigned int val, int shiftBy);


// Type of instruction
enum instruction_type {
  DATA_PROCESSING,
  MULTIPLY,
  SINGLE_DATA_TRANSFER,
  BRANCH
};

// Fetch-execute cycle
void fetch_decode_execute(struct ARM proc);
int check_condition_bits(struct ARM proc);
enum instruction_type get_instruction_type(int* ir);

// Data processing instructions
void data_processing(int* ir);

// Mutliply instructions
void multiply(int* ir);

// Single data transfer instructions
void single_data_transfer(int* ir);

// Branch instructions
void branch(int* ir);
