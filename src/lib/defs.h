// ARM processor specifications
#define MAX_MEMORY_SIZE (1 << 14)
#define NUM_REGISTERS 17
#define WORD_SIZE 4
#define BITS_IN_BYTE 8
#define pc registers[15]
#define PC_REG 15
#define LENGTH_OF_LINE 511

// Useful registers
#define CPSR_REGISTER 16
#define PRINT_REGISTERS 12

// Identifying bits for instructions (bits 26, 27)
#define BRANCH_IDENTIFIER 27
#define SINGLE_DATA_IDENTIFIER 26
#define MULT_ID_1 4
#define MULT_ID_2 7

// Data processing
#define DATA_PROC_IMM_IDENTIFIER 25
#define NUM_DP_INSTRUCTIONS 14
#define S_BIT 20
#define DP_BLOCK_SIZE 4
#define DP_SRC_REG 16
#define DP_DEST_REG 12
#define DP_OPCODE_START 21
#define OP2_START 0
#define OP2_SIZE 8
#define OP2_IMMEDIATE_START 8
#define OP2_IMMEDIATE_SIZE 4
#define OP2_RS_START 8
#define OP2_RS_SIZE 4
#define OP2_SHIFT_START 7
#define OP2_SHIFT_SIZE 5
#define OP2_SHIFYBY_IDENTIFIER 4
#define SHIFT_TYPE_1 5
#define SHIFT_TYPE_2 6

// Multiply
#define MUL_BLOCK_SIZE 4
#define MUL_ACCUMULATE 21
#define MUL_DEST 16
#define MUL_RS 8
#define MUL_RM 0
#define MUL_RN 12

// Branch
#define BRANCH_PIPELINE_OFFSET 8
#define BRANCH_SHIFT 2
#define BRANCH_IDENTIFIER_2 25
#define BRANCH_OFFSET_START 0
#define BRANCH_OFFSET_LEN 24

// Single data transfer
#define SDT_IMM_IDENTIFIER 25
#define SDT_PREPOST 24
#define SDT_UP_BIT 23
#define LOAD_STORE_BIT 20
#define SDT_BLOCK_SIZE 4
#define SDT_OFFSET_SIZE 12
#define SDT_RN 16
#define SDT_RD 12
#define SDT_OFFSET_START 0
#define IS_LDR 1
#define NOT_LDR 0

// Conditions
#define COND_START 28
#define COND_NUM_BITS 4
#define Z_SET 0
#define Z_CLEAR 1
#define N_EQUALS_V 10
#define N_NOT_V 11
#define Z_CLEAR_N_EQUALS_V 12
#define Z_SET_N_NOT_V 13
#define AL_FLAG 14

// CPSR register
#define CPSR_N 31
#define CPSR_Z 30
#define CPSR_C 29
#define CPSR_V 28

enum opcodes {
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

// Identifying physical addresses for GPIO
#define GPIO_0_9 0x20200000
#define GPIO_10_19 0x20200004
#define GPIO_20_29 0x20200008
#define PINS_IN_MEMORY 9
#define PIN_OFF 0x20200028
#define PIN_ON 0x2020001c
