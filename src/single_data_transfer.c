#include <stdio.h>
#include "emulate.h"

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

  if (pre_post_indexing == 1) {
    // Pre-indexing
  }

  signed int memory_address;
  if (up_bit == 1) {
    memory_address = proc->registers[rn] + offset;
  }
  else {
    memory_address = proc->registers[rn] - offset;
  }

  if (pre_post_indexing == 0) {
    // Post-indexing
  }

  if (load_store_bit == 1) {
    // To load
    proc->registers[rd] = proc->memory[memaddr_to_index(memory_address)];
  }
  else {
    // To store
    proc->memory[memaddr_to_index(memory_address)] = proc->registers[rd];
  }

}
