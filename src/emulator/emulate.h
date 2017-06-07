#include <stdio.h>
#include <stdlib.h>
#include "../lib/bitutils.h"

// Create the ARM struct
typedef struct ARM {
   unsigned int memory[MAX_MEMORY_SIZE];
   unsigned int registers[NUM_REGISTERS];
   unsigned int ir;
   int load;
   int has_loaded;
   int has_fetched;
} ARM;

// Reading binary files
void read_binary_file(ARM* proc, char* path);

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
void fetch_decode_execute(ARM* proc);
int check_condition_bits(ARM* proc);
enum instruction_type get_instruction_type(unsigned int* ir);

// Output
void print_registers(ARM* proc);
void print_nonzeromemory(ARM* proc);

// Data processing instructions
void data_processing(ARM* proc);
void do_and(ARM* proc, unsigned int rn, unsigned int op2, int dest, int s);
void do_eor(ARM* proc, unsigned int rn, unsigned int op2, int dest, int s);
void do_sub(ARM* proc, unsigned int rn, unsigned int op2, int dest, int s);
void do_rsb(ARM* proc, unsigned int rn, unsigned int op2, int dest, int s);
void do_add(ARM* proc, unsigned int rn, unsigned int op2, int dest, int s);
void do_tst(ARM* proc, unsigned int rn, unsigned int op2, int dest, int s);
void do_teq(ARM* proc, unsigned int rn, unsigned int op2, int dest, int s);
void do_cmp(ARM* proc, unsigned int rn, unsigned int op2, int dest, int s);
void do_orr(ARM* proc, unsigned int rn, unsigned int op2, int dest, int s);
void do_mov(ARM* proc, unsigned int rn, unsigned int op2, int dest, int s);

void store_result(ARM* proc, int result, int* dest, int s);
void set_cpsr_nz(ARM* proc, int s, unsigned int result);
void set_cpsr_c(ARM* proc, int s, int c);

// Utils
int calculate_op2(ARM* proc);
int barrel_shifter(ARM* proc, int shiftBy);
int memaddr_to_index(int memaddr);
int index_to_memaddr(int index);
int read_memory_bytes(ARM* proc, unsigned int addr);
void write_memory_bytes(ARM* proc, unsigned int data, unsigned int addr);

// Mutliply instructions
void multiply(ARM* proc);
void multiply_with_accumulate(ARM* proc, unsigned int d, unsigned int m, unsigned int s, unsigned int n);
void multiply_regular(ARM* proc, unsigned int d, unsigned int m, unsigned int s);

// Single data transfer instructions
void single_data_transfer(ARM* proc);

// Branch instructions
void branch(ARM* proc);

//GPIO instuctions
void setGPIO(ARM* proc);
void clearGPIO(ARM* proc);
int getGPIO(ARM* proc, int* memory_address);
