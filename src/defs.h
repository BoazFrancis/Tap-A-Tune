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

#define COND_START 28
#define COND_NUM_BITS 4
#define Z_SET 0
#define Z_CLEAR 1
#define N_EQUALS_V 10
#define N_NOT_V 11
#define Z_CLEAR_N_EQUALS_V 12
#define Z_SET_N_NOT_V 13
#define AL_FLAG 14

#define BRANCH_OFFSET_START 0
#define BRANCH_OFFSET_LEN 24

// CPSR register
#define CPSR_N 31
#define CPSR_C 29
#define CPSR_V 28
#define CPSR_Z 30
