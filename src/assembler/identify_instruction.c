#include <string.h>;

int isDataProcessing(char *mnem) {
  // strcmp(s1, s2) returns 0 is string s1 is the same as s2
  return !strcmp(*mnem, "add") || !strcmp(*mnem, "sub") || !strcmp(*mnem, "rsb") ||
         !strcmp(*mnem, "and") || !strcmp(*mnem, "eor") || !strcmp(*mnem, "orr") ||
         !strcmp(*mnem, "mov") || !strcmp(*mnem, "tst") || !strcmp(*mnem, "teq") ||
         !strcmp(*mnem, "cmp");
}

int isMultiply(char *mnem) {
  return !strcmp(mnem, "mul") || !strcmp(mnem, "mla");
}

int isSDT(char * mnem) {
  return !strcmp(mnem, "ldr") || !strcmp(mnem, "str");
}

int isBranch(char *mnem) {
  return !strcmp(mnem, )
}

int isSpecial(char *mnem) { // if shravan

}