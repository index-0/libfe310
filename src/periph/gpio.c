/* See LICENSE file for copyright and license details. */

#include <fe310/periph/gpio.h>

volatile Gpio *const gpio __attribute__((used)) = (volatile Gpio *)GPIO_BASE;
