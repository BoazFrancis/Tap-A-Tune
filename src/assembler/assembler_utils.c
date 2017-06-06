#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assemble.h"


int get_rotated_op(unsigned int* operand) {
  // Keep rotating until size is 8 bits
  int i = 0;
  unsigned int rotation;
  while (i < 16) {
    rotation = rotate_left(*operand, 2*i);
    if (rotation < (1 << 9)) {
      break;
    }
    i++;
  }
  *operand = rotation;
  return i;
}

int do_mov(char* params) {

  char* value;
  unsigned int cond = 14 << COND_START;
  char* reg = strtok_r(params, ",", &value);
  value = trim_whitespace(value);
  unsigned int instruction = MOV << 21;
  unsigned int op2;

  if (value[0] == '#') {
    // Immediate value
    set_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
    int rotation = get_rotated_op(&op2);
    // The full operand is the first 8 bits of op2 | the 4 bits of rotation
    op2 = (rotation << 8) | op2;
  }
  else {

    // Register e.g. mov r2, r1
    clear_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);

    char* shift;
    char* str = strtok_r(value, ",", &shift);

    if (strcmp(trim_whitespace(shift), "")) {

      shift = trim_whitespace(shift);
      char* shift_type = malloc(sizeof(char)*3);
      strncpy(shift_type, shift, 3);

      if (!strcmp(shift_type,"lsr")) {
        set_bit(&instruction,  5);
        clear_bit(&instruction, 6);
      }
      else if (!strcmp(shift_type,"lsl")) {
        clear_bit(&instruction, 5);
        clear_bit(&instruction, 6);
      }
      else if (!strcmp(shift_type,"asr")) {
        clear_bit(&instruction, 5);
        set_bit(&instruction, 6);
      }
      else if (!strcmp(shift_type,"ror")) {
        set_bit(&instruction, 5);
        set_bit(&instruction, 6);
      }

      int shift_reg = strtol(shift + 5, NULL, 0);

      if (shift[4] == '#') {
        instruction |= shift_reg << 7;
        clear_bit(&instruction, 4);
      }
      else {
        instruction |= shift_reg << 8;
        set_bit(&instruction, 4);
      }

    }

  }

  // Store Rd register, removing the "r"
  long unsigned reg_binary = strtol(reg+1, NULL, 0);
  reg_binary <<= 12;

  instruction |= cond | op2 | reg_binary;
  return instruction;

}

int do_add(char* params) {

  // Declare binary instruction, set it to 0
  unsigned int instruction = 0;

  char* value;

  // Set the condition field to 1110 (i.e. 14)
  unsigned int cond = 14 << COND_START;

  char* rn_string = strtok_r(params, ",", &value);
  value = trim_whitespace(value);
  // Set Rn to value of base register
  unsigned int rn = strtol(rn_string+1, NULL, 0) << 12;

  char* rd_string = strtok_r(value, ",", &value);
  // set Rd to value of destination register
  value = trim_whitespace(value);
  unsigned int rd = strtol(rd_string+1, NULL, 0) << 16;

  unsigned int opcode = ADD << 21;
  unsigned int op2;
  clear_bit(&instruction, 20);

  if (value[0] == '#') {
    // Immediate value
    set_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
    int rotation = get_rotated_op(&op2);
    // The full operand is the first 8 bits of op2 | the 4 bits of rotation
    op2 = (rotation << 8) | op2;
  }
  else {
    // Register e.g. mov r2, r1
    clear_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
  }

  instruction |= cond | op2 | rd | rn | opcode;
  return instruction;

}

int do_orr(char* params) {

  // Declare binary instruction, set it to 0
  unsigned int instruction = 0;

  char* value;

  // Set the condition field to 1110 (i.e. 14)
  unsigned int cond = 14 << COND_START;

  char* rn_string = strtok_r(params, ",", &value);
  value = trim_whitespace(value);
  // Set Rn to value of base register
  unsigned int rn = strtol(rn_string+1, NULL, 0) << 12;

  char* rd_string = strtok_r(value, ",", &value);
  // set Rd to value of destination register
  value = trim_whitespace(value);
  unsigned int rd = strtol(rd_string+1, NULL, 0) << 16;

  unsigned int opcode = ORR << 21;
  unsigned int op2;
  clear_bit(&instruction, 20);

  if (value[0] == '#') {
    // Immediate value
    set_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
    int rotation = get_rotated_op(&op2);
    // The full operand is the first 8 bits of op2 | the 4 bits of rotation
    op2 = (rotation << 8) | op2;
  }
  else {
    // Register e.g. mov r2, r1
    clear_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
  }

  instruction |= cond | op2 | rd | rn | opcode;
  return instruction;

}

int do_sub(char* params) {

  // Declare binary instruction, set it to 0
  unsigned int instruction = 0;

  char* value;

  // Set the condition field to 1110 (i.e. 14)
  unsigned int cond = 14 << COND_START;

  char* rn_string = strtok_r(params, ",", &value);
  value = trim_whitespace(value);
  // Set Rn to value of base register
  unsigned int rn = strtol(rn_string+1, NULL, 0) << 12;

  char* rd_string = strtok_r(value, ",", &value);
  // set Rd to the destination register number
  value = trim_whitespace(value);
  unsigned int rd = strtol(rd_string+1, NULL, 0) << 16;

  unsigned int opcode = SUB << 21;

  // Declare Operand2
  unsigned int op2;


  if (value[0] == '#') {
    // operand 2 is an Immediate value
    set_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
    int rotation = get_rotated_op(&op2);
    // The full operand is the first 8 bits of op2 | the 4 bits of rotation
    op2 = (rotation << 8) | op2;
  }
  else {
    // Operand2 is of the form of a shifted register, Rm{,<shift>}
    

    //Declare Rm string and Rm register number
    char* rm_str;
    unsigned int rm = 0;


    // value now has the form of "Rm{, <shift>}"

    //check for the comma - i.e. check for existence of {, <shift>}
    char* is_comma;
    is_comma = strpbrk(value, ",");
    if (is_comma == NULL) {
      // there is no comma
      // therefore value has the form of "Rm"
      // Obtain Rm register number
      rm = strtol(value+1, NULL, 0);
      // or Operand2 with Rm - leaving the shift (bits 4-11) clear
      op2 |= rm;
    } else {
      // There is a comma
      // Declare offset_str which will be used for bits (4-11)
      char* offset_str;
      // therefore we need to split by the comma

      rm_str = strtok_r(value, ",", &offset_str);
      // Obtain Rm register number
      rm = strtol(rm_str+1, NULL, 0);


      char* shift_type_str;
      //now split by the space to get the shift type
      shift_type_str = strtok_r(offset_str, " ", &offset_str);

      // shift type is lsl by default
      unsigned int shift_type = 0;
      if (!strcmp(shift_type_str, "lsl")) {shift_type << 5;}
      if (!strcmp(shift_type_str, "lsr")) {shift_type = 1 << 5;}
      if (!strcmp(shift_type_str, "asr")) {shift_type = 2 << 5;}
      if (!strcmp(shift_type_str, "ror")) {shift_type = 3 << 5;}

      op2 |= rm | shift_type;
      // now offset_str = shift (either register or a constant amount)
      if (offset_str[0] == '#') {
        // shift = constant amount
        // leave 4th bitsr #2"

        // or offset with the constant (bits 7 - 11)
        op2 |= strtol(offset_str+1, NULL, 0) << 7;
      } else {
        // shift = register
        // set 4th bit
        set_bit(&op2, 4);

        // bit 7 is zero
        // or offset with the shift register (Rs) number
        op2 |= strtol(offset_str+1, NULL, 0) << 8;
      }
    }
  }

  instruction |= cond | op2 | rd | rn | opcode;
  return instruction;

}

int do_cmp(char* params) {

  char* value;
  unsigned int cond = 14 << COND_START;
  char* reg = strtok_r(params, ",", &value);
  value = trim_whitespace(value);
  unsigned int instruction = 0;
  unsigned int opcode = CMP << 21;
  unsigned int op2;
  set_bit(&instruction, 20);
  if (value[0] == '#') {
    // Immediate value
    set_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
    int rotation = get_rotated_op(&op2);
    // The full operand is the first 8 bits of op2 | the 4 bits of rotation
    op2 = (rotation << 8) | op2;
  }
  else {
    // Register e.g. mov r2, r1
    clear_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
  }

  // Store Rd register, removing the "r"
  long unsigned reg_binary = strtol(reg+1, NULL, 0);
  reg_binary <<= 16;

  instruction |= cond | op2 | reg_binary | opcode;
  return instruction;

}

int do_eor(char* params) {

  // Declare binary instruction, set it to 0
  unsigned int instruction = 0;

  char* value;

  // Set the condition field to 1110 (i.e. 14)
  unsigned int cond = 14 << COND_START;

  char* rn_string = strtok_r(params, ",", &value);
  value = trim_whitespace(value);
  // Set Rn to value of base register
  unsigned int rn = strtol(rn_string+1, NULL, 0) << 12;

  char* rd_string = strtok_r(value, ",", &value);
  // set Rd to value of destination register
  value = trim_whitespace(value);
  unsigned int rd = strtol(rd_string+1, NULL, 0) << 16;

  unsigned int opcode = EOR << 21;
  unsigned int op2;
  clear_bit(&instruction, 20);

  if (value[0] == '#') {
    // Immediate value
    set_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
    int rotation = get_rotated_op(&op2);
    // The full operand is the first 8 bits of op2 | the 4 bits of rotation
    op2 = (rotation << 8) | op2;
  }
  else {
    // Register e.g. mov r2, r1
    clear_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
  }

  instruction |= cond | op2 | rd | rn | opcode;
  return instruction;

}

int do_tst(char* params) {

  char* value;
  unsigned int cond = 14 << COND_START;
  char* reg = strtok_r(params, ",", &value);
  value = trim_whitespace(value);
  unsigned int instruction = 0;
  unsigned int opcode = TST << 21;
  unsigned int op2;
  set_bit(&instruction, 20);
  if (value[0] == '#') {
    // Immediate value
    set_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
    int rotation = get_rotated_op(&op2);
    // The full operand is the first 8 bits of op2 | the 4 bits of rotation
    op2 = (rotation << 8) | op2;
  }
  else {
    // Register e.g. mov r2, r1
    clear_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
  }

  // Store Rd register, removing the "r"
  long unsigned reg_binary = strtol(reg+1, NULL, 0);
  reg_binary <<= 16;

  instruction |= cond | op2 | reg_binary | opcode;
  return instruction;

}

int do_mul(char* params) {

  // Declare binary instruction, set it to 0
  unsigned int instruction = 0;
  char* rest;

  // Set the condition field to 1110 (i.e. 14)
  unsigned int cond = 14 << COND_START;

  // Set bits 4 and 7
  // Bits A and S are not set
  set_bit(&instruction, 4);
  set_bit(&instruction, 7);

  char* rd_string = strtok_r(params, ",", &rest);
  char* rm_string = strtok_r(trim_whitespace(rest), ",", &rest);
  char* rs_string = strtok_r(trim_whitespace(rest), ",", &rest);

  // Set Rn to value of base register
  unsigned int rd = strtol(rd_string+1, NULL, 0) << 16;
  unsigned int rs = strtol(rs_string+1, NULL, 0) << 8;
  unsigned int rm = strtol(rm_string+1, NULL, 0);

  instruction |= cond | rd | rs | rm;
  return instruction;

}

int do_teq(char* params) {
  char* value;
  unsigned int cond = 14 << COND_START;
  char* reg = strtok_r(trim_whitespace(params), ",", &value);
  value = trim_whitespace(value);
  unsigned int instruction = 0;
  unsigned int opcode = TEQ << 21;
  unsigned int op2;
  set_bit(&instruction, 20);
  if (value[0] == '#') {
    // Immediate value
    set_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
    int rotation = get_rotated_op(&op2);
    // The full operand is the first 8 bits of op2 | the 4 bits of rotation
    op2 = (rotation << 8) | op2;
  }
  else {
    // Register e.g. mov r2, r1
    clear_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
  }

  // Store Rd register, removing the "r"
  long unsigned reg_binary = strtol(reg+1, NULL, 0);
  reg_binary <<= 16;

  instruction |= cond | op2 | reg_binary | opcode;
  return instruction;
}








int do_rsb(char* params) {

  // Declare binary instruction, set it to 0
  unsigned int instruction = 0;

  char* value;

  // Set the condition field to 1110 (i.e. 14)
  unsigned int cond = 14 << COND_START;

  char* rn_string = strtok_r(params, ",", &value);
  value = trim_whitespace(value);
  // Set Rn to value of base register
  unsigned int rn = strtol(rn_string+1, NULL, 0) << 12;

  char* rd_string = strtok_r(value, ",", &value);
  // set Rd to value of destination register
  value = trim_whitespace(value);
  unsigned int rd = strtol(rd_string+1, NULL, 0) << 16;

  unsigned int opcode = RSB << 21;
  unsigned int op2;
  clear_bit(&instruction, 20);

  if (value[0] == '#') {
    // Immediate value
    set_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
    int rotation = get_rotated_op(&op2);
    // The full operand is the first 8 bits of op2 | the 4 bits of rotation
    op2 = (rotation << 8) | op2;
  }
  else {
    // Register e.g. mov r2, r1
    clear_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
  }

  instruction |= cond | op2 | rd | rn | opcode;
  return instruction;

}









int do_and(char* params) {

  // Declare binary instruction, set it to 0
  unsigned int instruction = 0;

  char* value;

  // Set the condition field to 1110 (i.e. 14)
  unsigned int cond = 14 << COND_START;

  char* rn_string = strtok_r(params, ",", &value);
  value = trim_whitespace(value);
  // Set Rn to value of base register
  unsigned int rn = strtol(rn_string+1, NULL, 0) << 12;

  char* rd_string = strtok_r(value, ",", &value);
  // set Rd to value of destination register
  value = trim_whitespace(value);
  unsigned int rd = strtol(rd_string+1, NULL, 0) << 16;

  unsigned int opcode = AND << 21;
  unsigned int op2;
  clear_bit(&instruction, 20);

  if (value[0] == '#') {
    // Immediate value
    set_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
    int rotation = get_rotated_op(&op2);
    // The full operand is the first 8 bits of op2 | the 4 bits of rotation
    op2 = (rotation << 8) | op2;
  }
  else {
    // Register e.g. mov r2, r1
    clear_bit(&instruction, DATA_PROC_IMM_IDENTIFIER);
    op2 = strtol(value+1, NULL, 0);
  }

  instruction |= cond | op2 | rd | rn | opcode;
  return instruction;

}


int do_mla(char* params) {

  // Declare binary instruction, set it to 0
  unsigned int instruction = 0;
  char* rest;

  // Set the condition field to 1110 (i.e. 14)
  unsigned int cond = 14 << COND_START;

  // Set bits 4 and 7, and 21 (A bit)
  // Bit S is not set
  set_bit(&instruction, 4);
  set_bit(&instruction, 7);
  set_bit(&instruction, 21);

  char* rd_string = strtok_r(params, ",", &rest);
  char* rm_string = strtok_r(trim_whitespace(rest), ",", &rest);
  char* rs_string = strtok_r(trim_whitespace(rest), ",", &rest);
  char* rn_string = strtok_r(trim_whitespace(rest), ",", &rest);

  // Set Rn to value of base register
  unsigned int rd = strtol(rd_string+1, NULL, 0) << 16;
  unsigned int rn = strtol(rn_string+1, NULL, 0) << 12;
  unsigned int rs = strtol(rs_string+1, NULL, 0) << 8;
  unsigned int rm = strtol(rm_string+1, NULL, 0);

  instruction |= cond | rd | rn | rs | rm;
  return instruction;

}

int do_ldr(char* params, int instruction_addr, int* num_no_labels, int** memory) {

  unsigned int instruction = 0;
  char* rn_string;
  char* rd_str;
  char* addr_str;
  char* offset_str;
  // TODO: long or int??
  unsigned int addr;
  unsigned int rn = 0;
  unsigned int rd = 0;
  unsigned int offset = 0;

  unsigned int cond = 14 << 28;

  // 26th bit is always set to 1 for sdt
  set_bit(&instruction, 26);

  // L bit is set for ldr (bit 20)
  set_bit(&instruction, 20);

  // Set U (23rd) bit by default - clear it if necessary
  set_bit(&instruction, 23);

  //get the Rd string (e.g. r3) by splitting by the comma
  rd_str = strtok_r(params, ",", &addr_str);

  // get the Rd register number
  rd = strtol(rd_str+1, NULL, 0) << 12;

  //trim the whitespace after the comma if there is one
  addr_str = trim_whitespace(addr_str);

  if (addr_str[0] == '=') {

    // Set the offset
    int mem_val = strtol(addr_str+1, NULL, 0);

    if (mem_val < 0xFF) {
      char* without_eq = addr_str + 1;
      char* mov_param = cat(rd_str, ",#", without_eq);
      return do_mov(mov_param);
    }
    else {

      int store_addr = *num_no_labels * WORD_SIZE;
      int offset = store_addr - instruction_addr - 8;
      set_bit(&instruction, 24);

      // Set Rn to the PC
      rn = PC_REG << 16;

      // Save mem_val
      (*memory)[*num_no_labels] = mem_val;
      (*num_no_labels)++;

      return instruction | cond | rd | rn | offset;

    }

  }
  else {
    // Register

    //Declare the pointer that checks for the comma - used later on
    char* is_comma;

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
  }

  instruction |= cond | addr | rn | rd | offset;

}

int do_str(char* params) {
  // NOTE: this is the same as ldr but without the numberic constant cas
  // for <address>, and L bit is NOT set

  unsigned int instruction = 0;
  char* rn_string;
  char* rd_str;
  char* addr_str;
  char* offset_str;
  // TODO: long or int??
  unsigned int addr;
  unsigned int rn = 0;
  unsigned int rd = 0;
  unsigned int offset = 0;

  unsigned int cond = 14 << 28;

  // 26th bit is always set to 1 for sdt
  set_bit(&instruction, 26);

  // L bit is NOT set for str (bit 20)

  // Set U (23rd) bit by default - clear it if necessary
  set_bit(&instruction, 23);

  //get the Rd string (e.g. r3) by splitting by the comma
  rd_str = strtok_r(params, ",", &addr_str);

  // get the Rd register number
  rd = strtol(rd_str+1, NULL, 0) << 12;

  //trim the whitespace after the comma if there is one
  addr_str = trim_whitespace(addr_str);

  // Register

  //Declare the pointer that checks for the comma - used later on
  char* is_comma;

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
  instruction |= cond | addr | rn | rd | offset;

}

int do_branch(char* params, SymbolTable* st, int addr, unsigned int cond) {

  int jump_addr = get_address(st, trim_whitespace(params)) - addr - 8;
  jump_addr >>= 2;

  // Set bits 27 and 25
  unsigned int instruction = extract_bits(&jump_addr, BRANCH_OFFSET_START, BRANCH_OFFSET_LEN);
  set_bit(&instruction, 25);
  set_bit(&instruction, 27);

  return instruction | cond;

}

int do_beq(char* params, SymbolTable* st, int addr) {
  return do_branch(params, st, addr, 0 << COND_START);
}

int do_bne(char* params, SymbolTable* st, int addr) {
  return do_branch(params, st, addr, 1 << COND_START);
}

int do_bge(char* params, SymbolTable* st, int count) {
  return do_branch(params, st, count, 10 << COND_START);
}

int do_blt(char* params, SymbolTable* st, int addr) {
  return do_branch(params, st, addr, 11 << COND_START);
}

int do_bgt(char* params, SymbolTable* st, int addr) {
  return do_branch(params, st, addr, 12 << COND_START);
}

int do_ble(char* params, SymbolTable* st, int addr) {
  return do_branch(params, st, addr, 13 << COND_START);
}

int do_b(char* params, SymbolTable* st, int addr) {
  return do_branch(params, st, addr, 14 << COND_START);
}

int do_lsl(char* params) {

  char* rest;
  char* rn_string = strtok_r(params, ",", &rest);
  char* lsl = malloc(sizeof(char)*12);
  strcpy(lsl, "lsl ");
  lsl = strcat(lsl, trim_whitespace(rest));

  char* rn_comma = strcat(rn_string, ", ");
  return do_mov(strcat(strcat(rn_comma, rn_comma), lsl));

}

int do_andeq(char* params) {
  return 0;
}
