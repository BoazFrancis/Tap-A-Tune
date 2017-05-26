#include <stdio.h>
#include "emulate.h"

/**
 * Executes the data processing instructions
 * @param ir - The pointer to the instruction register
*/
void data_processing(int* ir) {
  // if the operand2 is an immediate value
  if (extract_bit(ir, 25) == 1) {
    unsigned int op2
      = rotate_right(extract_bits(ir, 0, 8), 2*extract_bits(ir, 8, 4));
  }
  // if the operand2 is a register
  else {
    unsigned int fourth_bit = extract_bit(ir, 4);
    unsigned int shiftType = extract_bits(ir, 5, 2);
    /*switch (shiftType) {
      case 0:

      case 1:
      case 2:
      case 3:
    } */


  }

  unsigned int opcode = extract_bits(ir, 21, 4);

/*  switch (opcode) {
    case 0:
       and();
       break;
    case 1:
       eor();
       break;
    case 2:
       sub();
       break;
    case 3:
       rsb();
       break;
    case 4:
       add();
       break;
    case 8:
       tst();
       break;
    case 9:
       teq();
       break;
    case 10:
       cmp();
       break;
    case 12:
       orr();
       break;
    case 13:
       mov();
       break;
    default:
       break;

  } */
}
