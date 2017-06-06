#include "assemble.h"

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
  set_bit(instruction, 25);

  // offset string is in the form of "{+/-}r2{, lsr <shift>}"
  // where shift is either an immediate or a register

  //check for the comma
  rm_str = strtok_r(offset_str, ",", &offset_str);

  if (rm_str[0] == '-') {
    // there is a minus
    // clear the U (23rd) bit
    clear_bit(instruction, 23);
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
