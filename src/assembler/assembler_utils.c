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
    if (rotation < (1 << 8)) {
      break;
    }
    i++;
  }
  *operand = rotation;
  return i;
}

void do_mov(char* params, FILE* output) {

  char* value;
  unsigned int cond = 14 << COND_START;
  char* reg = strtok_r(params, ",", &value);
  value = trim_whitespace(value);
  unsigned int instruction = MOV << 21;;
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
  write_to_file(instruction, output);
}

void do_add(char* params, FILE* output) {

}

void do_orr(char* params, FILE* output) {

}

void do_sub(char* params, FILE* output) {

}

void do_cmp(char* params, FILE* output) {

}

void do_eor(char* params, FILE* output) {

}

void do_tst(char* params, FILE* output) {

}

void do_mul(char* params, FILE* output) {

}

void do_teq(char* params, FILE* output) {

}

void do_rsb(char* params, FILE* output) {

}

void do_and(char* params, FILE* output) {

}

void do_mla(char* params, FILE* output) {

}

void do_ldr(char* params, FILE* output) {

}

void do_str(char* params, FILE* output) {

}

void do_beq(char* params, FILE* output) {

}

void do_bne(char* params, FILE* output) {

}

void do_bge(char* params, FILE* output) {

}

void do_blt(char* params, FILE* output) {

}

void do_bgt(char* params, FILE* output) {

}

void do_ble(char* params, FILE* output) {

}

void do_b(char* params, FILE* output) {

}

void do_lsl(char* params, FILE* output) {

}

void do_andeq(char* params, FILE* output) {

}
