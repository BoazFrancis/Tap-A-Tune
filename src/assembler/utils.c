#include <ctype.h>
#include "assemble.h"

char* cat(char* m, char* r, const char* e) {

  char* result = calloc(511, sizeof(char));
  for (int i = 0; m[i] != '\0'; i++) {
    result[i] = m[i];
  }
  for (int i = 0; r[i] != '\0'; i++) {
    result[i + strlen(m)] = r[i];
  }
  for (int i = 0; e[i] != '\0'; i++) {
    result[i + strlen(m) + strlen(r)] = e[i];
  }

  return result;

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
