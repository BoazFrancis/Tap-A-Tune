#include <stdint.h>
#include "emulate.h"

/**
 * Extracts the part of all data processing instructions
 * and calls the relavant method based on the opcode
 * @param proc - A pointer to the processor
 * @returns void
 */
void data_processing(ARM *proc) {

  // Extract the position of the source and destination register
  unsigned int srcRegPos = extract_bits(proc->ir, DP_SRC_REG, DP_BLOCK_SIZE);
  unsigned int destRegPos = extract_bits(proc->ir, DP_DEST_REG, DP_BLOCK_SIZE);

  // Get the s bit
  unsigned int s = extract_bit(proc->ir, S_BIT);

  // Get value of source register Rn
  int rn = proc->registers[srcRegPos];

  // Declare a variable for operand 2
  uint32_t op2;
  op2 = calculate_op2(proc);

  unsigned int opcode = extract_bits(proc->ir, DP_OPCODE_START, DP_BLOCK_SIZE);

  // Declare an array of function pointers for the methods below
  void (*dp_methods[NUM_DP_INSTRUCTIONS])(ARM*, unsigned int, unsigned int, int, int) = {
  	&do_and, &do_eor, &do_sub, &do_rsb, &do_add, NULL, NULL, NULL,
    &do_tst, &do_teq, &do_cmp, NULL, &do_orr, &do_mov
  };

  // Call the method based on the opcode
  dp_methods[opcode](proc, rn, op2, destRegPos, s);

}

/**
 * Sets the N and Z bit of the CPSR register based on the calculation
 * @param proc - A pointer to the processor
 * @param s - If set to 0, the method doesn't do anything
 * @param result - The result performed by the data processing instruction
 * @returns void
 */
void set_cpsr_nz(ARM *proc, int s, unsigned int result) {
  if (s == 1) {
    set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_N, extract_bit(result, WORD_SIZE*BITS_IN_BYTE-1));
    set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_Z, result == 0);
  }
}

/**
 * Sets the C bit of the CPSR register based on the calculation
 * @param proc - A pointer to the processor
 * @param s - If set to 0, the method doesn't do anything
 * @param c - Either a 1 or 0 based on previous methods
 * @returns void
 */
void set_cpsr_c(ARM *proc, int s, int c) {
  if (s == 1) {
    set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_C, c);
  }
}

/**
 * Process the AND instruction and store the result in dest
 * @param proc - A pointer to the processor
 * @param rn - The source register
 * @param op2 - The operand, either an immediate value or shifted register
 * @param dest - The destination register to store the result
 * @param s - Whether or not to set the CPSR register flags
 * @returns void
 */
void do_and(ARM *proc, unsigned int rn, unsigned int op2, int dest, int s) {
  int result = op2 & rn;
  proc->registers[dest] = result;
  set_cpsr_nz(proc, s, result);
}

/**
 * Process the EOR instruction and store the result in dest
 * @param proc - A pointer to the processor
 * @param rn - The source register
 * @param op2 - The operand, either an immediate value or shifted register
 * @param dest - The destination register to store the result
 * @param s - Whether or not to set the CPSR register flags
 * @returns void
 */
void do_eor(ARM *proc, unsigned int rn, unsigned int op2, int dest, int s) {
  int result = op2 ^ rn;
  proc->registers[dest] = result;
  set_cpsr_nz(proc, s, result);
}

/**
 * Process the SUB instruction and store the result in dest
 * @param proc - A pointer to the processor
 * @param rn - The source register
 * @param op2 - The operand, either an immediate value or shifted register
 * @param dest - The destination register to store the result
 * @param s - Whether or not to set the CPSR register flags
 * @returns void
 */
void do_sub(ARM *proc, unsigned int rn, unsigned int op2, int dest, int s) {
  int result = rn - op2;
  proc->registers[dest] = result;
  do_cmp(proc, rn, op2, dest, s);
}

/**
 * Process the RSB instruction and store the result in dest
 * @param proc - A pointer to the processor
 * @param rn - The source register
 * @param op2 - The operand, either an immediate value or shifted register
 * @param dest - The destination register to store the result
 * @param s - Whether or not to set the CPSR register flags
 * @returns void
 */
void do_rsb(ARM *proc, unsigned int rn, unsigned int op2, int dest, int s) {
  int result = op2 - rn;
  proc->registers[dest] = result;
  set_cpsr_nz(proc, s, result);
  set_cpsr_c(proc, s, rn <= op2);
}

/**
 * Process the ADD instruction and store the result in dest
 * @param proc - A pointer to the processor
 * @param rn - The source register
 * @param op2 - The operand, either an immediate value or shifted register
 * @param dest - The destination register to store the result
 * @param s - Whether or not to set the CPSR register flags
 * @returns void
 */
void do_add(ARM *proc, unsigned int rn, unsigned int op2, int dest, int s) {
  int result = rn + op2;
  proc->registers[dest] = result;
  set_cpsr_nz(proc, s, result);
  if (s == 1) {
    int a = extract_bit(rn, WORD_SIZE*BITS_IN_BYTE-1);
    int b = extract_bit(op2, WORD_SIZE*BITS_IN_BYTE-1);
    int c = extract_bit(proc->registers[dest], WORD_SIZE*BITS_IN_BYTE-1);
    set_bit_to(&proc->registers[CPSR_REGISTER], CPSR_C, (a & b & (!c)));
  }
}

/**
 * Process the TST instruction
 * @param proc - A pointer to the processor
 * @param rn - The source register
 * @param op2 - The operand, either an immediate value or shifted register
 * @param dest - The destination register to store the result
 * @param s - Whether or not to set the CPSR register flags
 * @returns void
 */
void do_tst(ARM *proc, unsigned int rn, unsigned int op2, int dest, int s) {
  set_cpsr_nz(proc, s, op2 & rn);
}

/**
 * Process the TEQ instruction
 * @param proc - A pointer to the processor
 * @param rn - The source register
 * @param op2 - The operand, either an immediate value or shifted register
 * @param dest - The destination register to store the result
 * @param s - Whether or not to set the CPSR register flags
 * @returns void
 */
void do_teq(ARM *proc, unsigned int rn, unsigned int op2, int dest, int s) {
  set_cpsr_nz(proc, s, op2 ^ rn);
}

/**
 * Process the CMP instruction
 * @param proc - A pointer to the processor
 * @param rn - The source register
 * @param op2 - The operand, either an immediate value or shifted register
 * @param dest - The destination register to store the result
 * @param s - Whether or not to set the CPSR register flags
 * @returns void
 */
void do_cmp(ARM *proc, unsigned int rn, unsigned int op2, int dest, int s) {
  set_cpsr_nz(proc, s, rn - op2);
  set_cpsr_c(proc, s, rn >= op2);
}

/**
 * Process the ORR instruction and store the result in dest
 * @param proc - A pointer to the processor
 * @param rn - The source register
 * @param op2 - The operand, either an immediate value or shifted register
 * @param dest - The destination register to store the result
 * @param s - Whether or not to set the CPSR register flags
 * @returns void
 */
void do_orr(ARM *proc, unsigned int rn, unsigned int op2, int dest, int s) {
  int result = rn | op2;
  proc->registers[dest] = result;
  set_cpsr_nz(proc, s, result);
}

/**
 * Process the MOV instruction and store the result in dest
 * @param proc - A pointer to the processor
 * @param rn - The source register
 * @param op2 - The operand, either an immediate value or shifted register
 * @param dest - The destination register to store the result
 * @param s - Whether or not to set the CPSR register flags
 * @returns void
 */
void do_mov(ARM *proc, unsigned int rn, unsigned int op2, int dest, int s) {
  int result = op2;
  proc->registers[dest] = result;
  set_cpsr_nz(proc, s, result);
}
