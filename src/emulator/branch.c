#include "emulate.h"

void branch(ARM* proc) {

  // Get bits 0-24 for 2s complement offset
  signed int offset = extract_bits(&proc->ir, BRANCH_OFFSET_START, BRANCH_OFFSET_LEN);

  // Shift left by 2 bits
  // and sign extend the offset from 24 to 32 bits
  offset <<= 2;
  int sign_bit = extract_bit(&proc->ir, 23);

  if (sign_bit) {
    offset |= 0xff000000;
  }

  // Add to PC
  proc->pc += offset;

  proc->load = 0;
  proc->ir = 0;

  proc->has_loaded = 0;
  proc->has_fetched = 0;

}
