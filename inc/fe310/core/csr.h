/* See LICENSE file for copyright and license details. */

#ifndef LIBFE310_CORE_CSR_H
#define LIBFE310_CORE_CSR_H

#include <fe310/types.h>

static inline u64
mcycle(void)
{
       u32 hi, hi2, lo;

       __asm__ volatile(
               "1:\n\t"
               "csrr %0, mcycleh\n\t"
               "csrr %1, mcycle\n\t"
               "csrr %2, mcycleh\n\t"
               "bne  %0, %2, 1b\n\t"
               : "=r" (hi), "=r" (lo), "=r" (hi2)
       );

       return lo | ((u64)hi << 32);
}

#endif /* LIBFE310_CORE_CSR_H */
