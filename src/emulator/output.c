#include "emulate.h"

/**
 * Print the state of the registers
 * @param proc - A pointer to the processor
 * @returns void
 */
void print_registers(ARM *proc) {
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

/**
 * Print the non-zero memory
 * @param proc - A pointer to the processor
 * @returns void
 */
void print_nonzeromemory(ARM *proc) {
  printf("Non-zero memory:\n");
  for (int i=0; i<MAX_MEMORY_SIZE; i++) {
    if (proc->memory[i] != 0) {
      printf("0x%08x: 0x%08x\n", index_to_memaddr(i), reverse_int(proc->memory[i]));
    }
  }
}
