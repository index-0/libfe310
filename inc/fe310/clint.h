/* See LICENSE file for copyright and license details. */

#ifndef LIBFE310_CLINT_H
#define LIBFE310_CLINT_H

#include <fe310/types.h>
#include <fe310/vendor/clint.h>

extern volatile u32 *const msip;
extern volatile u32 *const mtimecmp_lo;
extern volatile u32 *const mtimecmp_hi;
extern volatile u32 *const mtime_lo;
extern volatile u32 *const mtime_hi;

static inline void
clint_set_mtime(u64 time)
{
	*mtime_hi = (u32)(time >> 32);
	*mtime_lo = (u32)time;
}

static inline u64
clint_get_mtime(void)
{
	u32 hi, lo;

	do {
		hi = *mtime_hi;
		lo = *mtime_lo;
	} while (*mtime_hi != hi);

	return lo | (((u64)hi) << 32);
}

static inline void
clint_set_mtimecmp(u64 time)
{
	*mtimecmp_hi = (u32)-1;
	*mtimecmp_lo = time;
	*mtimecmp_hi = (u32)(time >> 32);
}

static inline u64
clint_get_mtimecmp(void)
{
	return *mtimecmp_lo | (((u64)*mtimecmp_hi) << 32);
}

#endif /* LIBFE310_CLINT_H */
