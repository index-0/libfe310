/* See LICENSE file for copyright and license details. */

#ifndef LIBFE310_ATOMIC_H
#define LIBFE310_ATOMIC_H

#include "types.h"

static inline s32
lr_w(volatile u32 *p, s32 v)
{
	s32 r;
	__asm__ volatile (
		"lr.w %0, %2, (%1)"
		: "=r"(r)
		: "r"(p), "r"(v)
		: "memory"
	);
	return r;
}

static inline s32
sc_w(volatile u32 *p, s32 v)
{
	s32 r;
	__asm__ volatile (
		"sc.w %0, %2, (%1)"
		: "=r"(r)
		: "r"(p), "r"(v)
		: "memory"
	);
	return r;
}


static inline s32
amoswap_w(volatile u32 *p, s32 v)
{
	s32 r;
	__asm__ volatile (
		"amoswap.w %0, %2, (%1)"
		: "=r"(r)
		: "r"(p), "r"(v)
		: "memory"
	);
	return r;
}

static inline s32
amoadd_w(volatile u32 *p, s32 v)
{
	s32 r;
	__asm__ volatile (
		"amoadd.w %0, %2, (%1)"
		: "=r"(r)
		: "r"(p), "r"(v)
		: "memory"
	);
	return r;
}

static inline s32
amoxor_w(volatile u32 *p, s32 v)
{
	s32 r;
	__asm__ volatile (
		"amoxor.w %0, %2, (%1)"
		: "=r"(r)
		: "r"(p), "r"(v)
		: "memory"
	);
	return r;
}

static inline s32
amoand_w(volatile u32 *p, s32 v)
{
	s32 r;
	__asm__ volatile (
		"amoand.w %0, %2, (%1)"
		: "=r"(r)
		: "r"(p), "r"(v)
		: "memory"
	);
	return r;
}

static inline s32
amoor_w(volatile u32 *p, s32 v)
{
	s32 r;
	__asm__ volatile (
		"amoor.w %0, %2, (%1)"
		: "=r"(r)
		: "r"(p), "r"(v)
		: "memory"
	);
	return r;
}

static inline s32
amomin_w(volatile u32 *p, s32 v)
{
	s32 r;
	__asm__ volatile (
		"amomin.w %0, %2, (%1)"
		: "=r"(r)
		: "r"(p), "r"(v)
		: "memory"
	);
	return r;
}


static inline s32
amomax_w(volatile u32 *p, s32 v)
{
	s32 r;
	__asm__ volatile (
		"amomax.w %0, %2, (%1)"
		: "=r"(r)
		: "r"(p), "r"(v)
		: "memory"
	);
	return r;
}

static inline u32
amominu_w(volatile u32 *p, u32 v)
{
	s32 r;
	__asm__ volatile (
		"amominu.w %0, %2, (%1)"
		: "=r"(r)
		: "r"(p), "r"(v)
		: "memory"
	);
	return r;
}

static inline u32
amomaxu_w(volatile u32 *p, u32 v)
{
	s32 r;
	__asm__ volatile (
		"amomaxu.w %0, %2, (%1)"
		: "=r"(r)
		: "r"(p), "r"(v)
		: "memory"
	);
	return r;
}

#endif /* LIBFE310_ATOMIC_H */
