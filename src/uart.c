/* See LICENSE file for copyright and license details. */

#include "uart.h"

volatile Uart *const uart0 __attribute__((used)) = (volatile Uart *)UART0_BASE;
volatile Uart *const uart1 __attribute__((used)) = (volatile Uart *)UART1_BASE;
