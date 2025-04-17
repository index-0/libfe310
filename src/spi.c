/* See LICENSE file for copyright and license details. */

#include "spi.h"

volatile Spi *const spi0 __attribute__((used)) = (volatile Spi *)SPI0_BASE;
volatile Spi *const spi1 __attribute__((used)) = (volatile Spi *)SPI1_BASE;
volatile Spi *const spi2 __attribute__((used)) = (volatile Spi *)SPI2_BASE;
