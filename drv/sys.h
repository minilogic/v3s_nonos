#ifndef SYS_H
#define SYS_H

#include "v3s.h"
#include "display.h"
#include "spi.h"

#define ctr_us  (TIM->AVS_CNT0)
#define ctr_ms  (TIM->AVS_CNT1)
void delay (u32 ms);
void udelay (u32 us);

int kbhit(void);
void dump (void *ptr, uint16_t len);

#endif
