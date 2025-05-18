/* See LICENSE file for copyright and license details. */

#include <fe310/gpio.h>
#include <fe310/prci.h>
#include <fe310/uart.h>

volatile Uart *const uart0 __attribute__((used)) = (volatile Uart *)UART0_BASE;
volatile Uart *const uart1 __attribute__((used)) = (volatile Uart *)UART1_BASE;

void
uart_purge(volatile Uart *uart)
{
	while (uart_is_readable(uart));
}

void
uart_set_baudrate(volatile Uart *uart, UartBaudRate baud)
{
	uart_set_div(uart, prci_measure_hfclk_freq() / baud);
}

void
uart_init(volatile Uart *uart, UartBaudRate baud)
{
	u32 msk;

	if (uart == uart0)
		msk = IOF0_UART0_TX | IOF0_UART0_RX;
	else
		msk = IOF0_UART1_TX | IOF0_UART1_RX;

	uart_set_baudrate(uart, baud);
	uart_txctrl(uart, true, UART_STOP_BITS_ONE, WM_1);
	uart_rxctrl(uart, true, WM_1);

	gpio_cfg(GPIO_IOF0, msk);
}
