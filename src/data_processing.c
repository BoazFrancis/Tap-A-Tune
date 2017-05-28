#include <stdio.h>
#include <stdint.h>
#include "emulate.h"

/**
 * Executes the data processing instructions
 * @param ir - The pointer to the instruction register
*/
void data_processing(struct ARM* proc) {

  // Extract the position of the source and destination register
  unsigned int srcRegPos = binary_to_decimal(extract_bits(&proc->ir, 16, 4));
  unsigned int destRegPos = binary_to_decimal(extract_bits(&proc->ir, 12, 4));

  // Get value of source register
  unsigned int srcRegVal = (*proc).registers[srcRegPos];

  // Extract the positions of the Rm
  unsigned int rmPos = binary_to_decimal(extract_bits(&proc->ir, 0, 4));

  // Get value of the Rm
  int rmVal = (*proc).registers[rmPos];

  // if the operand2 is an immediate value
  if (extract_bit(&proc->ir, 25) == 1) {
    uint32_t op2 = extract_bits(&proc->ir, 0, 8);
    op2 = rotate_right(op2, 2*extract_bits(&proc->ir, 8, 4));
  }
  // if the operand2 is a register
  else {
    unsigned int fourth_bit = extract_bit(&proc->ir, 4);
    unsigned int shiftType = extract_bits(&proc->ir, 5, 2);
    unsigned int rm = extract_bits(&proc->ir, 0, 3);
    unsigned int shiftBy;
    if (fourth_bit == 0) {
      shiftBy = extract_bits(&proc->ir, 7, 5);
    } else {
      // fourth_bit == 1
      unsigned int rsNumber = extract_bits(&proc->ir, 8, 11);
      shiftBy = (*proc).registers[rsNumber];
    }
    // shift using the specified shift type and write result to op2
    uint32_t op2 = shift_by_type(shiftType, rm, shiftBy);
    }

  unsigned int opcode = extract_bits(&proc->ir, 21, 4);

  switch (opcode) {
    case AND:
       logical_and(op2);
       break;
    case EOR:
       eor(op2);
       break;
    case SUB:
       sub(op2);
       break;
    case RSB:
       rsb(op2);
       break;
    case ADD:
       add(op2);
       break;
    case TST:
       tst(op2);
       break;
    case TEQ:
       teq(op2);
       break;
    case CMP:
       cmp(op2);
       break;
    case ORR:
       orr(op2);
       break;
    case MOV:
       mov(op2);
       break;
    default:
      break;

  }
}
