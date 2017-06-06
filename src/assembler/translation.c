#include "assemble.h"


/*
 * Converts assembler instructions to binary on the second pass
 * @param instructions - array of assembler instructions
 * @returns void
*/
void process_instructions(int total_size, int* num_no_labels, char** instructions, FILE* output, SymbolTable* st) {

  const char space[2] = " ";
  int instruction_addr = 0;
  int* memory = malloc(sizeof(int)*total_size);

  for (int i=0; i<total_size; i++) {
    char *rest = instructions[i];
    if (!strcmp(rest, "")) {
      break;
    }
    char* mnem = strtok_r(rest, space, &rest);
    char* pos = strchr(mnem, ':');
    if (pos == NULL && strcmp(trim_whitespace(mnem), "") != 0) {
      int data = identify_instruction(mnem, rest, st, instruction_addr, num_no_labels, &memory);
      memory[instruction_addr/WORD_SIZE] = data;
      instruction_addr += WORD_SIZE;
    }
  }

  for (int i=0; i<*num_no_labels; i++) {
    write_to_file(memory[i], output);
  }

}

int identify_instruction(char* mnem, char* params, SymbolTable* st, int addr, int* num_no_labels, int** memory) {

       if (!strcmp(mnem, "mov"))   { return do_mov(params); }
  else if (!strcmp(mnem, "add"))   { return do_add(params); }
  else if (!strcmp(mnem, "orr"))   { return do_orr(params); }
  else if (!strcmp(mnem, "sub"))   { return do_sub(params); }
  else if (!strcmp(mnem, "cmp"))   { return do_cmp(params); }
  else if (!strcmp(mnem, "eor"))   { return do_eor(params); }
  else if (!strcmp(mnem, "mul"))   { return do_mul(params); }
  else if (!strcmp(mnem, "tst"))   { return do_tst(params); }
  else if (!strcmp(mnem, "teq"))   { return do_teq(params); }
  else if (!strcmp(mnem, "rsb"))   { return do_rsb(params); }
  else if (!strcmp(mnem, "and"))   { return do_and(params); }
  else if (!strcmp(mnem, "mla"))   { return do_mla(params); }
  else if (!strcmp(mnem, "ldr"))   { return do_ldr(params, addr, num_no_labels, memory); }
  else if (!strcmp(mnem, "str"))   { return do_str(params); }
  else if (!strcmp(mnem, "beq"))   { return do_beq(params, st, addr); }
  else if (!strcmp(mnem, "bne"))   { return do_bne(params, st, addr); }
  else if (!strcmp(mnem, "bge"))   { return do_bge(params, st, addr); }
  else if (!strcmp(mnem, "blt"))   { return do_blt(params, st, addr); }
  else if (!strcmp(mnem, "bgt"))   { return do_bgt(params, st, addr); }
  else if (!strcmp(mnem, "ble"))   { return do_ble(params, st, addr); }
  else if (!strcmp(mnem, "b"))     { return do_b(params, st, addr); }
  else if (!strcmp(mnem, "lsl"))   { return do_lsl(params); }
  else if (!strcmp(mnem, "andeq")) { return do_andeq(params); }
  else { fprintf(stderr, "Unknown mnemonic"); }
  return 0;
}
