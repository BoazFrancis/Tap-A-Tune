#include "assemble.h"

/**
 * Process the MUL instruction
 * @param params - The string params for this instruction
 * @returns the instruction
 */
int do_mul(char* params) {

  // Declare binary instruction, set it to 0
  unsigned int instruction = 0;
  char* rest;

  // Set the condition field to 1110 (i.e. 14)
  unsigned int cond = AL_FLAG << COND_START;

  // Set bits 4 and 7
  // Bits A and S are not set
  set_bit((int*)&instruction, MULT_ID_1);
  set_bit((int*)&instruction, MULT_ID_2);

  char* rd_string = strtok_r(params, ",", &rest);
  char* rm_string = strtok_r(trim_whitespace(rest), ",", &rest);
  char* rs_string = strtok_r(trim_whitespace(rest), ",", &rest);

  // Set Rn to value of base register
  unsigned int rd = strtol(rd_string+1, NULL, 0) << MUL_DEST;
  unsigned int rs = strtol(rs_string+1, NULL, 0) << MUL_RS;
  unsigned int rm = strtol(rm_string+1, NULL, 0) << MUL_RM;

  instruction |= cond | rd | rs | rm;
  return instruction;

}

/**
 * Process the MLA instruction
 * @param params - The string params for this instruction
 * @returns the instruction
 */
int do_mla(char* params) {

  // Call MUL with the same parameters
  char* original_params = malloc(sizeof(params));
  strcpy(original_params, params);
  unsigned int instruction = do_mul(params);

  // Break up the parameters again to find Rn for accumulate
  char* rest;
  strtok_r(original_params, ",", &rest);
  strtok_r(trim_whitespace(rest), ",", &rest);
  strtok_r(trim_whitespace(rest), ",", &rest);
  char* rn_string = strtok_r(trim_whitespace(rest), ",", &rest);

  // Set the accumulate bit
  set_bit((int*)&instruction, MUL_ACCUMULATE);

  unsigned int rn = strtol(rn_string+1, NULL, 0) << MUL_RN;
  instruction |= rn;
  return instruction;

}
