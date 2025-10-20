/* See LICENSE file for copyright and license details. */

#ifndef LIBFE310_DELAY_H
#define LIBFE310_DELAY_H

#include <fe310/types.h>

void delay(u32 s);
void delay_ms(u32 ms);
void delay_us(u32 hfclk, u32 us);

#endif /* LIBFE310_DELAY_H */
