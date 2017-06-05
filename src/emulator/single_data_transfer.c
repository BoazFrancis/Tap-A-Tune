#include <stdio.h>
#include "emulate.h"
#include <byteswap.h>

/**
* Executes the data processing instructions
* @param proc - The pointer to the processor
*/
void single_data_transfer(struct ARM* proc) {

  // Extract the relavant parts of the instruction
  unsigned int immediate = extract_bit(&proc->ir, 25);
  unsigned int pre_post_indexing = extract_bit(&proc->ir, 24);
  unsigned int up_bit = extract_bit(&proc->ir, 23);
  unsigned int load_store_bit = extract_bit(&proc->ir, 20);

  unsigned int rn = extract_bits(&proc->ir, 16, 4);
  unsigned int rd = extract_bits(&proc->ir, 12, 4);
  unsigned int offset = extract_bits(&proc->ir, 0, 12);

  if (immediate == 1) {
    // To avoid setting shifter flags with data processing set S to 0
    clear_bit(&proc->ir, 20);
    // Flip the Immediate bit as it is the opposite in single-data-transfer
    set_bit_to(&proc->ir, DATA_PROC_IMM_IDENTIFIER, extract_bit(&proc->ir, DATA_PROC_IMM_IDENTIFIER) == 0);
    offset = calculate_op2(proc);
  }

  int sign = up_bit == 1 ? 1 : -1;
  int memory_address = proc->registers[rn];

  if (pre_post_indexing == 1) {
    // Pre-indexing
    memory_address += offset * sign;
  }

  if (memory_address == GPIO_20_29 || memory_address == GPIO_10_19 || memory_address == GPIO_0_9) {
    switch (memory_address) {
      case GPIO_0_9:
      proc->gpio_initial_pin = 0;
      break;
      case GPIO_10_19:
      proc->gpio_initial_pin = 10;
      break;
      default:
      proc->gpio_initial_pin = 20;
    }
    gpio_emulator(proc, memory_address);
  }
  else if (memory_address == PIN_OFF || memory_address == PIN_ON) {
    gpio_emulator(proc, memory_address);
  }
  else if (memory_address >= MAX_MEMORY_SIZE) {
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

    if (pre_post_indexing == 0) {
      // Post-indexing
      // Increment base register by offset after execution
      proc->registers[rn] += offset * sign;
    }

  }

}
