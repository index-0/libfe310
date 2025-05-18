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
uart_set_baudrate(volatile Uart *uart, u32 baud)
{
	uart_set_div(uart, prci_measure_hfclk_freq() / baud);
}

u32
uart_get_baudrate(volatile Uart *uart)
{
	return prci_measure_hfclk_freq() / (uart_get_div(uart) + 1);
}

void
uart_close(volatile Uart *uart)
{
	u32 msk = uart_iof_msk(uart, true, true);

	uart_set_txctrl_tx_en(uart, false);
	uart_set_rxctrl_rx_en(uart, false);

	gpio_cfg(GPIO_DISABLE, msk);
}

void
uart_init(volatile Uart *uart, u32 baud)
{
	u32 msk = uart_iof_msk(uart, true, true);

	uart_set_baudrate(uart, baud);
	uart_txctrl(uart, true, UART_STOP_BITS_ONE, WM_1);
	uart_rxctrl(uart, true, WM_1);

	gpio_cfg(GPIO_IOF0, msk);
}
