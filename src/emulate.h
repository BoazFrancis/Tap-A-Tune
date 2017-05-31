#include "defs.h"

// Create the ARM struct
struct ARM {
   int memory[MAX_MEMORY_SIZE];
   int registers[NUM_REGISTERS];
   int pc;
   int ir;
   int load;
   int has_loaded;
   int has_fetched;
};

// Reading binary files
void read_binary_file(struct ARM* proc, char* path);

// Bit-utils
int extract_bits(int* n, int start, int length);
int extract_bit(int* n, int start);
int is_bit_set(int* n, int bit);
void set_bit(int* n, int bit);
void clear_bit(int* n, int bit);
void set_bit_to(int* n, int bit, int value);
unsigned int binary_to_decimal(unsigned int bin);
unsigned int base_to_base(int from, int to, unsigned int n);
signed int sign_extension(signed int n, int sbits, int ebits);
unsigned int read_memory_bytes(struct ARM* proc, unsigned int addr);
void write_memory_bytes(struct ARM* proc, unsigned int data, unsigned int addr);
int reverse_int(int n);

unsigned int rotate_left(const unsigned int val, int shiftBy);
unsigned int rotate_right(const unsigned int val, int shiftBy);

// Type of instruction
enum instruction_type {
  DATA_PROCESSING,
  MULTIPLY,
  SINGLE_DATA_TRANSFER,
  BRANCH
};

// Type of shift
enum shift_type {
  LOGICAL_LEFT,
  LOGICAL_RIGHT,
  ARITHMETIC_RIGHT,
  ROTATE_RIGHT
};

// Opcodes for data_processing
enum opcode {
  AND = 0,
  EOR = 1,
  SUB = 2,
  RSB = 3,
  ADD = 4,
  TST = 8,
  TEQ = 9,
  CMP = 10,
  ORR = 12,
  MOV = 13
};

// Fetch-execute cycle
void fetch_decode_execute(struct ARM* proc);
int check_condition_bits(struct ARM* proc);
enum instruction_type get_instruction_type(int* ir);
int memaddr_to_index(int memaddr);
int index_to_memaddr(int index);

// Output for testing
void print_registers(struct ARM* proc);
void print_nonzeromemory(struct ARM* proc);

// Data processing instructions
void data_processing(struct ARM* proc);
unsigned int shiftLeft(unsigned const int val, unsigned int shiftBy);
int logicalShiftRight(const int val, unsigned int shiftBy);
int arithmeticShiftRight(const int val, unsigned int shiftBy);
unsigned int shift_by_type(unsigned int shiftType, unsigned int val, unsigned int shiftBy);

// Mutliply instructions
void multiply(struct ARM* proc);
<<<<<<< HEAD
void multiply_with_accumulate(int* ir, unsigned int d, unsigned int m, unsigned int s, unsigned int n);
void multiply_regular(int* ir, unsigned int d, unsigned int m, unsigned int s);

// Single data transfer instructions
void single_data_transfer(struct ARM* proc);
void ldr(struct ARM* proc, unsigned int d, )
=======
void multiply_with_accumulate(struct ARM* proc, unsigned int d, unsigned int m, unsigned int s, unsigned int n);
void multiply_regular(struct ARM* proc, unsigned int d, unsigned int m, unsigned int s);

// Single data transfer instructions
void single_data_transfer(struct ARM* proc);
>>>>>>> 04d9bf3816072e58f2aac8d41a7aa04d1755e68d

// Branch instructions
void branch(struct ARM* proc);
