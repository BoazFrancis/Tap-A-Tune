#include "../lib/bitutils.h"

// Create the ARM struct
struct ARM {
   unsigned int memory[MAX_MEMORY_SIZE];
   unsigned int registers[NUM_REGISTERS];
   unsigned int ir;
   unsigned int load;
   unsigned int has_loaded;
   unsigned int has_fetched;
};

// Reading binary files
void read_binary_file(struct ARM* proc, char* path);

// Type of instruction
enum instruction_type {
  DATA_PROCESSING,
  MULTIPLY,
  SINGLE_DATA_TRANSFER,
  BRANCH,
  SPECIAL,
  LABEL
};

// Type of shift
enum shift_type {
  LOGICAL_LEFT,
  LOGICAL_RIGHT,
  ARITHMETIC_RIGHT,
  ROTATE_RIGHT
};

// Fetch-execute cycle
void fetch_decode_execute(struct ARM* proc);
int check_condition_bits(struct ARM* proc);
enum instruction_type get_instruction_type(int* ir);
int memaddr_to_index(int memaddr);
int index_to_memaddr(int index);

// Output
void print_registers(struct ARM* proc);
void print_nonzeromemory(struct ARM* proc);
unsigned int read_memory_bytes(struct ARM* proc, unsigned int addr);
void write_memory_bytes(struct ARM* proc, unsigned int data, unsigned int addr);

// Data processing instructions
void data_processing(struct ARM* proc);
int calculate_op2(struct ARM* proc);
int barrel_shifter(struct ARM* proc, int shiftBy);

// Mutliply instructions
void multiply(struct ARM* proc);
void multiply_with_accumulate(struct ARM* proc, unsigned int d, unsigned int m, unsigned int s, unsigned int n);
void multiply_regular(struct ARM* proc, unsigned int d, unsigned int m, unsigned int s);

// Single data transfer instructions
void single_data_transfer(struct ARM* proc);

// Branch instructions
void branch(struct ARM* proc);
