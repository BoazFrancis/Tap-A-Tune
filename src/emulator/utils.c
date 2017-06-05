#include "emulate.h"

int calculate_op2(ARM* proc) {

  // if the operand2 is an immediate value
  if (extract_bit(&proc->ir, DATA_PROC_IMM_IDENTIFIER) == 1) {
    int op2 = extract_bits(&proc->ir, 0, 8);
    return rotate_right(op2, 2*extract_bits(&proc->ir, 8, 4));
  }
  else {

    // operand2 is a register
    unsigned int shiftBy;

    if (is_bit_set(&proc->ir, 4)) {
      unsigned int rsNumber = extract_bits(&proc->ir, 8, 4);
      shiftBy = proc->registers[rsNumber] & 0xFF;
    }
    else {
      shiftBy = extract_bits(&proc->ir, 7, 5);
    }

    // Return the result of the barrel shifter
    return barrel_shifter(proc, shiftBy);

  }

}

int barrel_shifter(ARM* proc, int shiftBy) {

  unsigned int shiftType = extract_bits(&proc->ir, 5, 2);
  unsigned int rm = extract_bits(&proc->ir, 0, 4);
  unsigned int s = extract_bit(&proc->ir, 20);

  // Setup the result variable
  int r = 0;

  switch (shiftType) {

    case LOGICAL_LEFT:
      r = proc->registers[rm] << shiftBy;
      if (s) {
				int c = (shiftBy == 0) ? 0 : extract_bit(&proc->registers[rm], WORD_SIZE*BITS_IN_BYTE - shiftBy);
				set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_C, c);
			}
      return r;

    case LOGICAL_RIGHT:
      r = proc->registers[rm] >> shiftBy;
      break;

    case ARITHMETIC_RIGHT:
      r = proc->registers[rm] >> shiftBy;
      break;

    case ROTATE_RIGHT:
      r = rotate_right(proc->registers[rm], shiftBy);
      break;

  }

  // Set C flag for logical right, arithmetic right and rotate right
  if (s) {
    int c = (shiftBy == 0) ? 0 : extract_bit(&proc->registers[rm], shiftBy - 1);
    set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_C, c);
  }

  return r;

}

int memaddr_to_index(int memaddr) {
  return memaddr / WORD_SIZE;
}

int index_to_memaddr(int index) {
  return index * WORD_SIZE;
}

unsigned int read_memory_bytes(ARM* proc, unsigned int addr) {
  unsigned int mod = addr % WORD_SIZE;
  unsigned int start_addr = addr / WORD_SIZE;
  unsigned int start_bit = mod * BITS_IN_BYTE;
  unsigned int bits_remaining = WORD_SIZE * BITS_IN_BYTE - start_bit;
  unsigned int extracted_first = extract_bits(&proc->memory[start_addr], start_bit, bits_remaining);
  unsigned int extracted_second = extract_bits(&proc->memory[start_addr+1], 0, start_bit);
  unsigned int new_second = extracted_second << bits_remaining;
  return extracted_first | new_second;
}

void write_memory_bytes(ARM* proc, unsigned int data, unsigned int addr) {
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
