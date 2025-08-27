/* See LICENSE file for copyright and license details. */

#include <fe310/aon.h>
#include <fe310/clint.h>
#include <fe310/riscv.h>

void
delay(u32 s)
{
	u64 ticks = RTC_FREQ * (u64)s;
	u64 start = clint_get_mtime();
	while ((clint_get_mtime() - start) < ticks);
}

void
delay_ms(u32 ms)
{
	u64 ticks = (RTC_FREQ * (u64)ms) / 1000ULL;
	u64 start = clint_get_mtime();
	while ((clint_get_mtime() - start) < ticks);
}

void
delay_us(u32 hfclk, u32 us)
{
	u64 ticks = ((u64)hfclk * (u64)us + 1000000ULL - 1ULL) / 1000000ULL;
	u64 start = mcycle();
	while ((mcycle() - start) < ticks);
}
