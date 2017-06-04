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
  // set Rd to value of destination register
  value = trim_whitespace(value);
  unsigned int rd = strtol(rd_string+1, NULL, 0) << 16;

  unsigned int opcode = SUB << 21;
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
  char* rs_string = strtok_r(trim_whitespace(rest), ",", &rest);
  char* rm_string = strtok_r(trim_whitespace(rest), ",", &rest);

  // Set Rn to value of base register
  unsigned int rd = strtol(rd_string+1, NULL, 0) << 16;
  unsigned int rs = strtol(rm_string+1, NULL, 0) << 8;
  unsigned int rm = strtol(rs_string+1, NULL, 0);

  instruction |= cond | rd | rs | rm;
  return instruction;

}

int do_teq(char* params) {
  char* value;
  unsigned int cond = 14 << COND_START;
  char* reg = strtok_r(params, ",", &value);
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

}

int do_ldr(char* params) {
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

  //get the Rd string (e.g. r3) by splitting by the comma
  rd_str = strtok_r(params, ",", &addr_str);

  // get the Rd register number
  rd = strtol(rd_str+1, NULL, 0) << 12;

  //trim the whitespace after the comma if there is one
  addr_str = trim_whitespace(addr_str);

  if (addr_str[0] == '=') {
    // Direct address
    if (addr_str[1] == '-') {
      // Negative
      clear_bit(&instruction, 23);
      addr = strtol(addr_str+2, NULL, 0);
    } else {
      set_bit(&instruction, 23);
      addr = strtol(addr_str+1, NULL, 0);
    }



    // Base register is PC
    rn = 15 << 16;

    // Pre indexed (set P)
    set_bit(&instruction, 24);



/* TODO:
    if (addr <= 0xff) {
      do_mov(params);
    }
*/


  } else {
    // Register
    if (addr_str[strlen(addr_str)-1] == ']') {
      // Pre indexed
      clear_bit(&instruction, 23);
      // Strip end bracket
      addr_str[strlen(addr_str)-1] = '\0';
      char* is_comma = strpbrk(addr_str, ",");
      if (is_comma == NULL) {
        // there is no comma in addr_str, i.e. if there is an offset
        // get Rn (note that addr_str is "[r10", for example
        // since the end bracket is stripped and we just need the 10)
        rn = strtol(addr_str+2, NULL, 0) << 16;
      } else {
        // There is a comma in addr_str
        // TODO: deal with offset
        rn_string = strtok_r(addr_str, ",", &offset_str);
        // rn_string starts with "r.."" and we just need what follows "r"
        rn = strtol(rn_string+2, NULL, 0) << 16;

        //trim whitespace after the comma if there is one
        offset_str = trim_whitespace(offset_str);

        if (offset_str[0] == '#') {
          //offset is an immediate value
          offset = strtol(offset_str, NULL, 0);
        }
      }
    } else {
      // Post indexed

    }
  }

  instruction |= addr | rn | rd | offset;
}

int do_str(char* params) {

}

int do_branch(char* params, SymbolTable* st, int count, unsigned int cond) {

  int jump_addr = get_address(st, trim_whitespace(params)) - count * WORD_SIZE - 8;

  // Set bits 27 and 25
  unsigned int instruction = extract_bits(&jump_addr, BRANCH_OFFSET_START, BRANCH_OFFSET_LEN) >> 2;
  set_bit(&instruction, 25);
  set_bit(&instruction, 27);

  return instruction | cond;

}

int do_beq(char* params, SymbolTable* st, int count) {
  return do_branch(params, st, count, 0 << COND_START);
}

int do_bne(char* params, SymbolTable* st, int count) {
  return do_branch(params, st, count, 1 << COND_START);
}

int do_bge(char* params, SymbolTable* st, int count) {
  return do_branch(params, st, count, 10 << COND_START);
}

int do_blt(char* params, SymbolTable* st, int count) {
  return do_branch(params, st, count, 11 << COND_START);
}

int do_bgt(char* params, SymbolTable* st, int count) {
  return do_branch(params, st, count, 12 << COND_START);
}

int do_ble(char* params, SymbolTable* st, int count) {
  return do_branch(params, st, count, 13 << COND_START);
}

int do_b(char* params, SymbolTable* st, int count) {
  return do_branch(params, st, count, 14 << COND_START);
}

int do_lsl(char* params) {

}

int do_andeq(char* params) {

}
