#include <stdio.h>
#include <stdint.h>
#include "emulate.h"

/**
* Executes the data processing instructions
* @param ir - The pointer to the instruction register
*/
void data_processing(struct ARM* proc) {

  // Extract the position of the source and destination register
  unsigned int srcRegPos = extract_bits(&proc->ir, 16, 4);
  unsigned int destRegPos = extract_bits(&proc->ir, 12, 4);

  // Get value of source register Rn
  int rn = proc->registers[srcRegPos];

  // Declare a variable for operand 2
  uint32_t op2;

  // if the operand2 is an immediate value
  if (extract_bit(&proc->ir, DATA_PROC_IMM_IDENTIFIER) == 1) {
    op2 = extract_bits(&proc->ir, 0, 8);
    op2 = rotate_right(op2, 2*extract_bits(&proc->ir, 8, 4));
  }
  else {
    // operand2 is a register
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
    op2 = shift_by_type(shiftType, proc->registers[rm], shiftBy);
  }

  unsigned int opcode = extract_bits(&proc->ir, 21, 4);
  unsigned int s = extract_bit(&proc->ir, 20);

  switch (opcode) {
    case AND:
      proc->registers[destRegPos] = op2 & rn;
      // If S bit is set
      if (s == 1) {
        // Set N flag to 1 if result is negative, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_N, proc->registers[destRegPos]<0);
        // Set Z flag to 1 if result is equal to zero, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_Z, proc->registers[destRegPos]==0);
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_C, 0);
      }
      break;
    case EOR:
      proc->registers[destRegPos] = op2 ^ rn;
      // If S bit is set
      if (s == 1) {
        // Set N flag to 1 if result is negative, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_N, proc->registers[destRegPos]<0);
        // Set Z flag to 1 if result is equal to zero, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_Z, proc->registers[destRegPos]==0);
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_C, 0);
      }
      break;
    case SUB:
      proc->registers[destRegPos] = rn - op2;
      // If S bit is set
      if (s == 1) {
        signed int subResult = rn - op2;
        // Set N flag to bit 31
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_N, extract_bit(&subResult, CPSR_N));
        // Set Z flag to 1 if result is equal to zero, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_Z, subResult==0);
        // Set C flag to 1 carry is 1, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_C, rn>=op2);
      }
      break;
    case RSB:
      proc->registers[destRegPos] = op2 - rn;
      // If S bit is set
      if (s == 1) {
        // Set N flag to 1 if result is negative, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_N, proc->registers[destRegPos]<0);
        // Set Z flag to 1 if result is equal to zero, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_Z, proc->registers[destRegPos] == 0);
        // Set C flag to 1 carry is 1, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_C, 0);//TODO: check for carry
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
        // Set C flag to 1 carry is 1, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_C, 0); //TODO: check for carry
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
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_C, 0);
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
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_C, 0);
      }
      break;
    case CMP:
      // If S bit is set
      if (s == 1) {
        signed int subResult = rn - op2;
        // Set N flag to bit 31
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_N, extract_bit(&subResult, CPSR_N));
        // Set Z flag to 1 if result is equal to zero, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_Z, subResult==0);
        // Set C flag to 1 carry is 1, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_C, rn>=op2);
      }
      break;
    case ORR:
      proc->registers[destRegPos] = rn | op2;
      // If S bit is set
      if (s == 1) {
        // Set N flag to 1 if result is negative, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_N, proc->registers[destRegPos]<0);
        // Set Z flag to 1 if result is equal to zero, 0 otherwise
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_Z, proc->registers[destRegPos]==0);
        set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_C, 0);
      }
      break;
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
