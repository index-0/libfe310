/* See LICENSE file for copyright and license details. */

#include <fe310/clint.h>
#include <fe310/prci.h>

#define RTC_FREQ 32768

volatile Prci *const prci __attribute__((used)) = (volatile Prci *)PRCI_BASE;

static inline __attribute__((always_inline)) void
mcycle(u64 *cycles)
{
	u32 hi, hi_tmp, lo;

	__asm__ volatile(
		"1:\n\t"
		"csrr %0, mcycleh\n\t"
		"csrr %1, mcycle\n\t"
		"csrr %2, mcycleh\n\t"
		"bne  %0, %2, 1b\n\t"
		: "=r" (hi), "=r" (lo), "=r" (hi_tmp)
	);

	*cycles = lo | ((u64)hi << 32);
}

u32
prci_measure_hfclk_freq(void)
{
	u32 last, next, tmp;
	u64 lmc, nmc;

	do {
		last = *mtime_lo;
		next = last + RTC_FREQ + 1;
	} while (next < last);

	tmp = last;

	do {
		last = *mtime_lo;
	} while (last == tmp);

	mcycle(&lmc);

	while (*mtime_lo < next);

	mcycle(&nmc);

	return nmc - lmc;
}
