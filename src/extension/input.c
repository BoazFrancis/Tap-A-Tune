#include <stdio.h>
#include "extension.h"

char read_char() {
  char character;
  // ignore the leading space in the input
  scanf(" %c", &character);
  return character;
}

int main() {
  printf("%c\n", read_char());
  return 0;
}
