#include <stdio.h>
#include "emulate.h"

unsigned int shiftLeft(unsigned const int val, unsigned int shiftBy) {
  return val << shiftBy;
}

int logicalShiftRight(const int val, unsigned int shiftBy) {
  return val >> shiftBy;
}


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

/**
 * Sets destination register to (Rn AND operand2)
 * @param Rn
 * @param
 * @param length - Number of bits to extract
 * @returns the extracted bits
*/

void logical_and(uint32_t op2) {
  
}
/*
void eor();

void sub();

void rsb();

void add();

void tst();

void teq();

void cmp();

void orr();

void mov();
*/
