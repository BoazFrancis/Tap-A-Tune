#include "assemble.h"

/**
 * Obtains the ldr instruction for the constant case
 * @param instruction - A pointer to the instruction
 * @param instruction_addr - The address in memory that this instruction will be stored in
 * @param num_no_labels - A pointer to the number of instructions without labels
 * @param memory - A pointer to the array of memory
 * @param rd_str - Destination register (Rd) string
 * @param addr_str - Address specification string
 * @returns the instruction
*/
int do_ldr_constant(int* instruction, int instruction_addr, int* num_no_labels, int** memory, char* rd_str, char* addr_str) {
  // Set the offset
  int mem_val = strtol(addr_str+1, NULL, 0);

  if (mem_val < 0xFF) {
    char* without_eq = addr_str + 1;
    char* mov_param = cat(rd_str, ",#", without_eq);
    return do_mov(mov_param);
  }
  else {

    int store_addr = *num_no_labels * WORD_SIZE;
    int offset = store_addr - instruction_addr - BRANCH_PIPELINE_OFFSET;
    set_bit(instruction, SDT_PREPOST);

    // Set Rn to the PC
    unsigned int rn = PC_REG << SDT_RN;

    // Save mem_val
    (*memory)[*num_no_labels] = mem_val;
    (*num_no_labels)++;

    return *instruction | rn | offset;
  }
}

/**
* Writes the instruction for the shifted register case in Single Data Transfer
* @param instruction - An int pointer to the instruction
* @param offset_str - An offset string
*/
void sdt_shifted_register(int* instruction, char* offset_str) {

  char* rm_str;
  char* shifter;
  //Declare the shift register (Rs)
  unsigned int rm = 0;

  // Set the I (25th) bit
  set_bit(instruction, SDT_IMM_IDENTIFIER);

  // offset string is in the form of "{+/-}r2{, lsr <shift>}"
  // where shift is either an immediate or a register

  //check for the comma
  rm_str = strtok_r(offset_str, ",", &offset_str);

  if (rm_str[0] == '-') {
    // there is a minus
    // clear the U (23rd) bit
    clear_bit(instruction, SDT_UP_BIT);
    // obtain the rm by skipping the "-r"
    // Get the register Rm (Bits 0 - 3)
    rm = strtol(rm_str+2, NULL, 0);
  }
  else {
    // there is no minus
    // obtain the rm by skipping the "r"
    // Get the register Rm (Bits 0 - 3)
    rm = strtol(rm_str+1, NULL, 0);
  }

  if (offset_str != NULL) {
    check_shift(instruction, offset_str);
  }

  *instruction |= rm;

}

/**
* Returns the instruction for the register case in Single Data Transfer
* @param instruction - Instruction up to this point
* @param cond - Condition field of the SDT instruction
* @param rd - Destination register (Rd) field of the SDT instruction
* @param addr_str - Address specification string
* @return completed instruction
*/
int do_sdt_reg(unsigned int instruction, unsigned int cond, unsigned int rd, char* addr_str) {

  // Declare the pointer that checks for the comma - used later on
  char* is_comma;

  char* rn_string;
  unsigned int rn;

  char* offset_str;
  unsigned int offset = 0;

  if (addr_str[strlen(addr_str)-1] == ']') {
    // Pre indexed
    // Hence the P bit (24) is set
    set_bit(&instruction, SDT_PREPOST);
    // Strip end bracket
    addr_str[strlen(addr_str)-1] = '\0';
    is_comma = strpbrk(addr_str, ",");
    if (is_comma == NULL) {
      // there is no comma in addr_str, i.e. there is NO offset
      // get Rn (note that addr_str is "[r10", for example
      // since the end bracket is stripped and we just need the 10)
      rn = strtol(addr_str+2, NULL, 0) << SDT_RN;
    }
    else {
      // There is a comma in addr_str
      rn_string = strtok_r(addr_str, ",", &offset_str);
      // rn_string starts with "r.."" and we just need what follows "r"
      rn = strtol(rn_string+2, NULL, 0) << SDT_RN;

      //trim whitespace after the comma if there is one
      offset_str = trim_whitespace(offset_str);

      if (offset_str[0] == '#') {
        //offset is an immediate value
        // Leave the I (25th) bit
        get_offset(&instruction, offset_str, &offset);
      }
      else {
        // offset is a shifted register
        sdt_shifted_register(&instruction, offset_str);
      }
    }
  }
  else {
    // Post indexed
    // Hence the P bit (24th) is not set;
    // get the Rn string in the form of e.g. "[r10]"
    rn_string = strtok_r(addr_str, ",", &offset_str);

    //get rid of the closing bracket
    rn_string[strlen(rn_string)-1] = 0;

    //get rid of the opening bracket and 'r'
    rn = strtol(rn_string+2, NULL, 0) << SDT_RN;

    if (offset_str[0] == '#') {
      // offset is an immediate value
      // the I bit is NOT set
      get_offset(&instruction, offset_str, &offset);
    }
    else {
      // offset is a shifted register
      sdt_shifted_register(&instruction, offset_str);
    }
  }

  instruction |= cond | rn | rd | offset;
  return instruction;
}

/**
* Writes the offset to the offset field of the instruction
* @param instruction - A pointer to the instruction
* @param offset_str - An offset string (from command line)
* @param offset - A pointer to the offset field of the instruction
*/
void get_offset(int* instruction, char* offset_str, int* offset) {
  if (offset_str[1] == '-') {
    // Negative therefore clear U (23rd) bit
    clear_bit(instruction, SDT_UP_BIT);
    *offset = strtol(offset_str+2, NULL, 0);
  }
  else {
    // Positive, U bit set by default
    *offset = strtol(offset_str+1, NULL, 0);
  }
}
