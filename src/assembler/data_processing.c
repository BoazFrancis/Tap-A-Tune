#include "assemble.h"

/**
 * Process the MOV instruction
 * @param params - The string params for this instruction
 * @returns the instruction
 */
int do_mov(char *params) {

  char *value;
  unsigned int cond = AL_FLAG << COND_START;
  char *reg = strtok_r(params, ",", &value);
  value = trim_whitespace(value);
  unsigned int instruction = MOV << DP_OPCODE_START;

  unsigned int op2 = calculate_op2(&instruction, value);

  // Store Rd register, removing the "r"
  long unsigned reg_binary = strtol(reg+1, NULL, 0);
  reg_binary <<= DP_DEST_REG;

  instruction |= cond | op2 | reg_binary;
  return instruction;

}

/**
 * Process the ADD instruction
 * @param params - The string params for this instruction
 * @returns the instruction
 */
int do_add(char *params) {
  unsigned int opcode = ADD << DP_OPCODE_START;
  return setup_params(params, 1) | opcode;
}

/**
 * Process the ORR instruction
 * @param params - The string params for this instruction
 * @returns the instruction
 */
int do_orr(char *params) {
  unsigned int opcode = ORR << DP_OPCODE_START;
  return setup_params(params, 1) | opcode;
}

/**
 * Process the SUB instruction
 * @param params - The string params for this instruction
 * @returns the instruction
 */
int do_sub(char *params) {
  unsigned int opcode = SUB << DP_OPCODE_START;
  return setup_params(params, 1) | opcode;
}

/**
 * Process the CMP instruction
 * @param params - The string params for this instruction
 * @returns the instruction
 */
int do_cmp(char *params) {
  unsigned int instruction = setup_params(params, 0);
  unsigned int opcode = CMP << DP_OPCODE_START;
  set_bit(&instruction, S_BIT);
  return instruction | opcode;
}

/**
 * Process the EOR instruction
 * @param params - The string params for this instruction
 * @returns the instruction
 */
int do_eor(char *params) {
  unsigned int opcode = EOR << DP_OPCODE_START;
  return setup_params(params, 1) | opcode;
}

/**
 * Process the TST instruction
 * @param params - The string params for this instruction
 * @returns the instruction
 */
int do_tst(char *params) {
  unsigned int instruction = setup_params(params, 0);
  unsigned int opcode = TST << DP_OPCODE_START;
  set_bit(&instruction, S_BIT);
  return instruction | opcode;
}

/**
 * Process the TEQ instruction
 * @param params - The string params for this instruction
 * @returns the instruction
 */
int do_teq(char *params) {
  unsigned int instruction = setup_params(params, 0);
  unsigned int opcode = TEQ << DP_OPCODE_START;
  set_bit(&instruction, S_BIT);
  return instruction | opcode;
}

/**
 * Process the RSB instruction
 * @param params - The string params for this instruction
 * @returns the instruction
 */
int do_rsb(char *params) {
  unsigned int opcode = RSB << DP_OPCODE_START;
  return setup_params(params, 1) | opcode;
}

/**
 * Process the AND instruction
 * @param params - The string params for this instruction
 * @returns the instruction
 */
int do_and(char *params) {
  unsigned int opcode = AND << DP_OPCODE_START;
  return setup_params(params, 1) | opcode;
}
