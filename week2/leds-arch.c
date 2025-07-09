#include "contiki.h"
#include "dev/leds.h"
#include <stdint.h>

#define GPIO_PA_MODEL     (*(volatile uint32_t *)0x40006004)
#define GPIO_PA_DOUT      (*(volatile uint32_t *)0x4000600C)
#define GPIO_PA_DOUTSET   (*(volatile uint32_t *)0x40006018)
#define GPIO_PA_DOUTCLR   (*(volatile uint32_t *)0x4000601C)

#define LED_PIN           5  // Change if your LED is on a different pin

void leds_arch_init(void) {
  // Configure PA5 as push-pull output (mode = 0x1)
  GPIO_PA_MODEL &= ~(0xF << (LED_PIN * 4));  // Clear mode
  GPIO_PA_MODEL |=  (0x1 << (LED_PIN * 4));  // Set to push-pull
}

void leds_arch_set(unsigned char leds) {
  if(leds & LEDS_GREEN) {
    GPIO_PA_DOUTSET = (1 << LED_PIN);
  } else {
    GPIO_PA_DOUTCLR = (1 << LED_PIN);
  }
}

unsigned char leds_arch_get(void) {
  return (GPIO_PA_DOUT & (1 << LED_PIN)) ? LEDS_GREEN : 0;
}

