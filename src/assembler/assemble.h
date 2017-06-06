#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/bitutils.h"
#include "map.h"

// Loading in the assembly file
int read_file(FILE* input, int num_lines, char** instructions);
int count_lines(FILE* input);
int build_symbol_table(int total_size, char** instructions, SymbolTable* st);

// Utility methods
char* cat(char* m, char* r, const char* e);
char* trim_whitespace(char *str);
int get_rotated_op(unsigned int* operand);

// Processing instructions
void process_instructions(int total_size, int* num_no_labels, char** instructions, FILE* output, SymbolTable* st);
int identify_instruction(char* mnem, char* params, SymbolTable* st, int addr, int* num_no_labels, int** memory);

// Output
void write_to_file(unsigned int line, FILE* output);

// Data processing
int do_mov(char* params);
int do_add(char* params);
int do_orr(char* params);
int do_sub(char* params);
int do_cmp(char* params);
int do_eor(char* params);
int do_tst(char* params);
int do_teq(char* params);
int do_rsb(char* params);
int do_and(char* params);

// Multiply instructions
int do_mul(char* params);
int do_mla(char* params);

// Special instructions
int do_lsl(char* params);
int do_andeq(char* params);

// Single data transfer
int do_ldr(char* params, int instruction_addr, int* num_no_labels, int** memory);
int do_str(char* params);

// Branch instructions
int do_branch(char* params, SymbolTable* st, int addr, unsigned int cond);
int do_b(char* params, SymbolTable* st, int addr);
int do_beq(char* params, SymbolTable* st, int addr);
int do_bne(char* params, SymbolTable* st, int addr);
int do_bge(char* params, SymbolTable* st, int addr);
int do_blt(char* params, SymbolTable* st, int addr);
int do_bgt(char* params, SymbolTable* st, int addr);
int do_ble(char* params, SymbolTable* st, int addr);
