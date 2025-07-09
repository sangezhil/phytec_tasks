#include <stdint.h>
#include "contiki.h"
#include "dev/leds.h"
#include <stdio.h>

PROCESS(led_blink_process, "LED Blink Process");
AUTOSTART_PROCESSES(&led_blink_process);

PROCESS_THREAD(led_blink_process, ev, data)
{
  static struct etimer timer;
  static uint8_t led_on = 0;

  PROCESS_BEGIN();

  printf("Starting LED Blink on EFR32ZG28...\n");

  etimer_set(&timer, CLOCK_SECOND);  // 1 second interval

  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));

    if(led_on) {
      leds_off(LEDS_ALL);
      led_on = 0;
    } else {
      leds_on(LEDS_ALL);
      led_on = 1;
    }

    etimer_reset(&timer);
  }

  PROCESS_END();
}

