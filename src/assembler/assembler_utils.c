#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assemble.h"
#include "../emulator/emulate.h"

void do_mov(char* params, FILE* output) {
  char comma[2] = ",";
  char* value;
  unsigned int cond = 14 << COND_START;
  char* reg = strtok_r(params, comma, &value);
  value = trim_whitespace(value);
  unsigned int instruction = MOV << 21;
  long unsigned int op2;
  if (value[0] == '#') {
    // Immediate value
    set_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
  }
  else {
    // Register e.g. mov r2, r1
    clear_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
  }
  instruction |= cond | op2;
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
