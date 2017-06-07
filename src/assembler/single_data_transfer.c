#include "assemble.h"

/**
 * Obtains ldr instruction
 * @param params - The string of parameters for this instruction
 * @param instruction_addr - The address in memory that this instruction will be stored in
 * @param num_no_labels - A pointer to the number of instructions without labels
 * @param memory - A pointer to the array of memory
 * @returns the instruction
*/
int do_ldr(char* params, int instruction_addr, int* num_no_labels, int** memory) {
  return do_sdt(params, instruction_addr, num_no_labels, memory, LDR);
}

/**
* Obtains str instruction
* @param params - The string of parameters for this instruction
* @param instruction_addr - The address in memory that this instruction will be stored in
* @param num_no_labels - A pointer to the number of instructions without labels
* @param memory - A pointer to the array of memory
* @returns the instruction
*/
int do_str(char* params, int instruction_addr, int* num_no_labels, int** memory) {
  return do_sdt(params, instruction_addr, num_no_labels, memory, STR);
}

/**
 * Obtains Single Data Transfer instruction
 * @param params - The string of parameters for this instruction
 * @param instruction_addr - The address in memory that this instruction will be stored in
 * @param num_no_labels - A pointer to the number of instructions without labels
 * @param memory - A pointer to the array of memory
 * @param is_ldr - An integer that corresponds to the type of sdt instruction (ldr = 1, str = 0)
 * @returns the instruction
 */
int do_sdt(char* params, int instruction_addr, int* num_no_labels, int** memory, int is_ldr) {

  unsigned int instruction = 0;
  char* rd_str;
  char* addr_str;
  unsigned int rd = 0;
  unsigned int cond = AL_FLAG << 28;

  // 26th bit is always set to 1 for sdt
  set_bit((int*)&instruction, SINGLE_DATA_IDENTIFIER);

  // Set U (23rd) bit by default - clear it if necessary
  set_bit((int*)&instruction, SDT_UP_BIT);

  // get the Rd string (e.g. r3) by splitting by the comma
  rd_str = strtok_r(params, ",", &addr_str);

  // get the Rd register number
  rd = strtol(rd_str+1, NULL, 0) << SDT_RD;

  //trim the whitespace after the comma if there is one
  addr_str = trim_whitespace(addr_str);

  if (is_ldr == 1) {
    // ldr instruction
    // L bit is set for ldr (bit 20)
    set_bit((int*)&instruction, LOAD_STORE_BIT);

    if (addr_str[0] == '=') {
      // if constant
      instruction |= cond | rd;
      return do_ldr_constant((int*)&instruction, instruction_addr, num_no_labels, memory, rd_str, addr_str);
    }
    else {
      // Register
      return do_sdt_reg(instruction, cond, rd, addr_str);
    }
  }
  else {
    // str instruction
    // L bit is NOT set for str (bit 20)
    return do_sdt_reg(instruction, cond, rd, addr_str);
  }
}
