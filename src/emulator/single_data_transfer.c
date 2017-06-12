#include "emulate.h"

/**
 * Executes the data processing instructions
 * @param proc - The pointer to the processor
 * @returns void
 */
void single_data_transfer(ARM *proc) {

  // Extract the relavant parts of the instruction
  unsigned int immediate = extract_bit(proc->ir, SDT_IMM_IDENTIFIER);
  unsigned int pre_post_indexing = extract_bit(proc->ir, SDT_PREPOST);
  unsigned int up_bit = extract_bit(proc->ir, SDT_UP_BIT);
  unsigned int load_store_bit = extract_bit(proc->ir, LOAD_STORE_BIT);

  unsigned int rn = extract_bits(proc->ir, SDT_RN, SDT_BLOCK_SIZE);
  unsigned int rd = extract_bits(proc->ir, SDT_RD, SDT_BLOCK_SIZE);
  unsigned int offset = extract_bits(proc->ir, SDT_OFFSET_START, SDT_OFFSET_SIZE);

  if (immediate == 1) {
    // To avoid setting shifter flags with data processing set S to 0
    clear_bit(&proc->ir, LOAD_STORE_BIT);
    // Flip the Immediate bit as it is the opposite in single-data-transfer
    set_bit_to(&proc->ir, DATA_PROC_IMM_IDENTIFIER, extract_bit(proc->ir, DATA_PROC_IMM_IDENTIFIER) == 0);
    offset = calculate_op2(proc);
  }

  int sign = up_bit == 1 ? 1 : -1;
  int memory_address = proc->registers[rn];

  // Pre-indexing
  if (pre_post_indexing == 1) {
    memory_address += offset * sign;
  }

  if (getGPIO(proc, &memory_address)) {
    return;
  }

  if (memory_address >= MAX_MEMORY_SIZE*WORD_SIZE) {
    printf("Error: Out of bounds memory access at address 0x%08x\n", memory_address);
  }
  else {

    if (load_store_bit == 1) {
      // To load
      proc->registers[rd] = read_memory_bytes(proc, memory_address);
    }
    else {
      // To store
      write_memory_bytes(proc, proc->registers[rd], memory_address);
    }

    // Post-indexing
    if (pre_post_indexing == 0) {
      // Increment base register by offset after execution
      proc->registers[rn] += offset * sign;
    }

  }

}
