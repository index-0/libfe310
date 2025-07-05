/* See LICENSE file for copyright and license details. */

#include <fe310/gpio.h>
#include <fe310/prci.h>
#include <fe310/uart.h>

volatile Uart *const uart0 __attribute__((used)) = (volatile Uart *)UART0_BASE;
volatile Uart *const uart1 __attribute__((used)) = (volatile Uart *)UART1_BASE;

void
uart_iof(volatile Uart *uart, bool en, bool tx, bool rx)
{
	gpio_cfg(en ? GPIO_IOF0 : GPIO_DISABLE, uart_msk_iof(uart, tx, rx));
}

void
uart_baudrate(volatile Uart *uart, u32 hfclk, u32 baud)
{
	u32 rdiv = hfclk / baud;
	uart_div(uart, rdiv > 0 ? rdiv - 1 : 0);
}

u32
uart_get_baudrate(volatile Uart *uart, u32 hfclk)
{
	return hfclk / (uart_get_div(uart) + 1);
}

void
uart_purge(volatile Uart *uart)
{
	while (uart_is_readable(uart));
}
