#include <stdio.h>
#include "emulate.h"

/**
 * Performs shift to the left (logical = arithmetic) on 'val'
 * @param val - The value being shifted
 * @param shiftBy - The number of bits shifted by
 * @returns the value shifted left by the specified number of bits
*/
unsigned int shiftLeft(unsigned const int val, unsigned int shiftBy) {
  return val << shiftBy;
}

/**
 * Performs logical shift to the right on 'val'
 * @param val - The value being shifted
 * @param shiftBy - The number of bits shifted by
 * @returns the value shifted (logical) right by the specified number of bits
*/
int logicalShiftRight(const int val, unsigned int shiftBy) {
  return val >> shiftBy;
}

/**
 * Performs arithmetic shift to the right on 'val'
 * @param val - The value being shifted
 * @param shiftBy - The number of bits shifted by
 * @returns the value shifted (arithmetic) right by the specified number of bits
*/
int arithmeticShiftRight(const int val, unsigned int shiftBy) {
  return sign_extension(val, 32, 32 + shiftBy) >> shiftBy;
}

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
 * Performs the shift operation according to the specified shift type on 'val'
 * by the specified number of bits
 * @param shiftType - shift type
 * @param val - The value being shifted
 * @param shiftBy - The number of bits shifted by
 * @returns returns the shifted value
*/
unsigned int shift_by_type(unsigned int shiftType, unsigned int val, unsigned int shiftBy) {
  switch (shiftType) {
    // logical shift left
    case LOGICAL_LEFT:
      return shiftLeft(val, shiftBy);
    // logical shift right
    case LOGICAL_RIGHT:
      return logicalShiftRight(val , shiftBy);
    // arithmetic shift right
    case ARITHMETIC_RIGHT:
      return arithmeticShiftRight(val, shiftBy);
    // rotate right
    case ROTATE_RIGHT:
      return rotate_right(val, shiftBy);
  }
}
