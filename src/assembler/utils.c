#include <ctype.h>
#include "assemble.h"

/**
 * Concatenate 3 strings into one and return a new pointer to the string
 * @param a - A pointer to the first string
 * @param b - A pointer to the second string
 * @param b - A pointer to the third string
 * @returns the concatenated string
 */
char* cat(char* a, char* b, const char* c) {

  char* result = calloc(LENGTH_OF_LINE, sizeof(char));
  for (int i = 0; a[i] != '\0'; i++) {
    result[i] = a[i];
  }
  for (int i = 0; b[i] != '\0'; i++) {
    result[i + strlen(a)] = b[i];
  }
  for (int i = 0; c[i] != '\0'; i++) {
    result[i + strlen(a) + strlen(b)] = c[i];
  }

  return result;

}

/**
 * Removes trailing and leading whitespace from string
 * @param str - The string
 * @returns the adapted string
 */
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

/**
 * Keep rotating the operand until we can fit it with 8 bits of data
 * @param operand - The operand to rotate
 * @returns the rotated operand
 */
int get_rotated_op(unsigned int* operand) {
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

/**
 * If a shift is specified, then consider the different cases
 * @param instruction - A pointer to the instruction
 * @param shift - The shift (if it exists)
 * @returns void
 */
void check_shift(unsigned int* instruction, char* shift) {

  if (strcmp(trim_whitespace(shift), "")) {

    // Fill a 4 character length string of the shift type
    shift = trim_whitespace(shift);
    char* shift_type = malloc(sizeof(char)*DP_BLOCK_SIZE);
    strncpy(shift_type, shift, DP_BLOCK_SIZE-1);
    shift_type[DP_BLOCK_SIZE-1] = '\0';

    if (!strcmp(shift_type,"lsr")) {
      set_bit(instruction, SHIFT_TYPE_1);
      clear_bit(instruction, SHIFT_TYPE_2);
    }
    else if (!strcmp(shift_type,"lsl")) {
      clear_bit(instruction, SHIFT_TYPE_1);
      clear_bit(instruction, SHIFT_TYPE_2);
    }
    else if (!strcmp(shift_type,"asr")) {
      clear_bit(instruction, SHIFT_TYPE_1);
      set_bit(instruction, SHIFT_TYPE_2);
    }
    else if (!strcmp(shift_type,"ror")) {
      set_bit(instruction, SHIFT_TYPE_1);
      set_bit(instruction, SHIFT_TYPE_2);
    }

    int shift_reg = strtol(shift + OP2_SHIFT_SIZE, NULL, 0);

    if (shift[OP2_SHIFT_SIZE-1] == '#') {
      // If shift value is immediate
      *instruction |= shift_reg << OP2_SHIFT_START;
      clear_bit(instruction, OP2_SHIFYBY_IDENTIFIER);
    }
    else {
      // If shift value is a shifted register
      *instruction |= shift_reg << OP2_RS_START;
      set_bit(instruction, OP2_SHIFYBY_IDENTIFIER);
    }

  }

}
