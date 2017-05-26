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
