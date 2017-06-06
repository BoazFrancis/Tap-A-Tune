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
