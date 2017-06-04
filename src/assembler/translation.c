#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "assemble.h"


/*
 * Converts assembler instructions to binary on the second pass
 * @param instructions - array of assembler instructions
 * @returns void
*/
void process_instructions(char** instructions, FILE* output) {

  const char space[2] = " ";

  for (int i=0; i<100; i++) {
    char *rest = instructions[i];
    if (!strcmp(rest, "")) {
      break;
    }
    char* mnem = strtok_r(rest, space, &rest);
    identify_instruction(mnem, rest, output);
  }

}

void identify_instruction(char* mnem, char* params, FILE* output) {
       if (!strcmp(mnem, "mov"))   { do_mov(params, output); }
  else if (!strcmp(mnem, "add"))   { do_add(params, output); }
  else if (!strcmp(mnem, "orr"))   { do_orr(params, output); }
  else if (!strcmp(mnem, "sub"))   { do_sub(params, output); }
  else if (!strcmp(mnem, "cmp"))   { do_cmp(params, output); }
  else if (!strcmp(mnem, "eor"))   { do_eor(params, output); }
  else if (!strcmp(mnem, "mul"))   { do_mul(params, output); }
  else if (!strcmp(mnem, "tst"))   { do_tst(params, output); }
  else if (!strcmp(mnem, "teq"))   { do_teq(params, output); }
  else if (!strcmp(mnem, "rsb"))   { do_rsb(params, output); }
  else if (!strcmp(mnem, "and"))   { do_and(params, output); }
  else if (!strcmp(mnem, "mla"))   { do_mla(params, output); }
  else if (!strcmp(mnem, "ldr"))   { do_ldr(params, output); }
  else if (!strcmp(mnem, "str"))   { do_str(params, output); }
  else if (!strcmp(mnem, "beq"))   { do_beq(params, output); }
  else if (!strcmp(mnem, "bne"))   { do_bne(params, output); }
  else if (!strcmp(mnem, "bge"))   { do_bge(params, output); }
  else if (!strcmp(mnem, "blt"))   { do_blt(params, output); }
  else if (!strcmp(mnem, "bgt"))   { do_bgt(params, output); }
  else if (!strcmp(mnem, "ble"))   { do_ble(params, output); }
  else if (!strcmp(mnem, "b"))     { do_b(params, output); }
  else if (!strcmp(mnem, "lsl"))   { do_lsl(params, output); }
  else if (!strcmp(mnem, "andeq")) { do_andeq(params, output); }
  else { fprintf(stderr, "Unknown mnemonic"); }
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
