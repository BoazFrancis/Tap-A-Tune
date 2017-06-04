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

unsigned int read_memory_bytes(struct ARM* proc, unsigned int addr) {
  unsigned int mod = addr % WORD_SIZE;
  unsigned int start_addr = addr / WORD_SIZE;
  unsigned int start_bit = mod * BITS_IN_BYTE;
  unsigned int bits_remaining = WORD_SIZE * BITS_IN_BYTE - start_bit;
  unsigned int extracted_first = extract_bits(&proc->memory[start_addr], start_bit, bits_remaining);
  unsigned int extracted_second = extract_bits(&proc->memory[start_addr+1], 0, start_bit);
  unsigned int new_second = extracted_second << bits_remaining;
  return extracted_first | new_second;
}

void write_memory_bytes(struct ARM* proc, unsigned int data, unsigned int addr) {
  unsigned int mod = addr % WORD_SIZE;
  unsigned int start_addr = addr / WORD_SIZE;
  unsigned int end_bit = mod * BITS_IN_BYTE;
  unsigned int bits_remaining = WORD_SIZE * BITS_IN_BYTE - end_bit;
  unsigned int lsb_data = extract_bits(&data, 0, bits_remaining);
  unsigned int lower_memory = extract_bits(&proc->memory[start_addr], 0, end_bit);
  unsigned int new_lower_mem = lower_memory | (lsb_data << end_bit);
  unsigned int higher_memory = extract_bits(&proc->memory[start_addr+1], end_bit, bits_remaining);
  unsigned int msb_data = extract_bits(&data, bits_remaining, end_bit);
  unsigned int new_higher_mem = msb_data | (higher_memory << end_bit);
  // Write to memory
  proc->memory[start_addr] = new_lower_mem;
  proc->memory[start_addr+1] = new_higher_mem;
}
