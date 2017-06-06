#include "map.h"
#include "../lib/bitutils.h"

int read_file(char* path, char** instructions);
int build_symbol_table(int total_size, char** instructions, SymbolTable* st);

char* trim_whitespace(char *str);

void process_instructions(int total_size, int* num_no_labels, char** instructions, FILE* output, SymbolTable* st);
int identify_instruction(char* mnem, char* params, SymbolTable* st, int addr, int* num_no_labels, int** memory);

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
int do_ldr(char* params, int instruction_addr, int* num_no_labels, int** memory);
int do_str(char* params);
int do_lsl(char* params);
int do_andeq(char* params);

int do_branch(char* params, SymbolTable* st, int addr, unsigned int cond);
int do_b(char* params, SymbolTable* st, int addr);
int do_beq(char* params, SymbolTable* st, int addr);
int do_bne(char* params, SymbolTable* st, int addr);
int do_bge(char* params, SymbolTable* st, int addr);
int do_blt(char* params, SymbolTable* st, int addr);
int do_bgt(char* params, SymbolTable* st, int addr);
int do_ble(char* params, SymbolTable* st, int addr);

char* cat(char* m, char* r, const char* e);
int do_ldr_reg(unsigned int instruction, unsigned int cond, unsigned int rd, char* addr_str);
