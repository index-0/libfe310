/* See LICENSE file for copyright and license details. */

#include <fe310/clint.h>

#define MSIP_OFS 0x0000
#define MTIMECMP_LO_OFS 0x4000
#define MTIMECMP_HI_OFS 0x4004
#define MTIME_LO_OFS 0xBFF8
#define MTIME_HI_OFS 0xBFFC

volatile u32 *const msip __attribute__((used)) =
	(volatile u32 *)(CLINT_BASE + MSIP_OFS);
volatile u32 *const mtimecmp_lo __attribute__((used)) =
	(volatile u32 *)(CLINT_BASE + MTIMECMP_LO_OFS);
volatile u32 *const mtimecmp_hi __attribute__((used)) =
	(volatile u32 *)(CLINT_BASE + MTIMECMP_HI_OFS);
volatile u32 *const mtime_lo __attribute__((used)) =
	(volatile u32 *)(CLINT_BASE + MTIME_LO_OFS);
volatile u32 *const mtime_hi __attribute__((used)) =
	(volatile u32 *)(CLINT_BASE + MTIME_HI_OFS);
