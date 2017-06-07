#include "assemble.h"

/**
 * Process generic branch instructions
 * @param params - A pointer to the processor
 * @param st - A pointer to the symbol table
 * @param cond - The condition which depends on the specific instruction (see below)
 * @returns the 32-bit instruction
 */
int do_branch(char* params, SymbolTable* st, int addr, unsigned int cond) {

  // Get the jump address by looking up the label in the symbol table
  unsigned int jump_addr = get_address(st, trim_whitespace(params)) - addr - BRANCH_PIPELINE_OFFSET;
  jump_addr >>= BRANCH_SHIFT;

  // Set bits 27 and 25
  unsigned int instruction = extract_bits(&jump_addr, BRANCH_OFFSET_START, BRANCH_OFFSET_LEN);
  set_bit(&instruction, BRANCH_IDENTIFIER);
  set_bit(&instruction, BRANCH_IDENTIFIER_2);

  return instruction | cond;

}

/**
 * Process the BEQ instruction
 * @param params - A pointer to the processor
 * @param st - A pointer to the symbol table
 * @param addr - The address of this instruction to be stored in memory
 * @returns the 32-bit instruction
 */
int do_beq(char* params, SymbolTable* st, int addr) {
  return do_branch(params, st, addr, Z_SET << COND_START);
}

/**
 * Process the BNE instruction
 * @param params - A pointer to the processor
 * @param st - A pointer to the symbol table
 * @param addr - The address of this instruction to be stored in memory
 * @returns the 32-bit instruction
 */
int do_bne(char* params, SymbolTable* st, int addr) {
  return do_branch(params, st, addr, Z_CLEAR << COND_START);
}

/**
 * Process the BGE instruction
 * @param params - A pointer to the processor
 * @param st - A pointer to the symbol table
 * @param addr - The address of this instruction to be stored in memory
 * @returns the 32-bit instruction
 */
int do_bge(char* params, SymbolTable* st, int count) {
  return do_branch(params, st, count, N_EQUALS_V << COND_START);
}

/**
 * Process the BLT instruction
 * @param params - A pointer to the processor
 * @param st - A pointer to the symbol table
 * @param addr - The address of this instruction to be stored in memory
 * @returns the 32-bit instruction
 */
int do_blt(char* params, SymbolTable* st, int addr) {
  return do_branch(params, st, addr, N_NOT_V << COND_START);
}

/**
 * Process the BGT instruction
 * @param params - A pointer to the processor
 * @param st - A pointer to the symbol table
 * @param addr - The address of this instruction to be stored in memory
 * @returns the 32-bit instruction
 */
int do_bgt(char* params, SymbolTable* st, int addr) {
  return do_branch(params, st, addr, Z_CLEAR_N_EQUALS_V << COND_START);
}

/**
 * Process the BLE instruction
 * @param params - A pointer to the processor
 * @param st - A pointer to the symbol table
 * @param addr - The address of this instruction to be stored in memory
 * @returns the 32-bit instruction
 */
int do_ble(char* params, SymbolTable* st, int addr) {
  return do_branch(params, st, addr, Z_SET_N_NOT_V << COND_START);
}

/**
 * Process the B instruction
 * @param params - A pointer to the processor
 * @param st - A pointer to the symbol table
 * @param addr - The address of this instruction to be stored in memory
 * @returns the 32-bit instruction
 */
int do_b(char* params, SymbolTable* st, int addr) {
  return do_branch(params, st, addr, AL_FLAG << COND_START);
}
