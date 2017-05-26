#include <stdio.h>
#include "emulate.h"

void move(struct ARM* proc, int register_d, int operand) {
  proc->registers[register_d] = operand;
}
