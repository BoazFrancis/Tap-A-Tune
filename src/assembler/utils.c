#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
