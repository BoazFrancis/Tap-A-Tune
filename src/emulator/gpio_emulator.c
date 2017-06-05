#include <stdio.h>
#include "emulate.h"

void gpio_emulator(struct ARM* proc, int memory_address, const int increment) {

  //int GPIO_pins[54];

  if (memory_address == GPIO_20_29 || memory_address == GPIO_10_19 || memory_address == GPIO_0_9) {
    printf("One GPIO pin from %d to %d has been accessed\n", increment, increment + PINS_IN_MEMORY);
  }
  else {
    if (memory_address == PIN_ON) {
      printf("%s\n", "PIN ON");
      //clear pin
      clear_bit(&memory_address, increment);
    } else {
      printf("%s\n", "PIN OFF");
      //clear
      set_bit(&memory_address, increment);
    }
  }

}
