#include <stdio.h>
#include "emulate.h"

/**
 * Executes the data processing instructions
 * @param ir - The pointer to the instruction register
*/
void data_processing(int* ir) {
  if (extract_bit(ir, 25) == 1) {
    unsigned int op2 =
  }

  unsigned int opcode = extract_bits(ir, 21, 4);

  switch (opcode) {
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

  }

}

}
