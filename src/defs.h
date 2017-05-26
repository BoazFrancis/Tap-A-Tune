// ARM processor specifications
#define MAX_MEMORY_SIZE (1 << 4)
#define NUM_REGISTERS 17

// Useful registers
#define CPSR_REGISTER 16

// Identifying bits for instructions (bits 26, 27)
#define BRANCH_IDENTIFIER 27
#define SINGLE_DATA_IDENTIFIER 26
#define MULT_ID_1 4
#define MULT_ID_2 7

// CPSR register
#define CPSR_N 31
#define CPSR_C 29
#define CPSR_V 28
#define CPSR_Z 30
