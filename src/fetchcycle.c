#include <stdio.h>
#include "emulate.h"

void fetch_decode_execute(struct ARM proc) {

  proc.pc = 0;
  proc.ir = 0;

  do {

    // Get the next instruction and increment PC
    proc.ir = proc.memory[proc.pc];
    proc.pc++;

    if (check_condition_bits(proc) == 1) {

      /*
        switch (get_instruction_type(&ir)) {

          case DATA_PROCESSING:
          data_processing(&ir);
          break;

          case BRANCH:
          branch(&ir);
          break;

          case MULTIPLY:
          multiply(&ir);
          break;

          case SINGLE_DATA_TRANSFER:
          single_data_transfer(&ir);
          break;
        }

      */

    }

  }
  while (proc.ir != 0);

}

int check_condition_bits(struct ARM proc) {

  // Get the 4 most significant bits which is the "Cond"
  int cond = extract_bits(&proc.ir, 28, 4);

  switch (cond) {

    // Z set
    case 0:
    break;

    // Z clear
    case 1:
    break;

    // N equals V
    case 10:
    break;

    // N not equal to V
    case 11:
    break;

    // Z clear AND (N equals V)
    case 12:
    break;

    // Z set OR (N not equals to V)
    case 13:
    break;

    // Al flag
    case 14:
    return 1;

    default:
    fprintf(stderr, "Unknown condition");
    return 0;

  }

}
