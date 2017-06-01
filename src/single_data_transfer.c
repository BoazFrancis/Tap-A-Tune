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
    // offset is a register
    unsigned int fourth_bit = extract_bit(&proc->ir, 4);
    unsigned int shiftType = extract_bits(&proc->ir, 5, 2);
    unsigned int rm = extract_bits(&proc->ir, 0, 4);
    unsigned int shiftBy;
    if (fourth_bit == 0) {
      shiftBy = extract_bits(&proc->ir, 7, 5);
    }
    else {
      // fourth_bit == 1
      unsigned int rsNumber = extract_bits(&proc->ir, 8, 4);
      shiftBy = proc->registers[rsNumber];
    }
    // shift using the specified shift type and write result to op2
    offset = shift_by_type(shiftType, proc->registers[rm], shiftBy);
  }

  int sign = up_bit == 1 ? 1 : -1;
  int memory_address = proc->registers[rn];

  if (pre_post_indexing == 1) {
    // Pre-indexing
    memory_address += offset * sign;
  }

  if (memory_address >= MAX_MEMORY_SIZE) {
    printf("Error: Out of bounds memory access at address 0x%08x\n", memory_address);
  } else {

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



/* TODO: create cases to check for the following:

- A post-indexing ldr or str in which Rm is the same register as Rn is not allowed.
- Remember, if the PC is used as the base register (Rn), then your emulator must ensure it contains the instruction’s address plus 8 bytes due to the effects of
  the three stage pipeline.

*/
}
