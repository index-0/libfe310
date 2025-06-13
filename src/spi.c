/* See LICENSE file for copyright and license details. */

#include <fe310/gpio.h>
#include <fe310/prci.h>
#include <fe310/spi.h>

volatile Spi *const spi0 __attribute__((used)) = (volatile Spi *)SPI0_BASE;
volatile Spi *const spi1 __attribute__((used)) = (volatile Spi *)SPI1_BASE;
volatile Spi *const spi2 __attribute__((used)) = (volatile Spi *)SPI2_BASE;

void
spi_iof_dq(volatile Spi *spi, bool en, bool dq0, bool dq1, bool dq2, bool dq3)
{
	gpio_cfg(en ? GPIO_IOF0 : GPIO_DISABLE,
			spi_msk_iof_dq(spi, dq0, dq1, dq2, dq3));
}

void
spi_iof_cs(volatile Spi *spi, bool en, bool cs0, bool cs1, bool cs2, bool cs3)
{
	gpio_cfg(en ? GPIO_IOF0 : GPIO_DISABLE,
			spi_msk_iof_cs(spi, cs0, cs1, cs2, cs3));
}

void
spi_cs_hi(volatile Spi *spi, SpiCs cs)
{
	gpio_set(spi_sel_iof_cs(spi, cs));
}

void
spi_cs_lo(volatile Spi *spi, SpiCs cs)
{
	gpio_clr(spi_sel_iof_cs(spi, cs));
}

void
spi_baudrate(volatile Spi *spi, u32 baud)
{
	spi_sckdiv(spi, prci_measure_hfclk_freq() / (2 * baud));
}

u32
spi_get_baudrate(volatile Spi *spi)
{
	return prci_measure_hfclk_freq() / (2 * (spi_get_sckdiv(spi) + 1));
}
