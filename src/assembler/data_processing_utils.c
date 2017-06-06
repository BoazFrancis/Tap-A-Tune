#include "assemble.h"

/**
 * Calculate the operand by considering rotation and shifting
 * @param instruction - A pointer to the instruction
 * @param value - The string value of the operand in the .s file
 * @returns the unsigned opera nd
 */
unsigned int calculate_op2(int* instruction, char* value) {

  unsigned int op2;

  if (value[0] == '#') {
    // Immediate value
    set_bit(instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
    int rotation = get_rotated_op(&op2);
    // The full operand is the first 8 bits of op2 | the 4 bits of rotation
    op2 = (rotation << OP2_SIZE) | op2;
  }
  else {
    // Register e.g. mov r2, r1
    clear_bit(instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
    check_shift(instruction, value);
  }

  return op2;

}

/**
 * Deal with the parameters for data processing instructions
 * @param param - All the parameters for these instructions
 * @param two_reg - If 1 then Rn and Rd are included, if 0 then just one register
 * @returns the partially completed data processing instruction
 */
int setup_params(char* params, int two_reg) {

  // Declare binary instruction, set it to 0
  unsigned int instruction = 0;

  char* value;

  // Set the condition field to 1110 (i.e. 14)
  unsigned int cond = AL_FLAG << COND_START;

  char* rn_string = strtok_r(trim_whitespace(params), ",", &value);
  value = trim_whitespace(value);
  // Set Rn to value of base register
  unsigned int rn = strtol(rn_string+1, NULL, 0);

  if (two_reg == 1) {
    rn <<= DP_DEST_REG;
    char* rd_string = strtok_r(value, ",", &value);
    // set Rd to value of destination register
    value = trim_whitespace(value);
    unsigned int rd = strtol(rd_string+1, NULL, 0) << DP_SRC_REG;
    instruction |= rd;
  }
  else {
    // Shift the single register to position 16
    rn <<= DP_SRC_REG;
  }

  unsigned int op2 = calculate_op2(&instruction, value);

  instruction |= cond | op2 | rn;
  return instruction;

}

/**
 * If a shift is specified, then consider the different cases
 * @param instruction - A pointer to the instruction
 * @param value - The string value of the operand in the .s file
 * @returns void
 */
void check_shift(int* instruction, char* value) {

  char* shift;
  char* str = strtok_r(value, ",", &shift);

  if (strcmp(trim_whitespace(shift), "")) {

    // Fill a 4 character length string of the shift type
    shift = trim_whitespace(shift);
    char* shift_type = malloc(sizeof(char)*DP_BLOCK_SIZE);
    strncpy(shift_type, shift, DP_BLOCK_SIZE-1);
    shift_type[DP_BLOCK_SIZE-1] = '\0';

    if (!strcmp(shift_type,"lsr")) {
      set_bit(instruction, SHIFT_TYPE_1);
      clear_bit(instruction, SHIFT_TYPE_2);
    }
    else if (!strcmp(shift_type,"lsl")) {
      clear_bit(instruction, SHIFT_TYPE_1);
      clear_bit(instruction, SHIFT_TYPE_2);
    }
    else if (!strcmp(shift_type,"asr")) {
      clear_bit(instruction, SHIFT_TYPE_1);
      set_bit(instruction, SHIFT_TYPE_2);
    }
    else if (!strcmp(shift_type,"ror")) {
      set_bit(instruction, SHIFT_TYPE_1);
      set_bit(instruction, SHIFT_TYPE_2);
    }

    int shift_reg = strtol(shift + OP2_SHIFT_SIZE, NULL, 0);

    if (shift[OP2_SHIFT_SIZE-1] == '#') {
      // If shift value is immediate
      *instruction |= shift_reg << OP2_SHIFT_START;
      clear_bit(instruction, OP2_SHIFYBY_IDENTIFIER);
    }
    else {
      // If shift value is a shifted register
      *instruction |= shift_reg << OP2_RS_START;
      set_bit(instruction, OP2_SHIFYBY_IDENTIFIER);
    }

  }

}
