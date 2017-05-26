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

  int n_contents = proc->registers[src_register_n];
  int s_contents = proc->registers[src_register_s];
  int m_contents = proc->registers[src_register_m];
  printf("%i\n", dest_register);

  switch (a) {

    case 0:
    proc->registers[dest_register] = m_contents * s_contents;
    break;

    case 1:
    proc->registers[dest_register] = n_contents + (m_contents * s_contents);
    break;

  }

}
