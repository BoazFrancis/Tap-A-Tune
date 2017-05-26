#include <stdio.h>
#include "emulate.h"

/**
 * Executes the multiply instructions
 * @param ir - The pointer to the instruction register
*/
void multiply(struct ARM* proc) {

  unsigned int dest_register = binary_to_decimal(extract_bits(&proc->ir, 16, 4));
  unsigned int src_register_s = binary_to_decimal(extract_bits(&proc->ir, 8, 4));
  unsigned int src_register_m = binary_to_decimal(extract_bits(&proc->ir, 0, 4));
  unsigned int src_register_n = binary_to_decimal(extract_bits(&proc->ir, 12, 4));
  unsigned int a = extract_bit(&proc->ir, 21);

  switch (a) {

    case 0:
    multiply_regular(proc, dest_register, src_register_m, src_register_s);
    break;

    case 1:
    multiply_with_accumulate(proc, dest_register, src_register_m, src_register_s, src_register_n);
    break;

  }

}

/**
 * Stores in register d the sum of register n with register n * register s
 * @param ir - The pointer to the ARM
 * @param d - The destination register
 * @param m - Register m
 * @param s - Register s
 * @param n - Register n
*/
void multiply_with_accumulate(struct ARM* proc, unsigned int d, unsigned int m, unsigned int s, unsigned int n) {
  int n_contents = proc->registers[n];
  int s_contents = proc->registers[s];
  int m_contents = proc->registers[m];
  int d_contents = n_contents + (m_contents * s_contents);
  proc->registers[d] = d_contents;
}

/**
 * Stores in register d the result of register n * register s
 * @param proc - The pointer to the ARM
 * @param d - The destination register
 * @param m - Register m
 * @param s - Register s
*/
void multiply_regular(struct ARM* proc, unsigned int d, unsigned int m, unsigned int s){
  int s_contents = proc->registers[s];
  int m_contents = proc->registers[m];
  int d_contents = m_contents * s_contents;
  proc->registers[d] = d_contents;
}
