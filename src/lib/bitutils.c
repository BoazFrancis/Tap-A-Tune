#include <stdio.h>
#include <math.h>
#include "bitutils.h"

/**
 * Extracts bits from 'start' to start+length from the 32 bit int
 * @param n - The instruction
 * @param start - The start bit position (from right to left)
 * @param length - Number of bits to extract
 * @returns the extracted bits
*/
inline unsigned int extract_bits(unsigned int n, int start, int length) {
  if (length == BITS_IN_BYTE*WORD_SIZE) {
    return n;
  }
  unsigned int mask = ((1 << length) - 1);
  return (n >> start) & mask;
}

/**
 * Extracts a single bit from a longer int
 * @param n - The instruction
 * @param start - The start bit position (from right to left)
 * @returns the extracted bit
*/
inline unsigned int extract_bit(unsigned int n, int start) {
  return extract_bits(n, start, 1);
}

/**
 * Returns whether the bit is set (either 1 or 0)
 * @param n - The pointer to the number
 * @param bit - The bit to check (0 indexed)
 * @returns 1 or 0 on success or failure
*/
inline int is_bit_set(unsigned int* n, int bit) {
  return (*n & (1 << bit)) > 0;
}

/**
 * Sets the given bit to a 1
 * @param n - The pointer to the number
 * @param bit - The bit to set
 * @returns void
*/
inline void set_bit(unsigned int* n, int bit) {
  *n |= (1 << bit);
}

/**
 * Sets the given bit to a 0
 * @param n - The pointer to the number
 * @param bit - The bit to clear
 * @returns void
*/
inline void clear_bit(unsigned int* n, int bit) {
  *n &= ~(1 << bit);
}

/**
 * Sets the given bit to 'value'
 * @param n - The pointer to the number
 * @param bit - The bit to set
 * @param value - Either 0 or 1
 * @returns void
*/
inline void set_bit_to(unsigned int* n, int bit, int value) {
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

/**
 * For printing in test cases, reverse each byte.
 * This is due to endianess.
 * @param n - The input number as a 32-bit number
 * @returns the new formatted number
 */
unsigned int reverse_int(unsigned int n) {
  int result = 0;
  for (int i = 0; i < WORD_SIZE; i++) {
    result |= extract_bits(n, i * BITS_IN_BYTE, BITS_IN_BYTE) << (3 - i) * BITS_IN_BYTE;
  }
  return result;
}
