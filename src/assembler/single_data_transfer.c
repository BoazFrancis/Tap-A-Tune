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
  do_sdt(params, instruction_addr, num_no_labels, memory, LDR);
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
  do_sdt(params, instruction_addr, num_no_labels, memory, STR);
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
  char* rn_string;
  char* rd_str;
  char* addr_str;
  char* offset_str;

  unsigned int rn = 0;
  unsigned int rd = 0;
  unsigned int offset = 0;

  unsigned int cond = 14 << 28;

  // 26th bit is always set to 1 for sdt
  set_bit(&instruction, 26);

  // Set U (23rd) bit by default - clear it if necessary
  set_bit(&instruction, 23);

  // get the Rd string (e.g. r3) by splitting by the comma
  rd_str = strtok_r(params, ",", &addr_str);

  // get the Rd register number
  rd = strtol(rd_str+1, NULL, 0) << 12;

  //trim the whitespace after the comma if there is one
  addr_str = trim_whitespace(addr_str);

  if (is_ldr == 1) {
    // ldr instruction
    // L bit is set for ldr (bit 20)
    set_bit(&instruction, 20);

    if (addr_str[0] == '=') {
      // if constant
      do_ldr_constant(&instruction, instruction_addr, num_no_labels, memory, rd_str, addr_str, rd, cond);
    }
    else {
      // Register
      do_sdt_reg(instruction, cond, rd, addr_str);
    }
  }
  else {
    // str instruction
    // L bit is NOT set for str (bit 20)
    do_sdt_reg(instruction, cond, rd, addr_str);
  }
}
