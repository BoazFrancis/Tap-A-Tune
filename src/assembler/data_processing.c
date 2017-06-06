#include "assemble.h"

int do_mov(char* params) {

  char* value;
  unsigned int cond = 14 << COND_START;
  char* reg = strtok_r(params, ",", &value);
  value = trim_whitespace(value);
  unsigned int instruction = MOV << 21;

  unsigned int op2 = calculate_op2(&instruction, value);

  // Store Rd register, removing the "r"
  long unsigned reg_binary = strtol(reg+1, NULL, 0);
  reg_binary <<= 12;

  instruction |= cond | op2 | reg_binary;
  return instruction;

}

int do_add(char* params) {
  unsigned int opcode = ADD << 21;
  return setup_params(params, 1) | opcode;
}

int do_orr(char* params) {
  unsigned int opcode = ORR << 21;
  return setup_params(params, 1) | opcode;
}

int do_sub(char* params) {
  unsigned int opcode = SUB << 21;
  return setup_params(params, 1) | opcode;
}

int do_cmp(char* params) {
  unsigned int instruction = setup_params(params, 0);
  unsigned int opcode = CMP << 21;
  set_bit(&instruction, 20);
  return instruction | opcode;
}

int do_eor(char* params) {
  unsigned int opcode = EOR << 21;
  return setup_params(params, 1) | opcode;
}

int do_tst(char* params) {
  unsigned int instruction = setup_params(params, 0);
  unsigned int opcode = TST << 21;
  set_bit(&instruction, 20);
  return instruction | opcode;
}

int do_teq(char* params) {
  int instruction = setup_params(params, 0);
  unsigned int opcode = TEQ << 21;
  set_bit(&instruction, 20);
  return instruction | opcode;
}

int do_rsb(char* params) {
  unsigned int opcode = RSB << 21;
  return setup_params(params, 1) | opcode;
}

int do_and(char* params) {
  unsigned int opcode = AND << 21;
  return setup_params(params, 1) | opcode;
}
