#include "assemble.h"

int do_ldr_constant(int* instruction, int instruction_addr, int* num_no_labels, int** memory, char* rd_str, char* addr_str, unsigned int rd, unsigned int cond) {
  // Set the offset
  int mem_val = strtol(addr_str+1, NULL, 0);

  if (mem_val < 0xFF) {
    char* without_eq = addr_str + 1;
    char* mov_param = cat(rd_str, ",#", without_eq);
    return do_mov(mov_param);
  }
  else {

    int store_addr = *num_no_labels * WORD_SIZE;
    int offset = store_addr - instruction_addr - 8;
    set_bit(instruction, 24);

    // Set Rn to the PC
    unsigned int rn = PC_REG << 16;

    // Save mem_val
    (*memory)[*num_no_labels] = mem_val;
    (*num_no_labels)++;

    return *instruction | cond | rd | rn | offset;
  }
}
