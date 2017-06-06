#include "assemble.h"

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
    set_bit(&instruction, 24);
    // Strip end bracket
    addr_str[strlen(addr_str)-1] = '\0';
    is_comma = strpbrk(addr_str, ",");
    if (is_comma == NULL) {
      // there is no comma in addr_str, i.e. there is NO offset
      // get Rn (note that addr_str is "[r10", for example
      // since the end bracket is stripped and we just need the 10)
      rn = strtol(addr_str+2, NULL, 0) << 16;
    }
    else {
      // There is a comma in addr_str
      rn_string = strtok_r(addr_str, ",", &offset_str);
      // rn_string starts with "r.."" and we just need what follows "r"
      rn = strtol(rn_string+2, NULL, 0) << 16;

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
    rn = strtol(rn_string+2, NULL, 0) << 16;

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

void get_offset(int* instruction, char* offset_str, int* offset) {
  if (offset_str[1] == '-') {
    // Negative therefore clear U (23rd) bit
    clear_bit(instruction, 23);
    *offset = strtol(offset_str+2, NULL, 0);
  }
  else {
    // Positive, U bit set by default
    *offset = strtol(offset_str+1, NULL, 0);
  }
}
