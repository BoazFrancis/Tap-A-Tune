#include "emulate.h"

/**
 * Executes the multiply instructions (MUL and MLA)
 * @param proc - The pointer to the ARM processor
 * @returns void
*/
void multiply(ARM* proc) {

  unsigned int dest_register = extract_bits(proc->ir, MUL_DEST, MUL_BLOCK_SIZE);
  unsigned int src_register_s = extract_bits(proc->ir, MUL_RS, MUL_BLOCK_SIZE);
  unsigned int src_register_m = extract_bits(proc->ir, MUL_RM, MUL_BLOCK_SIZE);
  unsigned int src_register_n = extract_bits(proc->ir, MUL_RN, MUL_BLOCK_SIZE);
  unsigned int accumulate = extract_bit(proc->ir, MUL_ACCUMULATE);

  int n_contents = proc->registers[src_register_n];
  int s_contents = proc->registers[src_register_s];
  int m_contents = proc->registers[src_register_m];

  // Store the results of MUL and MLA
  switch (accumulate) {

    case 0:
    proc->registers[dest_register] = m_contents * s_contents;
    break;

    case 1:
    proc->registers[dest_register] = n_contents + (m_contents * s_contents);
    break;

  }

}
