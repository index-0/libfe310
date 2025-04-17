/* See LICENSE file for copyright and license details. */

#ifndef FE310_BITS_H
#define FE310_BITS_H

#define BITMASK(nr) (1UL << ((nr) % 31))
#define GENMASK(h, l) (((~0UL) - (1UL << (l)) + 1) & (~0UL >> (31 - (h))))

#define CTZ(x) ((u32)(x) ? (u32)__builtin_ctzl((u32)(x)) : 0UL)

#endif /* FE310_BITS_H */
