#include <stdint.h>
#include "emulate.h"

void do_and(ARM* proc, int rn, unsigned int op2, int reg, int s) {
  store_result(proc, op2 & rn, &proc->registers[reg], s);
}

void do_eor(ARM* proc, int rn, unsigned int op2, int reg, int s) {
  store_result(proc, op2 ^ rn, &proc->registers[reg], s);
}

void do_sub(ARM* proc, int rn, unsigned int op2, int reg, int s) {
  store_result(proc, rn - op2, &proc->registers[reg], s);
  set_cpsr_c(proc, s, rn >= op2);
}

void store_result(ARM* proc, int result, int* dest, int s) {
  *dest = result;
  set_cpsr_nz(proc, s, result);
}

void set_cpsr_nz(ARM* proc, int s, int result) {
  if (s == 1) {
    set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_N, extract_bit(&result, WORD_SIZE*BITS_IN_BYTE-1));
    set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_Z, result == 0);
  }
}

void set_cpsr_c(ARM* proc, int s, int c) {
  if (s == 1) {
    set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_C, c);
  }
}


/**
* Executes the data processing instructions
* @param ir - The pointer to the instruction register
*/
void data_processing(ARM* proc) {

  // Extract the position of the source and destination register
  unsigned int srcRegPos = extract_bits(&proc->ir, 16, 4);
  unsigned int destRegPos = extract_bits(&proc->ir, 12, 4);

  unsigned int s = extract_bit(&proc->ir, 20);

  // Get value of source register Rn
  int rn = proc->registers[srcRegPos];

  // Declare a variable for operand 2
  uint32_t op2;
  op2 = calculate_op2(proc);

  unsigned int opcode = extract_bits(&proc->ir, 21, 4);

  switch (opcode) {
    case AND: do_and(proc, rn, op2, destRegPos, s); break;
    case EOR: do_eor(proc, rn, op2, destRegPos, s); break;
    case SUB:
      do_sub(proc, rn, op2, destRegPos, s); break;
      /*proc->registers[destRegPos] = rn - op2;
      // If S bit is set
      if (s == 1) {
        int subResult = rn - op2;
        // Set N flag to bit 31
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_N, extract_bit(&subResult, WORD_SIZE*BITS_IN_BYTE-1));
        // Set Z flag to 1 if result is equal to zero, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_Z, subResult==0);
        // Set C flag to 1 carry is 1, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_C, rn >= op2);
      }
      break;*/
    case RSB:
      proc->registers[destRegPos] = op2 - rn;
      // If S bit is set
      if (s == 1) {
        signed int subResult = op2 - rn;
        // Set N flag to 1 if result is negative, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_N, extract_bit(&subResult, WORD_SIZE*BITS_IN_BYTE-1));
        // Set Z flag to 1 if result is equal to zero, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_Z, proc->registers[destRegPos] == 0);
        // Set C flag to 1 carry is 1, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_C, rn <= op2);
      }
      break;
    case ADD:
      proc->registers[destRegPos] = rn + op2;
      // If S bit is set
      if (s == 1) {
        // Set N flag to 1 if result is negative, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_N, proc->registers[destRegPos]<0);
        // Set Z flag to 1 if result is equal to zero, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_Z, proc->registers[destRegPos]==0);
        // Set CFLAG
    		int a = extract_bit(&rn, WORD_SIZE*BITS_IN_BYTE-1);
    		int b = extract_bit(&op2, WORD_SIZE*BITS_IN_BYTE-1);
    		int c = extract_bit(&proc->registers[destRegPos], WORD_SIZE*BITS_IN_BYTE-1);
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_C, ((!a) & (!b) & c) | (a & b & (!c)));
      }
      break;
    case TST:
      // If S bit is set
      if (s == 1) {
        unsigned int andResult = op2 & rn;
        // Set N flag to 1 if result is negative, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_N, andResult<0);
        // Set Z flag to 1 if result is equal to zero, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_Z, andResult==0);
      }
      break;
    case TEQ:
      // If S bit is set
      if (s == 1) {
        unsigned int eorResult = op2 ^ rn;
        // Set N flag to 1 if result is negative, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_N, eorResult < 0);
        // Set Z flag to 1 if result is equal to zero, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_Z, eorResult == 0);
      }
      break;
    case CMP:
      // If S bit is set
      if (s == 1) {
        signed int subResult = rn - op2;
        // Set N flag to bit 31
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_N, extract_bit(&subResult, WORD_SIZE*BITS_IN_BYTE-1));
        // Set Z flag to 1 if result is equal to zero, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_Z, subResult==0);
        // Set C flag to 1 carry is 1, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_C, rn >= op2);
      }
      break;
    case ORR: {
      int r = rn | op2;
      proc->registers[destRegPos] = r;
      // If S bit is set
      if (s == 1) {
        // Set N flag to 1 if result is negative, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_N, extract_bit(&r, WORD_SIZE*BITS_IN_BYTE-1));
        // Set Z flag to 1 if result is equal to zero, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_Z, r==0);
      }
      break;
    }
    case MOV:
      proc->registers[destRegPos] = op2;
      // If S bit is set
      if (s == 1) {
        // Set N flag to 1 if result is negative, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_N, proc->registers[destRegPos]<0);
        // Set Z flag to 1 if result is equal to zero, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_Z, proc->registers[destRegPos]==0);
      }
      break;
  }
}
