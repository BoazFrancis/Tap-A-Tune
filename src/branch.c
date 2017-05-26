#include <stdio.h>
#include "emulate.h"

void branch(struct ARM* proc) {

  // Get bits 0-24 for 2s complement offset
  signed int offset = extract_bits(ir, BRANCH_OFFSET_START, BRANCH_OFFSET_LEN);

  // Shift left by 2 bits
  // and sign extend the offset from 24 to 32 bits
  signed shifted = (offset << 2);
  signed signextend = sign_extension(shifted, 24, 32);

  // Add to PC
  proc->pc = signextend;

}
