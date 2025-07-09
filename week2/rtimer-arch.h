#ifndef RTIMER_ARCH_H_
#define RTIMER_ARCH_H_

#include <stdint.h>

typedef uint32_t rtimer_clock_t;
#define RTIMER_ARCH_SECOND 1000000  // 1 MHz timer (adjust later based on hardware)

void rtimer_arch_init(void);
rtimer_clock_t rtimer_arch_now(void);
void rtimer_arch_schedule(rtimer_clock_t t);

#endif /* RTIMER_ARCH_H_ */

