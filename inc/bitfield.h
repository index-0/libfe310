/* See LICENSE file for copyright and license details. */

#ifndef FE310_BITFIELD_H
#define FE310_BITFIELD_H

#include "bits.h"

#define FMAX(msk) \
	( ((u32)(msk)) >> CTZ(msk) )
#define FFIT(msk, val) \
	( ((((u32)(val) << CTZ(msk)) & ~((u32)(msk))) == 0) )
#define FPREP(msk, val) \
	( ((u32)(val) << CTZ(msk)) & ((u32)(msk)) )
#define FGET(msk, reg) \
	( (((reg) & ((u32)(msk))) >> CTZ(msk)) )

#endif /* FE310_BITFIELD_H */
