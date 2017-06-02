#include <stdio.h>
#include <stdlib.h>
#include "emulate.h"

void print_registers(struct ARM* proc) {
  printf("Registers:\n");
  for (int i=0; i<=PRINT_REGISTERS; i++) {
    char register_num[100];
    char register_val[100];
    sprintf(register_num, "$%d", i);
    sprintf(register_val, "%d", proc->registers[i]);
    printf("%-4s: %10s (0x%08x)\n", register_num, register_val, proc->registers[i]);
  }
  printf("PC  : %10d (0x%08x)\n", proc->pc, proc->pc);
  printf("CPSR: %10d (0x%08x)\n", proc->registers[CPSR_REGISTER], proc->registers[CPSR_REGISTER]);
}

void print_nonzeromemory(struct ARM* proc) {
  printf("Non-zero memory:\n");
  for (int i=0; i<MAX_MEMORY_SIZE; i++) {
    if (proc->memory[i] != 0) {
      printf("0x%08x: 0x%08x\n", index_to_memaddr(i), reverse_int(proc->memory[i]));
    }
  }
}
