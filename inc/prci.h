/* See LICENSE file for copyright and license details. */

#ifndef LIBFE310_PRCI_H
#define LIBFE310_PRCI_H

#include "types.h"
#include "vendor/prci.h"

typedef enum {
	PRCI_PLL_REFSEL_HFROSC = 0,
	PRCI_PLL_REFSEL_HFXOSC = 1,
} PrciPllRefSel;

typedef enum {
	PRCI_PLL_SEL_HFROSC = 0,
	PRCI_PLL_SEL_PLL = 1,
} PrciPllSel;

typedef struct Prci {
	volatile u32 hfrosccfg;
	volatile u32 hfxosccfg;
	volatile u32 pllcfg;
	volatile u32 plloutdiv;
	u32 reserved[56];
	volatile u32 procmoncfg;
} Prci;

extern volatile Prci *const prci;

u32 prci_measure_hfclk_freq(void);

/*
 * RING OSCILLATOR CONFIGURATION AND STATUS (hfrosccfg)
 */

static inline void
prci_set_hfrosc_div(u32 div)
{
	prci->hfrosccfg = (prci->hfrosccfg & ~PRCI_HFROSCCFG_DIV) |
		(div & PRCI_HFROSCCFG_DIV);
}

static inline u32
prci_get_hfrosc_div(void)
{
	return prci->hfrosccfg & PRCI_HFROSCCFG_DIV;
}

static inline void
prci_set_hfrosc_trim(u32 trim)
{
	prci->hfrosccfg = (prci->hfrosccfg & ~PRCI_HFROSCCFG_TRIM) |
		((trim << CTZ(PRCI_HFROSCCFG_TRIM)) & PRCI_HFROSCCFG_TRIM);
}

static inline u32
prci_get_hfrosc_trim(void)
{
	return (prci->hfrosccfg & PRCI_HFROSCCFG_TRIM) >>
		CTZ(PRCI_HFROSCCFG_TRIM);
}

static inline void
prci_set_hfrosc_en(bool en)
{
	if (en)
		prci->hfrosccfg |= PRCI_HFROSCCFG_EN;
	else
		prci->hfrosccfg &= ~PRCI_HFROSCCFG_EN;
}

static inline bool
prci_is_hfrosc_en(void)
{
	return (prci->hfrosccfg & PRCI_HFROSCCFG_EN) != 0;
}

static inline bool
prci_is_hfrosc_rdy(void)
{
	return (s32)prci->hfrosccfg < 0;
}

static inline void
prci_hfrosc(bool en, u32 div, u32 trim)
{
	prci->hfrosccfg = (div & PRCI_HFROSCCFG_DIV) |
		((trim << CTZ(PRCI_HFROSCCFG_TRIM)) & PRCI_HFROSCCFG_TRIM) |
		(en ? PRCI_HFROSCCFG_EN : 0);
}

/*
 * CRYSTAL OSCILLATOR CONFIGURATION AND STATUS (hfxosccfg)
 */

static inline void
prci_set_hfxosc_en(bool en)
{
	if (en)
		prci->hfxosccfg |= PRCI_HFXOSCCFG_EN;
	else
		prci->hfxosccfg &= ~PRCI_HFXOSCCFG_EN;
}

static inline bool
prci_is_hfxosc_en(void)
{
	return (prci->hfxosccfg & PRCI_HFXOSCCFG_EN) != 0;
}

static inline bool
prci_is_hfxosc_rdy(void)
{
	return (s32)prci->hfxosccfg < 0;
}

/*
 * PLL CONFIGURATION AND STATUS (pllcfg)
 */

static inline void
prci_set_pll_r(u32 val)
{
	prci->pllcfg = (prci->pllcfg & ~PRCI_PLLCFG_R) |
		(val & PRCI_PLLCFG_R);
}

static inline u32
prci_get_pll_r(void)
{
	return prci->pllcfg & PRCI_PLLCFG_R;
}

static inline void
prci_set_pll_f(u32 val)
{
	prci->pllcfg = (prci->pllcfg & ~PRCI_PLLCFG_F) |
		((val << CTZ(PRCI_PLLCFG_F)) & PRCI_PLLCFG_F);
}

static inline u32
prci_get_pll_f(void)
{
	return (prci->pllcfg & PRCI_PLLCFG_F) >> CTZ(PRCI_PLLCFG_F);
}

static inline void
prci_set_pll_q(u32 val)
{
	prci->pllcfg = (prci->pllcfg & ~PRCI_PLLCFG_Q) |
		((val << CTZ(PRCI_PLLCFG_Q)) & PRCI_PLLCFG_Q);
}

static inline u32
prci_get_pll_q(void)
{
	return (prci->pllcfg & PRCI_PLLCFG_Q) >> CTZ(PRCI_PLLCFG_Q);
}

static inline void
prci_set_pll_sel(PrciPllSel sel)
{
	if (sel)
		prci->pllcfg |= PRCI_PLLCFG_SEL;
	else
		prci->pllcfg &= ~PRCI_PLLCFG_SEL;
}

static inline PrciPllSel
prci_get_pll_sel(void)
{
	return (prci->pllcfg & PRCI_PLLCFG_SEL) ?
		PRCI_PLL_SEL_PLL : PRCI_PLL_SEL_HFROSC;
}

static inline void
prci_set_pll_refsel(PrciPllRefSel sel)
{
	if (sel)
		prci->pllcfg |= PRCI_PLLCFG_REFSEL;
	else
		prci->pllcfg &= ~PRCI_PLLCFG_REFSEL;
}

static inline PrciPllRefSel
prci_get_pll_refsel(void)
{
	return (prci->pllcfg & PRCI_PLLCFG_REFSEL) ?
		PRCI_PLL_REFSEL_HFXOSC : PRCI_PLL_REFSEL_HFROSC;
}

static inline void
prci_set_pll_bypass(bool en)
{
	if (en)
		prci->pllcfg |= PRCI_PLLCFG_BYPASS;
	else
		prci->pllcfg &= ~PRCI_PLLCFG_BYPASS;
}

static inline bool
prci_is_pll_bypass(void)
{
	return (prci->pllcfg & PRCI_PLLCFG_BYPASS) != 0;
}

static inline bool
prci_is_pll_lock(void)
{
	return (s32)prci->pllcfg < 0;
}

static inline void
prci_pll(u32 r, u32 f, u32 q, PrciPllSel sel, PrciPllRefSel ref, bool bypass)
{
	prci->pllcfg = (r & PRCI_PLLCFG_R) |
		((f << CTZ(PRCI_PLLCFG_F)) & PRCI_PLLCFG_F) |
		((q << CTZ(PRCI_PLLCFG_Q)) & PRCI_PLLCFG_Q) |
		(sel ? PRCI_PLLCFG_SEL : 0) |
		(ref ? PRCI_PLLCFG_REFSEL : 0) |
		(bypass ? PRCI_PLLCFG_BYPASS : 0);
}

/*
 * PLL FINAL DIVIDE CONFIGURATION (plloutdiv)
 */

static inline void
prci_set_pllout_div(u32 div)
{
	prci->plloutdiv = (prci->plloutdiv & ~PRCI_PLLOUTDIV_DIV) |
		(div & PRCI_PLLOUTDIV_DIV);
}

static inline u32
prci_get_pllout_div(void)
{
	return prci->plloutdiv & PRCI_PLLOUTDIV_DIV;
}

static inline void
prci_set_pllout_divby1(bool en)
{
	if (en)
		prci->plloutdiv |= PRCI_PLLOUTDIV_BY1;
	else
		prci->plloutdiv &= ~PRCI_PLLOUTDIV_BY1;
}

static inline bool
prci_is_pllout_divby1(void)
{
	return (prci->plloutdiv & PRCI_PLLOUTDIV_BY1) != 0;
}

static inline void
prci_pllout(u32 div, bool divby1_en)
{
	prci->plloutdiv = (div & PRCI_PLLOUTDIV_DIV) |
		(divby1_en ? PRCI_PLLOUTDIV_BY1 : 0);
}

/*
 * PROCESS MONITOR CONFIGURATION AND STATUS (procmoncfg)
 */

static inline void
prci_set_procmon_divsel(u32 div)
{
	prci->procmoncfg = (prci->procmoncfg & ~PRCI_PROCMONCFG_DIVSEL) |
		(div & PRCI_PROCMONCFG_DIVSEL);
}

static inline u32
prci_get_procmon_divsel(void)
{
	return prci->procmoncfg & PRCI_PROCMONCFG_DIVSEL;
}

static inline void
prci_set_procmon_delaysel(u32 delay)
{
	prci->procmoncfg = (prci->procmoncfg & ~PRCI_PROCMONCFG_DELAYSEL) |
		((delay << CTZ(PRCI_PROCMONCFG_DELAYSEL)) &
		 PRCI_PROCMONCFG_DELAYSEL);
}

static inline u32
prci_get_procmon_delaysel(void)
{
	return (prci->procmoncfg & PRCI_PROCMONCFG_DELAYSEL) >>
		CTZ(PRCI_PROCMONCFG_DELAYSEL);
}

static inline void
prci_set_procmon_en(bool en)
{
	if (en)
		prci->procmoncfg |= PRCI_PROCMONCFG_EN;
	else
		prci->procmoncfg &= ~PRCI_PROCMONCFG_EN;
}

static inline bool
prci_is_procmon_en(void)
{
	return (prci->procmoncfg & PRCI_PROCMONCFG_EN) != 0;
}

static inline void
prci_set_procmon_sel(u32 sel)
{
	prci->procmoncfg = (prci->procmoncfg & ~PRCI_PROCMONCFG_SEL) |
		((sel << CTZ(PRCI_PROCMONCFG_SEL)) & PRCI_PROCMONCFG_SEL);
}

static inline u32
prci_get_procmon_sel(void)
{
	return (prci->procmoncfg & PRCI_PROCMONCFG_SEL) >>
		CTZ(PRCI_PROCMONCFG_SEL);
}

static inline void
prci_procmon(bool en, u32 divsel, u32 delaysel, u32 sel)
{
	prci->procmoncfg = (divsel & PRCI_PROCMONCFG_DIVSEL) |
		((delaysel << CTZ(PRCI_PROCMONCFG_DELAYSEL)) &
		 PRCI_PROCMONCFG_DELAYSEL) |
		(en ? PRCI_PROCMONCFG_EN : 0) |
		((sel << CTZ(PRCI_PROCMONCFG_SEL)) & PRCI_PROCMONCFG_SEL);
}

#endif /* LIBFE310_PRCI_H */
