#include "assemble.h"

/**
 * Calculate the operand by considering rotation and shifting
 * @param instruction - A pointer to the instruction
 * @param value - The string value of the operand in the .s file
 * @returns the unsigned opera nd
 */
unsigned int calculate_op2(unsigned int *instruction, char *value) {

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
    char *shift;
    strtok_r(value, ",", &shift);
    check_shift(instruction, shift);
  }

  return op2;

}

/**
 * Deal with the parameters for data processing instructions
 * @param param - All the parameters for these instructions
 * @param two_reg - If 1 then Rn and Rd are included, if 0 then just one register
 * @returns the partially completed data processing instruction
 */
int setup_params(char *params, int two_reg) {

  // Declare binary instruction, set it to 0
  unsigned int instruction = 0;

  char *value;

  // Set the condition field to 1110 (i.e. 14)
  unsigned int cond = AL_FLAG << COND_START;

  char *rn_string = strtok_r(trim_whitespace(params), ",", &value);
  value = trim_whitespace(value);
  // Set Rn to value of base register
  unsigned int rn = strtol(rn_string+1, NULL, 0);

  if (two_reg == 1) {
    rn <<= DP_DEST_REG;
    char *rd_string = strtok_r(value, ",", &value);
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
