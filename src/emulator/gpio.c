#include <stdio.h>
#include "emulate.h"

void gpio(struct ARM* proc, int memory_address) {

  //int GPIO_pins[54];
  int increment = proc->gpio_initial_pin;

  if (memory_address == GPIO_20_29 || memory_address == GPIO_10_19 || memory_address == GPIO_0_9) {
    printf("One GPIO pin from %d to %d has been accessed\n", increment, increment + PINS_IN_MEMORY);
  }
  else {
    if (memory_address == PIN_ON) {
      printf("%s\n", "PIN ON");
      //clear pin at the first 3 bits of address
      clear_bit(&memory_address, increment);
    } else {
      printf("%s\n", "PIN OFF");
      //activate pin at the first 3 bits of address
      set_bit(&memory_address, increment);
    }
  }

}
