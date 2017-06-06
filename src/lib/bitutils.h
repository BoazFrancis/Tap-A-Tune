#include "defs.h"

int extract_bits(int* n, int start, int length);
int extract_bit(int* n, int start);
int is_bit_set(int* n, int bit);
void set_bit(int* n, int bit);
void clear_bit(int* n, int bit);
void set_bit_to(int* n, int bit, int value);
unsigned int binary_to_decimal(unsigned int bin);
unsigned int base_to_base(int from, int to, unsigned int n);
signed int sign_extension(signed int n, int sbits, int ebits);
int reverse_int(int n);
unsigned int rotate_left(const unsigned int val, int shiftBy);
unsigned int rotate_right(const unsigned int val, int shiftBy);
