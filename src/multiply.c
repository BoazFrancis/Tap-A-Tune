#include <stdio.h>
#include "emulate.h"

/**
 * Executes the multiply instructions
 * @param ir - The pointer to the instruction register
*/
void multiply(struct ARM* proc) {
  unsigned int dest_register = binary_to_decimal(extract_bits(proc->ir, 16, 4));
  unsigned int src_register_s = binary_to_decimal(extract_bits(proc->ir, 8, 4));
  unsigned int src_register_m = binary_to_decimal(extract_bits(proc->ir, 0, 4));
  unsigned int a = extract_bit(proc->ir, 21);

  switch (a) {

    case 0:
    multiply_regular(proc, dest_register, src_register_m, src_register_s);

    case 1 :
    unsigned int src_register_n = binary_to_decimal(extract_bits(proc->ir, 12, 4));
    multiply_with_accumulate(proc, dest_register, src_register_m, src_register_s, src_register_n);

  }
}
