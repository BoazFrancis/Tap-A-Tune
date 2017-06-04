#include "../lib/bitutils.h"

void read_file(char* path, char** instructions);
void build_symbol_table(char** instructions);

char* trim_whitespace(char *str);

void process_instructions(char** instructions, FILE* output);
void identify_instruction(char* mnem, char* params, FILE* output);

void write_to_file(unsigned int line, FILE* output);

int get_rotated_op(unsigned int* operand);

void do_mov(char* params, FILE* output);
void do_add(char* params, FILE* output);
void do_orr(char* params, FILE* output);
void do_sub(char* params, FILE* output);
void do_cmp(char* params, FILE* output);
void do_eor(char* params, FILE* output);
void do_tst(char* params, FILE* output);
void do_mul(char* params, FILE* output);
void do_teq(char* params, FILE* output);
void do_rsb(char* params, FILE* output);
void do_and(char* params, FILE* output);
void do_mla(char* params, FILE* output);
void do_ldr(char* params, FILE* output);
void do_str(char* params, FILE* output);
void do_beq(char* params, FILE* output);
void do_bne(char* params, FILE* output);
void do_bge(char* params, FILE* output);
void do_blt(char* params, FILE* output);
void do_bgt(char* params, FILE* output);
void do_ble(char* params, FILE* output);
void do_b(char* params, FILE* output);
void do_lsl(char* params, FILE* output);
void do_andeq(char* params, FILE* output);
