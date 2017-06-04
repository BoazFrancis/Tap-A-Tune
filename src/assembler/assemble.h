#include "map.h"
#include "../lib/bitutils.h"

int read_file(char* path, char** instructions);
void build_symbol_table(int count, char** instructions, SymbolTable* st);

char* trim_whitespace(char *str);

void process_instructions(char** instructions, FILE* output, SymbolTable* st);
int identify_instruction(char* mnem, char* params, SymbolTable* st);

void write_to_file(unsigned int line, FILE* output);

int get_rotated_op(unsigned int* operand);

int do_mov(char* params);
int do_add(char* params);
int do_orr(char* params);
int do_sub(char* params);
int do_cmp(char* params);
int do_eor(char* params);
int do_tst(char* params);
int do_mul(char* params);
int do_teq(char* params);
int do_rsb(char* params);
int do_and(char* params);
int do_mla(char* params);
int do_ldr(char* params);
int do_str(char* params);
int do_beq(char* params);
int do_bne(char* params);
int do_bge(char* params);
int do_blt(char* params);
int do_bgt(char* params);
int do_ble(char* params);
int do_b(char* params, SymbolTable* st);
int do_lsl(char* params);
int do_andeq(char* params);
