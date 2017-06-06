#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assemble.h"

int do_ldr_reg(unsigned int instruction, unsigned int cond, unsigned int rd, char* addr_str) {
  // Register

  //Declare the pointer that checks for the comma - used later on
  char* is_comma;

  char* rn_string;
  unsigned int rn;

  char* offset_str;
  unsigned int offset;

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

      // since there is no offset we leave the U (23) and I (25) bits


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
        if (offset_str[1] == '-') {
          // Negative therefore clear U (23rd) bit
          clear_bit(&instruction, 23);
          // Get
          offset = strtol(offset_str+2, NULL, 0);
        } else {
          // Positive, U bit set by default
          offset = strtol(offset_str+1, NULL, 0);
        }
      } else {
        // offset is a shifted register
        // - THIS CASE IS OPTIONAL

        char* rm_str;
        //Declare the shift register (Rs)
        unsigned int rm = 0;

        // Set the I (25th) bit
        set_bit(&instruction, 25);

        // offset string is in the form of "{+/-}r2{, lsr <shift>}"
        // where shift is either an immediate or a register

        //check for the comma
        is_comma = strpbrk(offset_str, ",");
        if (is_comma == NULL) {
          // there is no comma
          // offset string is in the form of "{+/-}r2"
          // check for the minus
          if (offset_str[0] == '-') {
            // there is a minus
            // clear the U (23rd) bit
            clear_bit(&instruction, 23);
            // obtain the rm by skipping the "-r"
            // Get the register Rm (Bits 0 - 3)
            rm = strtol(offset_str+2, NULL, 0);
          } else {
            // there is no minus
            // obtain the rm by skipping the "r"
            // Get the register Rm (Bits 0 - 3)
            rm = strtol(offset_str+1, NULL, 0);
          }

          // or offset with rm - leaving the shift (bits 4-11) clear
          offset |= rm;
        } else {
          // There is a comma
          // therefore we need to split by the comma

          rm_str = strtok_r(offset_str, ",", &offset_str);
          if (rm_str[0] == '-') {
            // there is a minus
            // clear the U (23rd) bit
            clear_bit(&instruction, 23);
            // obtain the rm by skipping the "-r"
            // Get the register Rm (Bits 0 - 3)
            rm = strtol(rm_str+2, NULL, 0);
          } else {
            // there is no minus
            // obtain the rm by skipping the "r"
            // Get the register Rm (Bits 0 - 3)
            rm = strtol(rm_str+1, NULL, 0);
          }

          char* shift_type_str;
          //now split by the space to get the shift type
          shift_type_str = strtok_r(offset_str, " ", &offset_str);

          // shift type is lsl by default
          unsigned int shift_type = 0;
          if (!strcmp(shift_type_str, "lsl")) {shift_type << 5;}
          if (!strcmp(shift_type_str, "lsr")) {shift_type = 1 << 5;}
          if (!strcmp(shift_type_str, "asr")) {shift_type = 2 << 5;}
          if (!strcmp(shift_type_str, "ror")) {shift_type = 3 << 5;}

          offset |= rm | shift_type;
          // now offset_str = shift (either register or a constant amount)
          if (offset_str[0] == '#') {
            // shift = constant amount
            // leave 4th bitsr #2"

            // or offset with the constant (bits 7 - 11)
            offset |= strtol(offset_str+1, NULL, 0) << 7;
          } else {
            // shift = register
            // set 4th bit
            set_bit(&offset, 4);

            // bit 7 is zero
            // or offset with the shift register (Rs) number
            offset |= strtol(offset_str+1, NULL, 0) << 8;
          }
        }
      }
    }


  } else {
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

      if (offset_str[1] == '-') {
        // offset is negative so clear the U (23rd) bit
        clear_bit(&instruction, 23);
        offset = strtol(offset_str+2, NULL, 0);
      } else {
        // offset is positive so the U bit is set by default
        offset = strtol(offset_str+1, NULL, 0);
      }
    } else {
      // offset is a shifted register
      // NOTE: THIS IS EXACTLY THE SAME AS IN PRE-INDEXING, SO WILL NEED TO REFORMAT
      // - THIS CASE IS OPTIONAL

      char* rm_str;
      //Declare the shift register (Rs)
      unsigned int rm = 0;

      // Set the I (25th) bit
      set_bit(&instruction, 25);

      // offset string is in the form of "{+/-}r2{, lsr <shift>}"
      // where shift is either an immediate or a register

      //check for the comma
      is_comma = strpbrk(offset_str, ",");
      if (is_comma == NULL) {
        // there is no comma
        // offset string is in the form of "{+/-}r2"
        // check for the minus
        if (offset_str[0] == '-') {
          // there is a minus
          // clear the U (23rd) bit
          clear_bit(&instruction, 23);
          // obtain the rm by skipping the "-r"
          // Get the register Rm (Bits 0 - 3)
          rm = strtol(offset_str+2, NULL, 0);
        } else {
          // there is no minus
          // obtain the rm by skipping the "r"
          // Get the register Rm (Bits 0 - 3)
          rm = strtol(offset_str+1, NULL, 0);
        }

        // or offset with rm - leaving the shift (bits 4-11) clear
        offset |= rm;
      } else {
        // There is a comma
        // therefore we need to split by the comma

        rm_str = strtok_r(offset_str, ",", &offset_str);
        if (rm_str[0] == '-') {
          // there is a minus
          // clear the U (23rd) bit
          clear_bit(&instruction, 23);
          // obtain the rm by skipping the "-r"
          // Get the register Rm (Bits 0 - 3)
          rm = strtol(rm_str+2, NULL, 0);
        } else {
          // there is no minus
          // obtain the rm by skipping the "r"
          // Get the register Rm (Bits 0 - 3)
          rm = strtol(rm_str+1, NULL, 0);
        }

        char* shift_type_str;
        //now split by the space to get the shift type
        shift_type_str = strtok_r(offset_str, " ", &offset_str);

        // shift type is lsl by default
        unsigned int shift_type = 0;
        if (!strcmp(shift_type_str, "lsl")) {shift_type << 5;}
        if (!strcmp(shift_type_str, "lsr")) {shift_type = 1 << 5;}
        if (!strcmp(shift_type_str, "asr")) {shift_type = 2 << 5;}
        if (!strcmp(shift_type_str, "ror")) {shift_type = 3 << 5;}

        offset |= rm | shift_type;
        // now offset_str = shift (either register or a constant amount)
        if (offset_str[0] == '#') {
          // shift = constant amount
          // leave 4th bitsr #2"

          // or offset with the constant (bits 7 - 11)
          offset |= strtol(offset_str+1, NULL, 0) << 7;
        } else {
          // shift = register
          // set 4th bit
          set_bit(&offset, 4);

          // bit 7 is zero
          // or offset with the shift register (Rs) number
          offset |= strtol(offset_str+1, NULL, 0) << 8;
        }
      }
    }
  }
instruction |= cond /*| addr */| rn | rd | offset;
return instruction;
}
