/* See LICENSE file for copyright and license details. */

#ifndef FE310_CLINT_H
#define FE310_CLINT_H

#include "types.h"
#include "vendor/clint.h"

extern volatile u32 *const msip;
extern volatile u32 *const mtimecmp_lo;
extern volatile u32 *const mtimecmp_hi;
extern volatile u32 *const mtime_lo;
extern volatile u32 *const mtime_hi;

#endif /* FE310_CLINT_H */
