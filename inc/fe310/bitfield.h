/* See LICENSE file for copyright and license details. */

#ifndef LIBFE310_BITFIELD_H
#define LIBFE310_BITFIELD_H

#include <fe310/bits.h>

#define FMAX(msk) \
	( ((u32)(msk)) >> CTZ(msk) )
#define FFIT(msk, val) \
	( ((((u32)(val) << CTZ(msk)) & ~((u32)(msk))) == 0) )
#define FPREP(msk, val) \
	( ((u32)(val) << CTZ(msk)) & ((u32)(msk)) )
#define FGET(msk, reg) \
	( (((reg) & ((u32)(msk))) >> CTZ(msk)) )

#endif /* LIBFE310_BITFIELD_H */
