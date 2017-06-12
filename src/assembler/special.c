#include "assemble.h"

/**
 * Process the LSL instruction.
 * Calls the mov command once formatting the parameters
 * @param params - A pointer to the processor
 * @returns the instruction
 */
int do_lsl(char *params) {

  char *rest;
  char *rn_string = strtok_r(params, ",", &rest);

  // Create a mov command with "lsl" in the operand
  char *lsl = malloc(sizeof(char)*LENGTH_OF_LINE);
  strcpy(lsl, "lsl ");
  lsl = strcat(lsl, trim_whitespace(rest));

  char *rn_comma = strcat(rn_string, ", ");
  return do_mov(strcat(strcat(rn_comma, rn_comma), lsl));

}

/**
 * Process the ANDEQ instruction
 * @param params - A pointer to the processor
 * @returns an all 0 instruction
 */
int do_andeq(char *params) {
  return 0;
}
