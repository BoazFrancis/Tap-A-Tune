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
