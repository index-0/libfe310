/* See LICENSE file for copyright and license details. */

#ifndef LIBFE310_CORE_CLINT_H
#define LIBFE310_CORE_CLINT_H

#include <fe310/core/hw/clint.h>
#include <fe310/types.h>

extern volatile u32 *const msip;
extern volatile u32 *const mtimecmp_lo;
extern volatile u32 *const mtimecmp_hi;
extern volatile u32 *const mtime_lo;
extern volatile u32 *const mtime_hi;

static inline void
clint_msip(bool en)
{
	*msip = en;
}

static inline void
clint_set_mtime(u64 time)
{
	*mtime_hi = time >> 32;
	*mtime_lo = time;
}

static inline u64
clint_get_mtime(void)
{
	u32 hi, lo;

	do {
		hi = *mtime_hi;
		lo = *mtime_lo;
	} while (*mtime_hi != hi);

	return ((u64)hi << 32) | lo;
}

static inline void
clint_set_mtimecmp(u64 time)
{
	*mtimecmp_hi = -1u;
	*mtimecmp_lo = time;
	*mtimecmp_hi = time >> 32;
}

static inline u64
clint_get_mtimecmp(void)
{
	return ((u64)*mtimecmp_hi << 32) | *mtimecmp_lo;
}

#endif /* LIBFE310_CORE_CLINT_H */
