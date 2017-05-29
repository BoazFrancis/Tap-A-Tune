#include <stdio.h>
#include <stdlib.h>
#include <byteswap.h>
#include "emulate.h"

void print_registers(struct ARM* proc) {
  printf("Registers:\n");
  for (int i=0; i<=PRINT_REGISTERS; i++) {
    char register_num[100];
    sprintf(register_num, "$%d", i);
    printf("%-4s:          %d (0x%08x)\n", register_num, proc->registers[i], proc->registers[i]);
  }
  printf("PC  :         %d (0x%08x)\n", proc->pc, proc->pc);
  printf("CPSR:          %d (0x%08x)\n", proc->registers[CPSR_REGISTER], proc->registers[CPSR_REGISTER]);
}

void print_nonzeromemory(struct ARM* proc) {
  printf("Non-zero memory:\n");
  for (int i=0; i<MAX_MEMORY_SIZE; i++) {
    if (proc->memory[i] != 0) {
      printf("0x%08x: 0x%08x\n", index_to_memaddr(i), __bswap_32(proc->memory[i]));
    }
  }
}
