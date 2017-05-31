#include <stdio.h>
#include <math.h>
#include "emulate.h"

/**
 * Extracts bits from 'start' to start+length from the 32 bit int
 * @param n - The instruction
 * @param start - The start bit position (from right to left)
 * @param length - Number of bits to extract
 * @returns the extracted bits
*/
int extract_bits(int* n, int start, int length) {

  // Set up an empty mask
  unsigned int mask = 0;

  // Fill the mask with 1s from start to length
  for (int i = 0; i < length; i++) {
    mask |= (1 << (start + i));
  }

  // Find the common bits in n
  unsigned int common = *n & mask;

  // Return just those bits i.e. ignore any zeros to the right by shifting
  return common >> start;

}

/**
 * Extracts a single bit from a longer int
 * @param n - The instruction
 * @param start - The start bit position (from right to left)
 * @returns the extracted bit
*/
int extract_bit(int* n, int start) {
  return extract_bits(n, start, 1);
}

/**
 * Returns whether the bit is set (either 1 or 0)
 * @param n - The pointer to the number
 * @param bit - The bit to check (0 indexed)
 * @returns 1 or 0 on success or failure
*/
int is_bit_set(int* n, int bit) {
  return (*n & (1 << bit)) > 0;
}

/**
 * Sets the given bit to a 1
 * @param n - The pointer to the number
 * @param bit - The bit to set
 * @returns void
*/
void set_bit(int* n, int bit) {
  *n |= (1 << bit);
}

/**
 * Sets the given bit to a 0
 * @param n - The pointer to the number
 * @param bit - The bit to clear
 * @returns void
*/
void clear_bit(int* n, int bit) {
  *n &= ~(1 << bit);
}

/**
 * Sets the given bit to 'value'
 * @param n - The pointer to the number
 * @param bit - The bit to set
 * @param value - Either 0 or 1
 * @returns void
*/
void set_bit_to(int* n, int bit, int value) {
  if (value == 1) {
    set_bit(n, bit);
  }
  else {
    clear_bit(n, bit);
  }
}

/**
 * Converts a binary number to decimal
 * @param bin - The binary number
 * @returns the unsigned decimal value
*/
unsigned int binary_to_decimal(unsigned int bin) {
  return base_to_base(2, 10, bin);
}

/**
 * Converts any number from one base to another
 * @param from - The starting base
 * @param to - The ending base
 * @param n - The original number
 * @returns the converted value
*/
unsigned int base_to_base(int from, int to, unsigned int n) {
  int new_number = 0, i = 0, rem;
  while (n != 0) {
    rem = n % from;
    n /= from;
    new_number += rem*pow(to,i);
    i++;
  }
  return new_number;
}

/**
 * Sign extend an integer
 * @param n - The original number
 * @param sbits - The starting number of bits
 * @param ebits - The ending number of bits
 * @returns the new sign extension
*/
signed int sign_extension(signed int n, int sbits, int ebits) {

  // Get the value of the (sbits)th bit of n
  int significant_bit = n & (1 << (sbits-1));

  // If MSB is 1, then fill the last (ebits-sbits) with a 1,
  // otherwise return the same number where the rest of the int are 0s
  if (significant_bit == 1) {
    for (int i=0; i<(ebits-sbits); i++) {
      n |= (1 << (sbits+i));
    }
  }

  return n;

}

/**
 * Binary rotate left
 * @param val - the number being shifted
 * @param shiftBy - the number of bits to shift by
 * @returns the rotated value
*/
unsigned int rotate_left(const unsigned int val, int shiftBy) {
  return (val << shiftBy) | (val >> (sizeof(val)*8 - shiftBy));
}

/**
 * Binary rotate right
 * @param val - the number being shifted
 * @param shiftBy - the number of bits to shift by
 * @returns the rotated value
*/
unsigned int rotate_right(const unsigned int val, int shiftBy) {
  return (val >> shiftBy) | (val << (sizeof(val)*8 - shiftBy));
}

unsigned int read_memory_bytes(struct ARM* proc, unsigned int addr) {
  unsigned int mod = addr % WORD_SIZE;
  unsigned int start_addr = addr / WORD_SIZE;
  unsigned int start_bit = mod * BITS_IN_BYTE;
  unsigned int bits_remaining = WORD_SIZE * BITS_IN_BYTE - start_bit;
  unsigned int extracted_first = extract_bits(&proc->memory[start_addr], start_bit, bits_remaining);
  unsigned int extracted_second = extract_bits(&proc->memory[start_addr+1], 0, start_bit);
  unsigned int new_second = extracted_second << bits_remaining;
  return extracted_first | new_second;
}

void write_memory_bytes(struct ARM* proc, unsigned int data, unsigned int addr) {
  unsigned int mod = addr % WORD_SIZE;
  unsigned int start_addr = addr / WORD_SIZE;
  unsigned int end_bit = mod * BITS_IN_BYTE;
  unsigned int lsb_data = extract_bits(&data, 0, WORD_SIZE * BITS_IN_BYTE - end_bit);
  unsigned int lower_memory = extract_bits(&proc->memory[start_addr], 0, end_bit);
  unsigned int new_lower_mem = lower_memory | (lsb_data << end_bit);
  unsigned int higher_memory = extract_bits(&proc->memory[start_addr+1], end_bit, WORD_SIZE * BITS_IN_BYTE - end_bit);
  unsigned int msb_data = extract_bits(&data, end_bit, WORD_SIZE * BITS_IN_BYTE - end_bit);
  unsigned int new_higher_mem = msb_data | (higher_memory << end_bit);
  // Write to memory
  proc->memory[start_addr] = new_lower_mem;
  proc->memory[start_addr+1] = new_higher_mem;
}

int reverse_int(int n) {
  int result = 0;
  for (int i = 0; i < WORD_SIZE; i++) {
    result |= extract_bits(&n, i * BITS_IN_BYTE, BITS_IN_BYTE) << (3 - i) * BITS_IN_BYTE;
  }
  return result;
}
