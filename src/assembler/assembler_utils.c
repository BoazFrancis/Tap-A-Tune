#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assemble.h"
#include "../emulator/emulate.h"

void do_mov(char* params) {
  char comma[2] = ",";
  char* value;
  char* reg = strtok_r(params, comma, &value);
  value = trim_whitespace(value);
  unsigned int instruction = MOV << 21;
  long unsigned int op2;
  if (value[0] == '#') {
    // Immediate value
    set_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
    printf("%ld\n", op2);
  }
  else {
    // Register e.g. mov r2, r1
    clear_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
    printf("%lu\n", op2);
    printf("%x\n", instruction);

  }
}

void do_add(char* params) {

}

void do_orr(char* params) {

}

void do_sub(char* params) {

}

void do_cmp(char* params) {

}

void do_eor(char* params) {

}

void do_tst(char* params) {

}

void do_mul(char* params) {

}

void do_teq(char* params) {

}

void do_rsb(char* params) {

}

void do_and(char* params) {

}

void do_mla(char* params) {

}

void do_ldr(char* params) {

}

void do_str(char* params) {

}

void do_beq(char* params) {

}

void do_bne(char* params) {

}

void do_bge(char* params) {

}

void do_blt(char* params) {

}

void do_bgt(char* params) {

}

void do_ble(char* params) {

}

void do_b(char* params) {

}

void do_lsl(char* params) {

}

void do_andeq(char* params) {

}
