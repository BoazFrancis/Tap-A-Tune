#include "assemble.h"

#define IS_LDR 1
#define NOT_LDR 0

/**
 * Obtains ldr instruction
 * @param params - 
 * @param instruction_addr
 * @param num_no_labels
 * @param memory
 * @returns the instruction
*/
int do_ldr(char* params, int instruction_addr, int* num_no_labels, int** memory) {
  do_sdt(params, instruction_addr, num_no_labels, memory, IS_LDR);
}

/**
 * Obtains str instruction
 * @param params
 * @param instruction_addr
 * @param num_no_labels
 * @param memory
 * @returns the instruction
*/
int do_str(char* params, int instruction_addr, int* num_no_labels, int** memory) {
  do_sdt(params, instruction_addr, num_no_labels, memory, NOT_LDR);
}
