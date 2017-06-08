#include "defs.h"

unsigned int extract_bits(unsigned int n, int start, int length);
unsigned int extract_bit(unsigned int n, int start);
int is_bit_set(unsigned int* n, int bit);
void set_bit(unsigned int* n, int bit);
void clear_bit(unsigned int* n, int bit);
void set_bit_to(unsigned int* n, int bit, int value);
unsigned int binary_to_decimal(unsigned int bin);
unsigned int base_to_base(int from, int to, unsigned int n);
signed int sign_extension(signed int n, int sbits, int ebits);
unsigned int reverse_int(unsigned int n);
unsigned int rotate_left(const unsigned int val, int shiftBy);
unsigned int rotate_right(const unsigned int val, int shiftBy);
