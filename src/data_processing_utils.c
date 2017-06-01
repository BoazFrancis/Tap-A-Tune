#include <stdio.h>
#include "emulate.h"

int calculate_op2(struct ARM* proc) {

  // if the operand2 is an immediate value
  if (extract_bit(&proc->ir, DATA_PROC_IMM_IDENTIFIER) == 1) {
    int op2 = extract_bits(&proc->ir, 0, 8);
    return rotate_right(op2, 2*extract_bits(&proc->ir, 8, 4));
  }
  else {

    // operand2 is a register
    unsigned int shiftBy;

    if (is_bit_set(&proc->ir, 4)) {
      unsigned int rsNumber = extract_bits(&proc->ir, 8, 4);
      shiftBy = proc->registers[rsNumber] & 0xFF;
    }
    else {
      shiftBy = extract_bits(&proc->ir, 7, 5);
    }

    // Return the result of the barrel shifter
    return barrel_shifter(proc, shiftBy);

  }

}

int barrel_shifter(struct ARM* proc, int shiftBy) {

  unsigned int shiftType = extract_bits(&proc->ir, 5, 2);
  unsigned int rm = extract_bits(&proc->ir, 0, 4);
  unsigned int s = extract_bit(&proc->ir, 20);

  // Setup the result variable
  int r = 0;

  switch (shiftType) {

    case LOGICAL_LEFT:
      r = proc->registers[rm] << shiftBy;
      if (s) {
				int c = (shiftBy == 0) ? 0 : extract_bit(&proc->registers[rm], WORD_SIZE*BITS_IN_BYTE - shiftBy);
				set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_C, c);
			}
      return r;

    case LOGICAL_RIGHT:
      r = proc->registers[rm] >> shiftBy;
      break;

    case ARITHMETIC_RIGHT:
      r = proc->registers[rm] >> shiftBy;
      break;

    case ROTATE_RIGHT:
      r = rotate_right(proc->registers[rm], shiftBy);
      break;

  }

  // Set C flag for logical right, arithmetic right and rotate right
  if (s) {
    int c = (shiftBy == 0) ? 0 : extract_bit(&proc->registers[rm], shiftBy - 1);
    set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_C, c);
  }

  return r;

}
