#include <stdio.h>
#include "emulate.h"



// Extract the position of the source and destination register
unsigned int srcRegPos = binary_to_decimal(extract_bits(ir, 16, 4));
unsigned int destRegPos = binary_to_decimal(extract_bits(ir, 12, 4));

// Get value of source register
unsigned int srcRegVal = proc.registers[srcRegPos];

/**
 * Extracts bits from 'start' to start+length from the 32 bit int
 * @param
 * @param start - The start bit position (from right to left)
 * @param length - Number of bits to extract
 * @returns the extracted bits
*/
and() {

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
