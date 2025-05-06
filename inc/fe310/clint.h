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

#endif /* LIBFE310_CLINT_H */
