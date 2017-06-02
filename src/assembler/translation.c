#include <stdio.h>
#include "assemble.h"


/*
 * Converts assembler instructions to binary on the second pass
 * @param instructions - array of assembler instructions
 * @returns void
*/
void process_instructions(char** instructions) {

  const char space[1] = " ";

  for (int i=0; i<100; i++) {
    char *rest = instructions[i];
    mnem = strtok_r(rest, space, &rest);
    identify_instruction(mnem, rest);
  }

}

void identifyInstruction(char* mnem, char* params) {
       if (!strcmp(mnem, "mov"))   { mov(params); }
  else if (!strcmp(mnem, "add"))   { add(params); }
  else if (!strcmp(mnem, "orr"))   { orr(params); }
  else if (!strcmp(mnem, "sub"))   { sub(params); }
  else if (!strcmp(mnem, "cmp"))   { cmp(params); }
  else if (!strcmp(mnem, "eor"))   { eor(params); }
  else if (!strcmp(mnem, "mul"))   { mul(params); }
  else if (!strcmp(mnem, "tst"))   { tst(params); }
  else if (!strcmp(mnem, "teq"))   { teq(params); }
  else if (!strcmp(mnem, "rsb"))   { rsb(params); }
  else if (!strcmp(mnem, "and"))   { and(params); }
  else if (!strcmp(mnem, "mla"))   { mla(params); }
  else if (!strcmp(mnem, "ldr"))   { ldr(params); }
  else if (!strcmp(mnem, "str"))   { str(params); }
  else if (!strcmp(mnem, "beq"))   { beq(params); }
  else if (!strcmp(mnem, "bne"))   { bne(params); }
  else if (!strcmp(mnem, "bge"))   { bge(params); }
  else if (!strcmp(mnem, "blt"))   { blt(params); }
  else if (!strcmp(mnem, "bgt"))   { bgt(params); }
  else if (!strcmp(mnem, "ble"))   { ble(params); }
  else if (!strcmp(mnem, "b"))     { b(params); }
  else if (!strcmp(mnem, "lsl"))   { lsl(params); }
  else if (!strcmp(mnem, "andeq")) { andeq(params); }
  else { fprintf(strerr, "Unknown mnemonic"); }
}
