#include "contiki.h"
#include "dev/leds.h"

void platform_init(void)
{
  leds_init();
}

