/* See LICENSE file for copyright and license details. */

#include <fe310/gpio.h>
#include <fe310/prci.h>
#include <fe310/uart.h>

volatile Uart *const uart0 __attribute__((used)) = (volatile Uart *)UART0_BASE;
volatile Uart *const uart1 __attribute__((used)) = (volatile Uart *)UART1_BASE;

void
uart_baudrate(volatile Uart *uart, u32 baud)
{
	uart_div(uart, prci_measure_hfclk_freq() / baud);
}

u32
uart_get_baudrate(volatile Uart *uart)
{
	return prci_measure_hfclk_freq() / (uart_get_div(uart) + 1);
}

void
uart_purge(volatile Uart *uart)
{
	while (uart_is_readable(uart));
}
