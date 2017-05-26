#include <stdio.h>
#include <stdlib.h>
#include "emulate.h"

void print_registers(struct ARM* proc) {
  printf("Registers:\n");
  for (int i=0; i<PRINT_REGISTERS; i++) {
    printf("$%d  :          %d (0x%08x)\n", i, proc->registers[i], proc->registers[i]);
  }
  printf("PC  :         %d (0x%08x)\n", proc->pc, proc->pc);
  printf("CPSR:          %d (0x%08x)\n", proc->registers[CPSR_REGISTER], proc->registers[CPSR_REGISTER]);
}

void print_nonzeromemory(struct ARM* proc) {

}
