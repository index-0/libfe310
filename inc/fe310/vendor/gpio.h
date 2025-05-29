/* See LICENSE file for copyright and license details. */

#ifndef LIBFE310_VENDOR_GPIO_H
#define LIBFE310_VENDOR_GPIO_H

#include <fe310/bits.h>

#define GPIO_BASE 0x10012000

#define GPIO_PIN(n) BITMASK(n)

#define LED_R GPIO_PIN(22)
#define LED_G GPIO_PIN(19)
#define LED_B GPIO_PIN(21)

#define PIN_0 GPIO_PIN(16)
#define PIN_1 GPIO_PIN(17)
#define PIN_2 GPIO_PIN(18)
#define PIN_3 GPIO_PIN(19)
#define PIN_4 GPIO_PIN(20)
#define PIN_5 GPIO_PIN(21)
#define PIN_6 GPIO_PIN(22)
#define PIN_7 GPIO_PIN(23)

#define PIN_8 GPIO_PIN(0)
#define PIN_9 GPIO_PIN(1)
#define PIN_10 GPIO_PIN(2)
#define PIN_11 GPIO_PIN(3)
#define PIN_12 GPIO_PIN(4)
#define PIN_13 GPIO_PIN(5)

/* #define PIN_14 NO_CONNECT */
#define PIN_15 GPIO_PIN(9)
#define PIN_16 GPIO_PIN(10)
#define PIN_17 GPIO_PIN(11)
#define PIN_18 GPIO_PIN(12)
#define PIN_19 GPIO_PIN(13)

#endif /* LIBFE310_VENDOR_GPIO_H */
