#include <stdio.h>
#include "emulate.h"

/**
 * Reserve the last 3 bytes of memory to store GPIO pins
 * @param proc - The pointer to the processor
 * @returns void
 */
void setGPIO(ARM *proc) {
	proc->memory[MAX_MEMORY_SIZE - 3] = GPIO_0_9;
	proc->memory[MAX_MEMORY_SIZE - 2] = GPIO_10_19;
	proc->memory[MAX_MEMORY_SIZE - 1] = GPIO_20_29;
}

/**
 * Clear the GPIO bits from memory
 * @param proc - The pointer to the processor
 * @returns void
 */
void clearGPIO(ARM *proc) {
	proc->memory[MAX_MEMORY_SIZE - 3] = 0;
	proc->memory[MAX_MEMORY_SIZE - 2] = 0;
	proc->memory[MAX_MEMORY_SIZE - 1] = 0;
}

/**
 * Using the given memory address, see whether we have accessed any of the
 * GPIO locations in memory.
 * Modifies the memory address to 1 word below the current pin location
 * @param proc - The pointer to the processor
 * @param memory_address - A pointer to the memory address
 * @returns whether or not to continue execution
 */
int getGPIO(ARM *proc, int *memory_address) {

  switch (*memory_address) {

    case PIN_ON:
      printf("PIN ON\n");
      return 1;

    case PIN_OFF:
      printf("PIN OFF\n");
      return 1;

    case GPIO_0_9:
      printf("One GPIO pin from 0 to 9 has been accessed\n");
      break;

    case GPIO_10_19:
      printf("One GPIO pin from 10 to 19 has been accessed\n");
      break;

    case GPIO_20_29:
      printf("One GPIO pin from 20 to 29 has been accessed\n");
      break;

    default:
      return 0;

  }

  // New memory address is 1 word below the position of the GPIO pins
  *memory_address = ((MAX_MEMORY_SIZE - ((*memory_address - GPIO_0_9) / WORD_SIZE)) - 1) * WORD_SIZE;

  return 0;

}
