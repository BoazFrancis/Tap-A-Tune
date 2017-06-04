#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assemble.h"

int get_rotated_op(unsigned int* operand) {
  // Keep rotating until size is 8 bits
  int i = 0;
  unsigned int rotation;
  while (i < 16) {
    rotation = rotate_left(*operand, 2*i);
    if (rotation < (1 << 9)) {
      break;
    }
    i++;
  }
  *operand = rotation;
  return i;
}

int do_mov(char* params) {
  char* value;
  unsigned int cond = 14 << COND_START;
  char* reg = strtok_r(params, ",", &value);
  value = trim_whitespace(value);
  unsigned int instruction = MOV << 21;
  unsigned int op2;

  if (value[0] == '#') {
    // Immediate value
    set_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
    int rotation = get_rotated_op(&op2);
    // The full operand is the first 8 bits of op2 | the 4 bits of rotation
    op2 = (rotation << 8) | op2;
  }
  else {
    // Register e.g. mov r2, r1
    clear_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
  }

  // Store Rd register, removing the "r"
  long unsigned reg_binary = strtol(reg+1, NULL, 0);
  reg_binary <<= 12;

  instruction |= cond | op2 | reg_binary;
  return instruction;

}

int do_add(char* params) {

  // Declare binary instruction, set it to 0
  unsigned int instruction = 0;

  char* value;

  // Set the condition field to 1110 (i.e. 14)
  unsigned int cond = 14 << COND_START;

  char* rn_string = strtok_r(params, ",", &value);
  value = trim_whitespace(value);
  // Set Rn to value of base register
  unsigned int rn = strtol(rn_string+1, NULL, 0) << 12;

  char* rd_string = strtok_r(value, ",", &value);
  // set Rd to value of destination register
  value = trim_whitespace(value);
  unsigned int rd = strtol(rd_string+1, NULL, 0) << 16;

  unsigned int opcode = ADD << 21;
  unsigned int op2;
  clear_bit(&instruction, 20);

  if (value[0] == '#') {
    // Immediate value
    set_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
    int rotation = get_rotated_op(&op2);
    // The full operand is the first 8 bits of op2 | the 4 bits of rotation
    op2 = (rotation << 8) | op2;
  }
  else {
    // Register e.g. mov r2, r1
    clear_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
  }

  instruction |= cond | op2 | rd | rn | opcode;
  return instruction;

}

int do_orr(char* params) {

}

int do_sub(char* params) {

}

int do_cmp(char* params) {

}

int do_eor(char* params) {

  // Declare binary instruction, set it to 0
  unsigned int instruction = 0;

  char* value;

  // Set the condition field to 1110 (i.e. 14)
  unsigned int cond = 14 << COND_START;

  char* rn_string = strtok_r(params, ",", &value);
  value = trim_whitespace(value);
  // Set Rn to value of base register
  unsigned int rn = strtol(rn_string+1, NULL, 0) << 12;

  char* rd_string = strtok_r(value, ",", &value);
  // set Rd to value of destination register
  value = trim_whitespace(value);
  unsigned int rd = strtol(rd_string+1, NULL, 0) << 16;

  unsigned int opcode = EOR << 21;
  unsigned int op2;
  clear_bit(&instruction, 20);

  if (value[0] == '#') {
    // Immediate value
    set_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
    int rotation = get_rotated_op(&op2);
    // The full operand is the first 8 bits of op2 | the 4 bits of rotation
    op2 = (rotation << 8) | op2;
  }
  else {
    // Register e.g. mov r2, r1
    clear_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
  }

  instruction |= cond | op2 | rd | rn | opcode;
  return instruction;

}

int do_tst(char* params) {

  char* value;
  unsigned int cond = 14 << COND_START;
  char* reg = strtok_r(params, ",", &value);
  value = trim_whitespace(value);
  unsigned int instruction = 0;
  unsigned int opcode = TST << 21;
  unsigned int op2;
  set_bit(&instruction, 20);
  if (value[0] == '#') {
    // Immediate value
    set_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
    int rotation = get_rotated_op(&op2);
    // The full operand is the first 8 bits of op2 | the 4 bits of rotation
    op2 = (rotation << 8) | op2;
  }
  else {
    // Register e.g. mov r2, r1
    clear_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
  }

  // Store Rd register, removing the "r"
  long unsigned reg_binary = strtol(reg+1, NULL, 0);
  reg_binary <<= 16;

  instruction |= cond | op2 | reg_binary | opcode;
  return instruction;

}

int do_mul(char* params) {

}

int do_teq(char* params) {

}

int do_rsb(char* params) {

}

int do_and(char* params) {

  // Declare binary instruction, set it to 0
  unsigned int instruction = 0;

  char* value;

  // Set the condition field to 1110 (i.e. 14)
  unsigned int cond = 14 << COND_START;

  char* rn_string = strtok_r(params, ",", &value);
  value = trim_whitespace(value);
  // Set Rn to value of base register
  unsigned int rn = strtol(rn_string+1, NULL, 0) << 12;

  char* rd_string = strtok_r(value, ",", &value);
  // set Rd to value of destination register
  value = trim_whitespace(value);
  unsigned int rd = strtol(rd_string+1, NULL, 0) << 16;

  unsigned int opcode = AND << 21;
  unsigned int op2;
  clear_bit(&instruction, 20);

  if (value[0] == '#') {
    // Immediate value
    set_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
    int rotation = get_rotated_op(&op2);
    // The full operand is the first 8 bits of op2 | the 4 bits of rotation
    op2 = (rotation << 8) | op2;
  }
  else {
    // Register e.g. mov r2, r1
    clear_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
  }

  instruction |= cond | op2 | rd | rn | opcode;
  return instruction;

}


int do_mla(char* params) {

}

int do_ldr(char* params) {

}

int do_str(char* params) {

}

int do_beq(char* params) {

}

int do_bne(char* params) {

}

int do_bge(char* params) {

}

int do_blt(char* params) {

}

int do_bgt(char* params) {

}

int do_ble(char* params) {

}

int do_b(char* params, SymbolTable* st, int count) {

  unsigned int cond = 14 << COND_START;
  int jump_addr = get_address(st, trim_whitespace(params)) - count * WORD_SIZE - 8;

  // Set bits 27 and 25
  unsigned int instruction = extract_bits(&jump_addr, BRANCH_OFFSET_START, BRANCH_OFFSET_LEN) >> 2;
  set_bit(&instruction, 25);
  set_bit(&instruction, 27);

  return instruction | cond;

}

int do_lsl(char* params) {

}

int do_andeq(char* params) {

}
