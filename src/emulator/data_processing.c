#include <stdint.h>
#include "emulate.h"

void set_cpsr_nz(ARM* proc, int s, int result) {
  if (s == 1) {
    set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_N, extract_bit(&result, WORD_SIZE*BITS_IN_BYTE-1));
    set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_Z, result == 0);
  }
}

void set_cpsr_c(ARM* proc, int s, int c) {
  if (s == 1) {
    set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_C, c);
  }
}

void do_and(ARM* proc, int rn, unsigned int op2, int dest, int s) {
  int result = op2 & rn;
  proc->registers[dest] = result;
  set_cpsr_nz(proc, s, result);
}

void do_eor(ARM* proc, int rn, unsigned int op2, int dest, int s) {
  int result = op2 ^ rn;
  proc->registers[dest] = result;
  set_cpsr_nz(proc, s, result);
}

void do_sub(ARM* proc, int rn, unsigned int op2, int dest, int s) {
  int result = rn - op2;
  proc->registers[dest] = result;
  do_cmp(proc, rn, op2, dest, s);
}

void do_rsb(ARM* proc, int rn, unsigned int op2, int dest, int s) {
  int result = op2 - rn;
  proc->registers[dest] = result;
  set_cpsr_nz(proc, s, result);
  set_cpsr_c(proc, s, rn <= op2);
}

void do_add(ARM* proc, int rn, unsigned int op2, int dest, int s) {
  int result = rn + op2;
  proc->registers[dest] = result;
  set_cpsr_nz(proc, s, result);
  if (s == 1) {
    int a = extract_bit(&rn, WORD_SIZE*BITS_IN_BYTE-1);
    int b = extract_bit(&op2, WORD_SIZE*BITS_IN_BYTE-1);
    int c = extract_bit(&proc->registers[dest], WORD_SIZE*BITS_IN_BYTE-1);
    set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_C, ((!a) & (!b) & c) | (a & b & (!c)));
  }
}

void do_tst(ARM* proc, int rn, unsigned int op2, int dest, int s) {
  set_cpsr_nz(proc, s, op2 & rn);
}

void do_teq(ARM* proc, int rn, unsigned int op2, int dest, int s) {
  set_cpsr_nz(proc, s, op2 ^ rn);
}

void do_cmp(ARM* proc, int rn, unsigned int op2, int dest, int s) {
  set_cpsr_nz(proc, s, rn - op2);
  set_cpsr_c(proc, s, rn >= op2);
}

void do_orr(ARM* proc, int rn, unsigned int op2, int dest, int s) {
  int result = rn | op2;
  proc->registers[dest] = result;
  set_cpsr_nz(proc, s, result);
}

void do_mov(ARM* proc, int rn, unsigned int op2, int dest, int s) {
  int result = op2;
  proc->registers[dest] = result;
  set_cpsr_nz(proc, s, result);
}

/**
* Executes the data processing instructions
* @param ir - The pointer to the instruction register
*/
void data_processing(ARM* proc) {

  // Extract the position of the source and destination register
  unsigned int srcRegPos = extract_bits(&proc->ir, 16, 4);
  unsigned int destRegPos = extract_bits(&proc->ir, 12, 4);

  unsigned int s = extract_bit(&proc->ir, 20);

  // Get value of source register Rn
  int rn = proc->registers[srcRegPos];

  // Declare a variable for operand 2
  uint32_t op2;
  op2 = calculate_op2(proc);

  unsigned int opcode = extract_bits(&proc->ir, 21, 4);

  void (*dp_methods[14])(ARM* proc, int rn, unsigned int op2, int dest, int s) = {
  	&do_and, &do_eor, &do_sub, &do_rsb, &do_add, NULL, NULL, NULL,
    &do_tst, &do_teq, &do_cmp, NULL, &do_orr, &do_mov
  };

  dp_methods[opcode](proc, rn, op2, destRegPos, s);

}
