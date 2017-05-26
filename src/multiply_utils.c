#include <stdio.h>
#include "emulate.h"


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
