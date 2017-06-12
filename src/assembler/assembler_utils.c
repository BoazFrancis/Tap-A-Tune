#include "assemble.h"


int get_rotated_op(unsigned int *operand) {
  // Keep rotating until size is 8 bits
  int i = 0;
  unsigned int rotated_val;
  while (i < 16) {
    rotated_val = rotate_left(*operand, 2*i);
    if (rotated_val < (1 << 8)) {
      break;
    }
    i++;
  }
  *operand = rotated_val;
  return i;
}

int do_mov(char *params) {

  char *value;
  unsigned int cond = 14 << COND_START;
  char *reg = strtok_r(params, ",", &value);
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

    char *shift;
    char *str = strtok_r(value, ",", &shift);

    if (strcmp(trim_whitespace(shift), "")) {

      shift = trim_whitespace(shift);
      char *shift_type = malloc(sizeof(char)*3);

      if (shift_type == NULL) {
        perror("shift_type malloc in assembler_utils");
        exit(EXIT_FAILURE);
      }

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

int do_add(char *params) {

  // Declare binary instruction, set it to 0
  unsigned int instruction = 0;

  char *value;

  // Set the condition field to 1110 (i.e. 14)
  unsigned int cond = 14 << COND_START;

  char *rn_string = strtok_r(params, ",", &value);
  value = trim_whitespace(value);
  // Set Rn to value of base register
  unsigned int rn = strtol(rn_string+1, NULL, 0) << 12;

  char *rd_string = strtok_r(value, ",", &value);
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

int do_orr(char *params) {

  // Declare binary instruction, set it to 0
  unsigned int instruction = 0;

  char *value;

  // Set the condition field to 1110 (i.e. 14)
  unsigned int cond = 14 << COND_START;

  char *rn_string = strtok_r(params, ",", &value);
  value = trim_whitespace(value);
  // Set Rn to value of base register
  unsigned int rn = strtol(rn_string+1, NULL, 0) << 12;

  char *rd_string = strtok_r(value, ",", &value);
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

int do_sub(char *params) {

  // Declare binary instruction, set it to 0
  unsigned int instruction = 0;

  char *value;

  // Set the condition field to 1110 (i.e. 14)
  unsigned int cond = 14 << COND_START;

  char *rn_string = strtok_r(params, ",", &value);
  value = trim_whitespace(value);
  // Set Rn to value of base register
  unsigned int rn = strtol(rn_string+1, NULL, 0) << 12;

  char *rd_string = strtok_r(value, ",", &value);
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
    char *rm_str;
    unsigned int rm = 0;


    // value now has the form of "Rm{, <shift>}"

    //check for the comma - i.e. check for existence of {, <shift>}
    char *is_comma;
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
      char *offset_str;
      // therefore we need to split by the comma

      rm_str = strtok_r(value, ",", &offset_str);
      // Obtain Rm register number
      rm = strtol(rm_str+1, NULL, 0);


      char *shift_type_str;
      //now split by the space to get the shift type
      shift_type_str = strtok_r(offset_str, " ", &offset_str);

      // shift type is lsl by default
      unsigned int shift_type = 0;
      if (!strcmp(shift_type_str, "lsl")) {shift_type << 5;}
      if (!strcmp(shift_type_str, "lsr")) {shift_type = 1 << 5;}
      if (!strcmp(shift_type_str, "asr")) {shift_type = 2 << 5;}
      if (!strcmp(shift_type_str, "ror")) {shift_type = 3 << 5;}

      op2 |= rm | shift_type;
      free(shift_type);
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

int do_cmp(char *params) {

  char *value;
  unsigned int cond = 14 << COND_START;
  char *reg = strtok_r(params, ",", &value);
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

int do_eor(char *params) {

  // Declare binary instruction, set it to 0
  unsigned int instruction = 0;

  char *value;

  // Set the condition field to 1110 (i.e. 14)
  unsigned int cond = 14 << COND_START;

  char *rn_string = strtok_r(params, ",", &value);
  value = trim_whitespace(value);
  // Set Rn to value of base register
  unsigned int rn = strtol(rn_string+1, NULL, 0) << 12;

  char *rd_string = strtok_r(value, ",", &value);
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

int do_tst(char *params) {

  char *value;
  unsigned int cond = 14 << COND_START;
  char *reg = strtok_r(params, ",", &value);
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

int do_mul(char *params) {

  // Declare binary instruction, set it to 0
  unsigned int instruction = 0;
  char *rest;

  // Set the condition field to 1110 (i.e. 14)
  unsigned int cond = 14 << COND_START;

  // Set bits 4 and 7
  // Bits A and S are not set
  set_bit(&instruction, 4);
  set_bit(&instruction, 7);

  char *rd_string = strtok_r(params, ",", &rest);
  char *rm_string = strtok_r(trim_whitespace(rest), ",", &rest);
  char *rs_string = strtok_r(trim_whitespace(rest), ",", &rest);

  // Set Rn to value of base register
  unsigned int rd = strtol(rd_string+1, NULL, 0) << 16;
  unsigned int rs = strtol(rs_string+1, NULL, 0) << 8;
  unsigned int rm = strtol(rm_string+1, NULL, 0);

  instruction |= cond | rd | rs | rm;
  return instruction;

}

int do_teq(char *params) {
  char *value;
  unsigned int cond = 14 << COND_START;
  char *reg = strtok_r(trim_whitespace(params), ",", &value);
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








int do_rsb(char *params) {

  // Declare binary instruction, set it to 0
  unsigned int instruction = 0;

  char *value;

  // Set the condition field to 1110 (i.e. 14)
  unsigned int cond = 14 << COND_START;

  char *rn_string = strtok_r(params, ",", &value);
  value = trim_whitespace(value);
  // Set Rn to value of base register
  unsigned int rn = strtol(rn_string+1, NULL, 0) << 12;

  char *rd_string = strtok_r(value, ",", &value);
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









int do_and(char *params) {

  // Declare binary instruction, set it to 0
  unsigned int instruction = 0;

  char *value;

  // Set the condition field to 1110 (i.e. 14)
  unsigned int cond = 14 << COND_START;

  char *rn_string = strtok_r(params, ",", &value);
  value = trim_whitespace(value);
  // Set Rn to value of base register
  unsigned int rn = strtol(rn_string+1, NULL, 0) << 12;

  char *rd_string = strtok_r(value, ",", &value);
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


int do_mla(char *params) {

  // Declare binary instruction, set it to 0
  unsigned int instruction = 0;
  char *rest;

  // Set the condition field to 1110 (i.e. 14)
  unsigned int cond = 14 << COND_START;

  // Set bits 4 and 7, and 21 (A bit)
  // Bit S is not set
  set_bit(&instruction, 4);
  set_bit(&instruction, 7);
  set_bit(&instruction, 21);

  char *rd_string = strtok_r(params, ",", &rest);
  char *rm_string = strtok_r(trim_whitespace(rest), ",", &rest);
  char *rs_string = strtok_r(trim_whitespace(rest), ",", &rest);
  char *rn_string = strtok_r(trim_whitespace(rest), ",", &rest);

  // Set Rn to value of base register
  unsigned int rd = strtol(rd_string+1, NULL, 0) << 16;
  unsigned int rn = strtol(rn_string+1, NULL, 0) << 12;
  unsigned int rs = strtol(rs_string+1, NULL, 0) << 8;
  unsigned int rm = strtol(rm_string+1, NULL, 0);

  instruction |= cond | rd | rn | rs | rm;
  return instruction;

}


int do_branch(char *params, SymbolTable *st, int addr, unsigned int cond) {

  int jump_addr = get_address(st, trim_whitespace(params)) - addr - 8;
  jump_addr >>= 2;

  // Set bits 27 and 25
  unsigned int instruction = extract_bits(&jump_addr, BRANCH_OFFSET_START, BRANCH_OFFSET_LEN);
  set_bit(&instruction, 25);
  set_bit(&instruction, 27);

  return instruction | cond;

}

int do_beq(char *params, SymbolTable *st, int addr) {
  return do_branch(params, st, addr, 0 << COND_START);
}

int do_bne(char *params, SymbolTable *st, int addr) {
  return do_branch(params, st, addr, 1 << COND_START);
}

int do_bge(char *params, SymbolTable *st, int count) {
  return do_branch(params, st, count, 10 << COND_START);
}

int do_blt(char *params, SymbolTable *st, int addr) {
  return do_branch(params, st, addr, 11 << COND_START);
}

int do_bgt(char *params, SymbolTable *st, int addr) {
  return do_branch(params, st, addr, 12 << COND_START);
}

int do_ble(char *params, SymbolTable *st, int addr) {
  return do_branch(params, st, addr, 13 << COND_START);
}

int do_b(char *params, SymbolTable *st, int addr) {
  return do_branch(params, st, addr, 14 << COND_START);
}

int do_lsl(char *params) {

  char *rest;
  char *rn_string = strtok_r(params, ",", &rest);
  char *lsl = malloc(sizeof(char)*12);
  if (lsl == NULL) {
    perror("lsl malloc in assembler_utils");
    exit(EXIT_FAILURE);
  }
  strcpy(lsl, "lsl ");
  lsl = strcat(lsl, trim_whitespace(rest));

  char *rn_comma = strcat(rn_string, ", ");
  return do_mov(strcat(strcat(rn_comma, rn_comma), lsl));

}

int do_andeq(char *params) {
  return 0;
}
