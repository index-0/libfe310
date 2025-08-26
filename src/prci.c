/* See LICENSE file for copyright and license details. */

#include <fe310/clint.h>
#include <fe310/prci.h>
#include <fe310/riscv.h>

#define RTC_FREQ 32768

volatile Prci *const prci __attribute__((used)) = (volatile Prci *)PRCI_BASE;

u32
prci_measure_hfclk(u32 ticks)
{
	u32 last, next, tmp;
	u64 delta, lmc, nmc;

	do {
		last = *mtime_lo;
		next = last + ticks + 1;
	} while (next < last);

	tmp = last;

	do {
		last = *mtime_lo;
	} while (last == tmp);

	lmc = mcycle();

	while (*mtime_lo < next);

	nmc = mcycle();

	delta = nmc - lmc;

	return (delta * RTC_FREQ) / (ticks + 1);
}
