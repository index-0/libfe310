/* See LICENSE file for copyright and license details. */

#ifndef LIBFE310_UART_H
#define LIBFE310_UART_H

#include <fe310/atomic.h>
#include <fe310/periph.h>
#include <fe310/types.h>
#include <fe310/vendor/uart.h>

#define UART_IOF_TX true, false
#define UART_IOF_RX false, true
#define UART_IOF_TXRX true, true

typedef enum {
	UART_STOP_BITS_ONE = 0,
	UART_STOP_BITS_TWO = 1,
} UartStopBits;

typedef struct Uart {
	volatile u32 txdata;
	volatile u32 rxdata;
	volatile u32 txctrl;
	volatile u32 rxctrl;
	volatile u32 ie;
	volatile u32 ip;
	volatile u32 div;
} Uart;

extern volatile Uart *const uart0;
extern volatile Uart *const uart1;

void uart_iof(volatile Uart *uart, bool en, bool tx, bool rx);
void uart_baudrate(volatile Uart *uart, u32 baud);
u32 uart_get_baudrate(volatile Uart *uart);
void uart_purge(volatile Uart *uart);

/*
 * TRANSMIT DATA REGISTER (txdata)
 */

static inline void
uart_putc(volatile Uart *uart, u8 c) {
	s32 r;
	do
		r = amoor_w(&uart->txdata, c);
	while (r < 0);
}

static inline bool
uart_is_writable(volatile Uart *uart)
{
	return ((s32)uart->txdata >= 0);
}

/*
 * RECEIVE DATA REGISTER (rxdata)
 */

static inline u8
uart_getc(volatile Uart *uart)
{
	s32 r;
	do
		r = uart->rxdata;
	while (r < 0);
	return (u8)r;
}

static inline bool
uart_is_readable(volatile Uart *uart)
{
	return ((s32)uart->rxdata >= 0);
}

/*
 * TRANSMIT CONTROL REGISTER (txctrl)
 */


static inline void
uart_set_txctrl_tx_en(volatile Uart *uart, bool en)
{
	if (en)
		uart->txctrl |= UART_TXCTRL_TXEN;
	else
		uart->txctrl &= ~UART_TXCTRL_TXEN;
}

static inline bool
uart_is_txctrl_tx_en(volatile Uart *uart)
{
	return (uart->txctrl & UART_TXCTRL_TXEN) != 0;
}

static inline void
uart_set_txctrl_nstop(volatile Uart *uart, UartStopBits nsb)
{
	if (nsb)
		uart->txctrl |= UART_TXCTRL_NSTOP;
	else
		uart->txctrl &= ~UART_TXCTRL_NSTOP;
}

static inline UartStopBits
uart_get_txctrl_nstop(volatile Uart *uart)
{
	return (uart->txctrl & UART_TXCTRL_NSTOP) ?
		UART_STOP_BITS_TWO : UART_STOP_BITS_ONE;
}

static inline void
uart_set_txctrl_txcnt(volatile Uart *uart, WaterMarkLevel wm)
{
	uart->txctrl = (uart->txctrl & ~UART_TXCTRL_TXCNT) |
		((wm << CTZ(UART_TXCTRL_TXCNT)) & UART_TXCTRL_TXCNT);
}

static inline u32
uart_get_txctrl_txcnt(volatile Uart *uart)
{
	return (uart->txctrl & UART_TXCTRL_TXCNT) >> CTZ(UART_TXCTRL_TXCNT);
}

static inline void
uart_txctrl(volatile Uart *uart, bool en, UartStopBits sb,
		WaterMarkLevel wm)
{
	uart->txctrl = (en ? UART_TXCTRL_TXEN : 0) |
		(sb ? UART_TXCTRL_NSTOP : 0) |
		((wm << CTZ(UART_TXCTRL_TXCNT)) & UART_TXCTRL_TXCNT);
}

/*
 * RECEIVE CONTROL REGISTER (rxctrl)
 */

static inline void
uart_set_rxctrl_rx_en(volatile Uart *uart, bool en)
{
	if (en)
		uart->rxctrl |= UART_RXCTRL_RXEN;
	else
		uart->rxctrl &= ~UART_RXCTRL_RXEN;
}

static inline bool
uart_is_rxctrl_rx_en(volatile Uart *uart)
{
	return (uart->rxctrl & UART_RXCTRL_RXEN) != 0;
}

static inline void
uart_set_rxctrl_rxcnt(volatile Uart *uart, WaterMarkLevel wm)
{
	uart->rxctrl = (uart->rxctrl & ~UART_RXCTRL_RXCNT) |
		((wm << CTZ(UART_RXCTRL_RXCNT)) & UART_RXCTRL_RXCNT);
}

static inline WaterMarkLevel
uart_get_rxctrl_rxcnt(volatile Uart *uart)
{
	return (uart->rxctrl & UART_RXCTRL_RXCNT) >> CTZ(UART_RXCTRL_RXCNT);
}

static inline void
uart_rxctrl(volatile Uart *uart, bool en, WaterMarkLevel wm)
{
	uart->rxctrl = (en ? UART_RXCTRL_RXEN : 0) |
		((wm << CTZ(UART_RXCTRL_RXCNT)) & UART_RXCTRL_RXCNT);
}

/*
 * INTERRUPT ENABLE REGISTER (ie)
 */

static inline void
uart_set_txwm_ie(volatile Uart *uart, bool en)
{
	if (en)
		uart->ie |= UART_IE_TXWM;
	else
		uart->ie &= ~UART_IE_TXWM;
}

static inline bool
uart_is_txwm_ie(volatile Uart *uart)
{
	return (uart->ie & UART_IE_TXWM) != 0;
}

static inline void
uart_set_rxwm_ie(volatile Uart *uart, bool en)
{
	if (en)
		uart->ie |= UART_IE_RXWM;
	else
		uart->ie &= ~UART_IE_RXWM;
}

static inline bool
uart_is_rxwm_ie(volatile Uart *uart)
{
	return (uart->ie & UART_IE_RXWM) != 0;
}

/*
 * INTERRUPT PENDING REGISTER (ip)
 */

static inline bool
uart_is_txwm_ip(volatile Uart *uart)
{
	return uart->ip & UART_IP_TXWM;
}

static inline bool
uart_is_rxwm_ip(volatile Uart *uart)
{
	return (uart->ip & UART_IP_RXWM) != 0;
}

/*
 * BAUD RATE DIVISOR REGISTER (div)
 */

static inline void
uart_div(volatile Uart *uart, u16 div)
{
	uart->div = div;
}

static inline u16
uart_get_div(volatile Uart *uart)
{
	return uart->div;
}

/*
 * HELPER
 */

static inline u32
uart_device(volatile Uart *uart)
{
	if (uart == uart1) return 1;
	else return 0;
}

static inline u32
uart_iof_msk(volatile Uart *uart, bool tx, bool rx)
{
	switch(uart_device(uart)) {
	case 0:
		return (tx ? IOF0_UART0_TX : 0) | (rx ? IOF0_UART0_RX : 0);
	case 1:
		return (tx ? IOF0_UART1_TX : 0) | (rx ? IOF0_UART1_RX : 0);
	default:
		return 0;
	}
}

#endif /* LIBFE310_UART_H */
