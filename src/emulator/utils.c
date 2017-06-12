#include "emulate.h"

/**
 * Calculate the operand for data processing instructions
 * by either rotate an immediate value or shifting a registers
 * @param proc - The pointer to the processor
 * @returns the 32-bit operand
 */
int calculate_op2(ARM *proc) {

  // If the operand2 is an immediate value
  if (extract_bit(proc->ir, DATA_PROC_IMM_IDENTIFIER) == 1) {
    int op2 = extract_bits(proc->ir, OP2_START, OP2_SIZE);
    return rotate_right(op2, 2*extract_bits(proc->ir, OP2_IMMEDIATE_START, OP2_IMMEDIATE_SIZE));
  }
  else {

    // operand2 is a register
    unsigned int shiftBy;

    if (is_bit_set(&proc->ir, OP2_SHIFYBY_IDENTIFIER)) {
      unsigned int rsNumber = extract_bits(proc->ir, OP2_RS_START, OP2_RS_SIZE);
      shiftBy = proc->registers[rsNumber] & 0xFF;
    }
    else {
      shiftBy = extract_bits(proc->ir, OP2_SHIFT_START, OP2_SHIFT_SIZE);
    }

    // Return the result of the barrel shifter
    return barrel_shifter(proc, shiftBy);

  }

}

/**
 * The barrel shifter shifts the operand by an appropriate amount
 * using the shift type.
 * After shifting, any carry bits set the CSPR register flags
 * @param proc - A pointer to the processor
 * @param shiftBy - the number of bits to shift
 * @returns the shifted register Rm
 */
int barrel_shifter(ARM *proc, int shiftBy) {

  unsigned int shiftType = extract_bits(proc->ir, 5, 2);
  unsigned int rm = extract_bits(proc->ir, 0, 4);
  unsigned int s = extract_bit(proc->ir, 20);

  // Setup the result variable
  int r = 0;

  switch (shiftType) {

    case LOGICAL_LEFT:
      r = proc->registers[rm] << shiftBy;
      if (s) {
        int c = (shiftBy == 0) ? 0 : extract_bit(proc->registers[rm], WORD_SIZE*BITS_IN_BYTE - shiftBy);
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
    int c = (shiftBy == 0) ? 0 : extract_bit(proc->registers[rm], shiftBy - 1);
    set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_C, c);
  }

  return r;

}

/**
 * Converts a memory address to an array index
 * as each entry in the array stores 4 bytes
 * @param memaddr - The memory address
 * @returns the index in the memory array
 */
int memaddr_to_index(int memaddr) {
  return memaddr / WORD_SIZE;
}

/**
 * Converts a memory index to physical address
 * as each entry in the array stores 4 bytes
 * @param imdex - The memory index
 * @returns the physical address
 */
int index_to_memaddr(int index) {
  return index * WORD_SIZE;
}

/**
 * Read a 32-bit number from the given memory address
 * taking into account unaligned access
 * @param proc - The pointer to the processor
 * @param addr - The byte address to start reading from
 * @returns the 32-bit unsigned number
 */
int read_memory_bytes(ARM *proc, unsigned int addr) {

  int mod = addr % WORD_SIZE;
  int start_addr = addr / WORD_SIZE;

  int start_bit = mod * BITS_IN_BYTE;

  // Find the number of bits left in the next row in the array
  int bits_remaining = WORD_SIZE * BITS_IN_BYTE - start_bit;

  // Extract the bytes on the first row (if unaligned)
  int extracted_first = extract_bits(proc->memory[start_addr], start_bit, bits_remaining);

  // If unaligned, there are still bytes to read from the second row
  int extracted_second = extract_bits(proc->memory[start_addr+1], 0, start_bit);
  int new_second = extracted_second << bits_remaining;

  // Or both together
  return extracted_first | new_second;

}

/**
 * Write  a 32-bit number into a given memory address
 * taking into account unaligned access
 * @param proc - The pointer to the processor
 * @param addr - The byte address to start writing to
 * @returns void
 */
void write_memory_bytes(ARM *proc, unsigned int data, unsigned int addr) {

  unsigned int mod = addr % WORD_SIZE;
  unsigned int start_addr = addr / WORD_SIZE;
  unsigned int end_bit = mod * BITS_IN_BYTE;

  unsigned int bits_remaining = WORD_SIZE * BITS_IN_BYTE - end_bit;

  // Shift the bytes which will be written on the first line
  unsigned int lsb_data = extract_bits(data, 0, bits_remaining);
  unsigned int lower_memory = extract_bits(proc->memory[start_addr], 0, end_bit);

  // Shift the bytes which will be written on the second line
  unsigned int new_lower_mem = lower_memory | (lsb_data << end_bit);
  unsigned int higher_memory = extract_bits(proc->memory[start_addr+1], end_bit, bits_remaining);
  unsigned int msb_data = extract_bits(data, bits_remaining, end_bit);
  unsigned int new_higher_mem = msb_data | (higher_memory << end_bit);

  // Write to memory
  proc->memory[start_addr] = new_lower_mem;
  proc->memory[start_addr+1] = new_higher_mem;

}
