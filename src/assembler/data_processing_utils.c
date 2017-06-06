#include "assemble.h"

unsigned int calculate_op2(int* instruction, char* value) {
  unsigned int op2;
  if (value[0] == '#') {
    // Immediate value
    set_bit(instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
    int rotation = get_rotated_op(&op2);
    // The full operand is the first 8 bits of op2 | the 4 bits of rotation
    op2 = (rotation << 8) | op2;
  }
  else {
    // Register e.g. mov r2, r1
    clear_bit(instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
    check_shift(instruction, value);
  }
  return op2;
}

int setup_params(char* params, int two_reg) {

  // Declare binary instruction, set it to 0
  unsigned int instruction = 0;

  char* value;

  // Set the condition field to 1110 (i.e. 14)
  unsigned int cond = 14 << COND_START;

  char* rn_string = strtok_r(trim_whitespace(params), ",", &value);
  value = trim_whitespace(value);
  // Set Rn to value of base register
  unsigned int rn = strtol(rn_string+1, NULL, 0);

  if (two_reg == 1) {
    rn <<= 12;
    char* rd_string = strtok_r(value, ",", &value);
    // set Rd to value of destination register
    value = trim_whitespace(value);
    unsigned int rd = strtol(rd_string+1, NULL, 0) << 16;
    instruction |= rd;
  }
  else {
    rn <<= 16;
  }

  unsigned int op2 = calculate_op2(&instruction, value);

  instruction |= cond | op2 | rn;
  return instruction;

}

void check_shift(int* instruction, char* value) {

  char* shift;
  char* str = strtok_r(value, ",", &shift);

  if (strcmp(trim_whitespace(shift), "")) {

    shift = trim_whitespace(shift);
    char* shift_type = malloc(sizeof(char)*4);
    strncpy(shift_type, shift, 3);
    shift_type[3] = '\0';

    if (!strcmp(shift_type,"lsr")) {
      set_bit(instruction, 5);
      clear_bit(instruction, 6);
    }
    else if (!strcmp(shift_type,"lsl")) {
      clear_bit(instruction, 5);
      clear_bit(instruction, 6);
    }
    else if (!strcmp(shift_type,"asr")) {
      clear_bit(instruction, 5);
      set_bit(instruction, 6);
    }
    else if (!strcmp(shift_type,"ror")) {
      set_bit(instruction, 5);
      set_bit(instruction, 6);
    }

    int shift_reg = strtol(shift + 5, NULL, 0);

    if (shift[4] == '#') {
      *instruction |= shift_reg << 7;
      clear_bit(instruction, 4);
    }
    else {
      *instruction |= shift_reg << 8;
      set_bit(instruction, 4);
    }

  }

}
