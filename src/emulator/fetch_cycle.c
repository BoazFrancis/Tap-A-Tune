#include "emulate.h"

void fetch_decode_execute(ARM* proc) {

  // Initialise processor properties
  proc->load = 0;
  proc->ir = 0;

  proc->has_loaded = 0;
  proc->has_fetched = 0;

  while (proc->pc < MAX_MEMORY_SIZE) {

    if (proc->has_fetched != 0) {
      // Halt on all zero instruction
      if (proc->ir == 0) {
        break;
      }
      else if (check_condition_bits(proc)) {
        switch (get_instruction_type(&proc->ir)) {
          case DATA_PROCESSING:       data_processing(proc); break;
          case BRANCH:                branch(proc); break;
          case MULTIPLY:              multiply(proc); break;
          case SINGLE_DATA_TRANSFER:  single_data_transfer(proc); break;
          default:                    fprintf(stderr, "Unknown type\n"); break;
        }
      }
    }

    if (proc->has_loaded != 0) {
      proc->ir = proc->load;
      proc->has_fetched = 1;
    }

    // Get the next instruction and increment PC
    proc->load = proc->memory[memaddr_to_index(proc->pc)];
    proc->has_loaded = 1;
    proc->pc += WORD_SIZE;

  }

}

int check_condition_bits(ARM* proc) {

  // Get the 4 most significant bits which is the "Cond"
  int cond = extract_bits(&proc->ir, COND_START, COND_NUM_BITS);

  unsigned int v = extract_bit(&proc->registers[CPSR_REGISTER], CPSR_V);
  unsigned int c = extract_bit(&proc->registers[CPSR_REGISTER], CPSR_C);
  unsigned int z = extract_bit(&proc->registers[CPSR_REGISTER], CPSR_Z);
  unsigned int n = extract_bit(&proc->registers[CPSR_REGISTER], CPSR_N);

  switch (cond) {
    case Z_SET:                 return z == 1;
    case Z_CLEAR:               return z == 0;
    case N_EQUALS_V:            return n == v;
    case N_NOT_V:               return n != v;
    case Z_CLEAR_N_EQUALS_V:    return z == 0 && n == v;
    case Z_SET_N_NOT_V:         return z == 1 || n != v;
    case AL_FLAG:               return 1;
    default:
    fprintf(stderr, "Unknown condition");
    return 0;
  }

}

enum instruction_type get_instruction_type(int* ir) {

  if (is_bit_set(ir, BRANCH_IDENTIFIER)) {
    return BRANCH;
  }

  if (is_bit_set(ir, SINGLE_DATA_IDENTIFIER)) {
    return SINGLE_DATA_TRANSFER;
  }

  // Either data processing or multiply
  if (is_bit_set(ir, DATA_PROC_IMM_IDENTIFIER)) {
    // Immediate operand set, therefore data processing
    return DATA_PROCESSING;
  }
  else {
    if (is_bit_set(ir, MULT_ID_1) && is_bit_set(ir, MULT_ID_2)) {
      return MULTIPLY;
    }
    return DATA_PROCESSING;
  }

}

int memaddr_to_index(int memaddr) {
  return memaddr / WORD_SIZE;
}

int index_to_memaddr(int index) {
  return index * WORD_SIZE;
}
