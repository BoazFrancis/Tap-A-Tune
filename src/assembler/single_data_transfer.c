#include "assemble.h"

#define IS_LDR 1
#define NOT_LDR 0

int do_ldr(char* params, int instruction_addr, int* num_no_labels, int** memory) {
  do_sdt(params, instruction_addr, num_no_labels, memory, IS_LDR);
}

int do_str(char* params, int instruction_addr, int* num_no_labels, int** memory) {
  // NOTE: this is the same as ldr but without the numberic constant cas
  // for <address>, and L bit is NOT set

  do_sdt(params, instruction_addr, num_no_labels, memory, NOT_LDR);
}
