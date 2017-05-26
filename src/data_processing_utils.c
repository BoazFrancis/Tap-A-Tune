#include <stdio.h>
#include "emulate.h"



// Extract the position of the source and destination register
unsigned int srcRegPos = binary_to_decimal(extract_bits(ir, 16, 4));
unsigned int destRegPos = binary_to_decimal(extract_bits(ir, 12, 4));

// Get value of source register
unsigned int srcRegVal = proc.registers[srcRegPos];

// Extract the positions of the Rm
unsigned int rmPos = binary_to_decimal(extract_bits(ir, 0, 4));

// Get value of the Rm
int rmVal = proc.registers[rmPos];

unsigned int shiftLeft(unsigned const int val, unsigned int shiftBy) {
  return val << shiftBy;
}

int logicalShiftRight(const int val, unsigned int shiftBy) {
  return val >> shiftBy;
}


int arithmeticShiftRight(const int val, unsigned int shiftBy) {
  return sign_extension(val, 32, 32 + shiftBy) >> shiftBy;
}

/**
 * Sets destination register to (Rn AND operand2)
 * @param Rn
 * @param
 * @param length - Number of bits to extract
 * @returns the extracted bits
*/

/*
void and() {

}

eor();

sub();

rsb();

add();

tst();

teq();

cmp();

orr();

mov();
*/
