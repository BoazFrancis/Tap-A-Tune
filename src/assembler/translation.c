#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "assemble.h"


/*
 * Converts assembler instructions to binary on the second pass
 * @param instructions - array of assembler instructions
 * @returns void
*/
void process_instructions(int count, char** instructions, FILE* output, SymbolTable* st) {

  const char space[2] = " ";
  int instruction_addr = 0;
  int original_count = count;
  int* excess_mem = malloc(sizeof(int));
  int excess_size = 0;

  for (int i=0; i<original_count; i++) {
    char *rest = instructions[i];
    if (!strcmp(rest, "")) {
      break;
    }
    char* mnem = strtok_r(rest, space, &rest);
    char* pos = strchr(mnem, ':');
    if (pos == NULL && strcmp(trim_whitespace(mnem), "") != 0) {
      int data = identify_instruction(mnem, rest, st, instruction_addr, &count, &excess_mem, &excess_size);
      write_to_file(data, output);
      instruction_addr += WORD_SIZE;
    }
  }

  for (int i=0; i<excess_size; i++) {
    write_to_file(excess_mem[i], output);
  }

}

int identify_instruction(char* mnem, char* params, SymbolTable* st, int addr, int* count, int** excess_mem, int* excess_size) {

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
  else if (!strcmp(mnem, "ldr"))   { return do_ldr(params, addr, count, excess_mem, excess_size); }
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

char* trim_whitespace(char *str) {

  char *end;

  // Trim leading space
  while (isspace((unsigned char)*str)) {
    str++;
  }

  if (*str == 0) {
    return str;
  }

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator
  *(end+1) = 0;

  return str;

}
