#include <stdio.h>
#include <string.h>
#include "assemble.h"

/*
 * Finds which instruction type the mnemonic corresponds to
 * @param mnem - pointer to the mnemonic string
 * @returns the corresponding instruction type
*/
enum instruction_type identifyInstruction(char* mnem) {
  if (isDataProcessing(mnem)) {
    return DATA_PROCESSING;
  } else if (isMultiply(mnem)) {
    return MULTIPLY;
  } else if (isSDT(mnem)) {
    return SINGLE_DATA_TRANSFER;
  } else if (isBranch(mnem)) {
    return BRANCH;
  } else if (isSpecial(mnem)){
    return SPECIAL;
  } else {
    // Instruction is label
    return LABEL;
  }
}

/*
 * Checks whether mnemonic corresponds to a Data Processing instruction
 * @param mnem - pointer to the mnemonic string
 * @returns 1 if mnem corresponds to a Data Processing instruction, 0 otherwise
*/
int isDataProcessing(char* mnem) {
  // strcmp(s1, s2) returns 0 is string s1 is the same as s2
  return !strcmp(*mnem, "add") || !strcmp(*mnem, "sub") || !strcmp(*mnem, "rsb") ||
         !strcmp(*mnem, "and") || !strcmp(*mnem, "eor") || !strcmp(*mnem, "orr") ||
         !strcmp(*mnem, "mov") || !strcmp(*mnem, "tst") || !strcmp(*mnem, "teq") ||
         !strcmp(*mnem, "cmp");
}


/*
 * Checks whether mnemonic corresponds to a Multiply instruction
 * @param mnem - pointer to the mnemonic string
 * @returns 1 if mnem corresponds to a Multiply instruction, 0 otherwise
*/
int isMultiply(char* mnem) {
  return !strcmp(*mnem, "mul") || !strcmp(*mnem, "mla");
}

/*
 * Checks whether mnemonic corresponds to a Single Data Transfer instruction
 * @param mnem - pointer to the mnemonic string
 * @returns 1 if mnem corresponds to a Single Data Transfer instruction,
 *          0 otherwise
*/
int isSDT(char* mnem) {
  return !strcmp(*mnem, "ldr") || !strcmp(*mnem, "str");
}

/*
 * Checks whether mnemonic corresponds to a Branch instruction
 * @param mnem - pointer to the mnemonic string
 * @returns 1 if mnem corresponds to a Branch instruction, 0 otherwise
*/
int isBranch(char* mnem) {
  return !strcmp(*mnem, "beq") || !strcmp(*mnem, "bne") || !strcmp(*mnem, "bge") ||
         !strcmp(*mnem, "blt") || !strcmp(*mnem, "bgt") ||!strcmp(*mnem, "ble") ||
         !strcmp(*mnem, "b");
}

/*
 * Checks whether mnemonic corresponds to a Special instruction
 * @param mnem - pointer to the mnemonic string
 * @returns 1 if mnem corresponds to a Special instruction, 0 otherwise
*/
int isSpecial(char* mnem) {
  return !strcmp(*mnem, "lsl") || !strcmp(*mnem, "andeq");
}
