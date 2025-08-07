/* See LICENSE file for copyright and license details. */

#ifndef LIBFE310_AON_H
#define LIBFE310_AON_H

#include <fe310/types.h>
#include <fe310/vendor/aon.h>

#define PMU_IE_RST(state) ((state) ? BITMASK(0) : 0UL)
#define PMU_IE_RTC(state) ((state) ? BITMASK(1) : 0UL)
#define PMU_IE_DWU(state) ((state) ? BITMASK(2) : 0UL)
#define PMU_IE_ALL(state) ((state) ? GENMASK(2, 0) : 0UL)

typedef enum {
	LFEXTCLK_MUX_STATUS_EXTERNAL = 0,
	LFEXTCLK_MUX_STATUS_SOFTWARE = 1,
} LfExtClkMuxStatus;

typedef enum {
	LFEXTCLK_SEL_INTERNAL = 0,
	LFEXTCLK_SEL_EXTERNAL = 1,
} LfExtClkSel;

typedef enum {
	PMU_RESET_POR = 0,
	PMU_RESET_EXT = 256,
	PMU_RESET_WDG = 512,
	PMU_RESET_XXX = 768, /* reserved */
} PmuCauseReset;

typedef enum {
	PMU_WAKEUP_RST = 0,
	PMU_WAKEUP_RTC = 1,
	PMU_WAKEUP_DIG = 2,
	PMU_WAKEUP_ANA = 3,
} PmuCauseWakeup;

typedef enum {
	PMU_PROGRAM_WAKEUP = 0,
	PMU_PROGRAM_SLEEP = 1,
} PmuProgram;

typedef struct Aon {
	volatile u32 wdogcfg;
	u32 reserved0;
	volatile u32 wdogcount;
	u32 reserved1;
	volatile u32 wdogs;
	u32 reserved2;
	volatile u32 wdogfeed;
	volatile u32 wdogkey;
	volatile u32 wdogcmp0;
	u32 reserved3[7];
	volatile u32 rtccfg;
	u32 reserved4;
	volatile u32 rtccountlo;
	volatile u32 rtccounthi;
	volatile u32 rtcs;
	u32 reserved5[3];
	volatile u32 rtccmp0;
	u32 reserved6[3];
	volatile u32 lfrosccfg;
	u32 reserved7[2];
	volatile u32 lfclkmux;
	volatile u32 backup[16];
	u32 reserved8[16];
	volatile u32 pmuwakeupi[8];
	volatile u32 pmusleepi[8];
	volatile u32 pmuie;
	volatile u32 pmucause;
	volatile u32 pmusleep;
	volatile u32 pmukey;
	u32 reserved9[48];
	volatile u32 sifivebandgap;
	u32 reserved10[59];
	volatile u32 aoncfg;
} Aon;

typedef struct AonCfg {
	bool bandgap;
	bool bod;
	bool ldo;
	bool lfrcosc;
	bool lfrosc;
	bool lfxosc;
	bool por;
} AonCfg;

extern volatile Aon *const aon;

/*
 * WATCHDOG CONFIGURATION REGISTER (wdogcfg)
 */

static inline void
wdog_set_cfg_scale(u32 scale)
{
	aon->wdogcfg = (aon->wdogcfg & ~WDOG_CFG_SCALE) |
		(scale & WDOG_CFG_SCALE);
}

static inline u32
wdog_get_cfg_scale(void)
{
	return aon->wdogcfg & WDOG_CFG_SCALE;
}

static inline void
wdog_set_cfg_rst_en(bool en)
{
	if (en)
		aon->wdogcfg |= WDOG_CFG_RSTEN;
	else
		aon->wdogcfg &= ~WDOG_CFG_RSTEN;
}

static inline bool
wdog_is_cfg_rst_en(void)
{
	return (aon->wdogcfg & WDOG_CFG_RSTEN) != 0;
}

static inline void
wdog_set_cfg_zerocmp(bool en)
{
	if (en)
		aon->wdogcfg |= WDOG_CFG_ZEROCMP;
	else
		aon->wdogcfg &= ~WDOG_CFG_ZEROCMP;
}

static inline bool
wdog_is_cfg_zerocmp(void)
{
	return (aon->wdogcfg & WDOG_CFG_ZEROCMP) != 0;
}

static inline void
wdog_set_cfg_always_en(bool en)
{
	if (en)
		aon->wdogcfg |= WDOG_CFG_ENALWAYS;
	else
		aon->wdogcfg &= ~WDOG_CFG_ENALWAYS;
}

static inline bool
wdog_is_cfg_always_en(void)
{
	return (aon->wdogcfg & WDOG_CFG_ENALWAYS) != 0;
}

static inline void
wdog_set_cfg_coreawake(bool en)
{
	if (en)
		aon->wdogcfg |= WDOG_CFG_COREAWAKE;
	else
		aon->wdogcfg &= ~WDOG_CFG_COREAWAKE;
}

static inline bool
wdog_is_cfg_coreawake(void)
{
	return (aon->wdogcfg & WDOG_CFG_COREAWAKE) != 0;
}

static inline void
wdog_clr_cfg_ip0(void)
{
	aon->wdogcfg |= WDOG_CFG_IP0;
}

static inline bool
wdog_is_cfg_ip0(void)
{
	return (aon->wdogcfg & WDOG_CFG_IP0) != 0;
}

static inline void
wdog_cfg(u32 scale, bool rsten, bool zerocmp, bool alwaysen, bool coreawake)
{
	aon->wdogcfg = (scale & WDOG_CFG_SCALE) |
		(rsten ? WDOG_CFG_RSTEN : 0) |
		(zerocmp ? WDOG_CFG_ZEROCMP : 0) |
		(alwaysen ? WDOG_CFG_ENALWAYS : 0) |
		(coreawake ? WDOG_CFG_COREAWAKE : 0);
}

/*
 * WATCHDOG COUNT REGISTER (wdogcount)
 */

static inline void
wdog_set_count(u32 count)
{
	aon->wdogcount = count;
}

static inline u32
wdog_get_count(void)
{
	return aon->wdogcount;
}

/*
 * WATCHDOG SCALED REGISTER (wdogs)
 */

static inline u16
wdog_get_s(void)
{
	return aon->wdogs;
}

/*
 * WATCHDOG COMPARE REGISTER (wdogcmp0)
 */

static inline void
wdog_set_cmp0(u16 val)
{
	aon->wdogcmp0 = val;
}

static inline u16
wdog_get_cmp0(void)
{
	return aon->wdogcmp0;
}

/* WATCHDOG HELPERS */

static inline void
wdog_feed(void)
{
	aon->wdogfeed = WDOG_FOOD;
}

static inline void
wdog_unlock(void)
{
	aon->wdogkey = WDOG_UNLOCK;
}

/*
 * RTC CONFIGURATION REGISTER (rtccfg)
 */

static inline void
rtc_set_cfg_scale(u32 scale)
{
	aon->rtccfg = (aon->rtccfg & ~RTC_CFG_SCALE) | (scale & RTC_CFG_SCALE);
}

static inline u32
rtc_get_cfg_scale(void)
{
	return aon->rtccfg & RTC_CFG_SCALE;
}

static inline void
rtc_set_cfg_en(bool en)
{
	if (en)
		aon->rtccfg |= RTC_CFG_ENALWAYS;
	else
		aon->rtccfg &= ~RTC_CFG_ENALWAYS;
}

static inline bool
rtc_is_cfg_en(void)
{
	return (aon->rtccfg & RTC_CFG_ENALWAYS) != 0;
}

static inline void
rtc_clr_cfg_ip0(void)
{
	aon->rtccfg |= RTC_CFG_IP0;
}

static inline bool
rtc_is_cfg_ip0(void)
{
	return (aon->rtccfg & RTC_CFG_IP0) != 0;
}

static inline void
rtc_cfg(bool en, u32 scale)
{
	aon->rtccfg = (scale & RTC_CFG_SCALE) |
		(en ? RTC_CFG_ENALWAYS : 0);
}

/*
 * RTC COUNT REGISTERS (rtccounthi/rtccountlo)
 */

static inline void
rtc_set_countlo(u32 count)
{
	aon->rtccountlo = count;
}

static inline u32
rtc_get_countlo(void)
{
	return aon->rtccountlo;
}

static inline void
rtc_set_counthi(u16 count)
{
	aon->rtccounthi = count;
}

static inline u16
rtc_get_counthi(void)
{
	return aon->rtccounthi;
}

/*
 * RTC SCALED REGISTER (rtcs)
 */

static inline u32
rtc_get_s(void)
{
	return aon->rtcs;
}

/*
 * RTC COMPARE REGISTER (rtccmp0)
 */

static inline void
rtc_set_cmp0(u32 val)
{
	aon->rtccmp0 = val;
}

static inline u32
rtc_get_cmp0(void)
{
	return aon->rtccmp0;
}

/*
 * LOW-FREQUENCY RING OSCILLATOR CONFIGURATION AND STATUS REGISTER (lfrosccfg)
 */

static inline void
lfrosc_set_cfg_div(u32 div)
{
	aon->lfrosccfg = (aon->lfrosccfg & ~LFROSC_CFG_DIV) |
		(div & LFROSC_CFG_DIV);
}

static inline u32
lfrosc_get_cfg_div(void)
{
	return aon->lfrosccfg & LFROSC_CFG_DIV;
}

static inline void
lfrosc_set_cfg_trim(u32 trim)
{
	aon->lfrosccfg = (aon->lfrosccfg & ~LFROSC_CFG_TRIM) |
		((trim << CTZ(LFROSC_CFG_TRIM)) & LFROSC_CFG_TRIM);
}

static inline u32
lfrosc_get_cfg_trim(void)
{
	return (aon->lfrosccfg & LFROSC_CFG_TRIM) >>
		CTZ(LFROSC_CFG_TRIM);
}

static inline void
lfrosc_set_cfg_en(bool en)
{
	if (en)
		aon->lfrosccfg |= LFROSC_CFG_EN;
	else
		aon->lfrosccfg &= ~LFROSC_CFG_EN;
}

static inline bool
lfrosc_is_cfg_en(void)
{
	return (aon->lfrosccfg & LFROSC_CFG_EN) != 0;
}

static inline bool
lfrosc_is_cfg_rdy(void)
{
	return (s32)aon->lfrosccfg < 0;
}

static inline void
lfrosc_cfg(bool en, u32 div, u32 trim)
{
	aon->lfrosccfg = (div & LFROSC_CFG_DIV) |
		((trim << CTZ(LFROSC_CFG_TRIM)) & LFROSC_CFG_TRIM) |
		(en ? LFROSC_CFG_EN : 0);
}

/*
 * LOW-FREQUENCY CLOCK MUX CONTROL AND STATUS REGISTER (lfclkmux)
 */

static inline void
lfclkmux_set_lfextclk_sel(LfExtClkSel sel)
{
	aon->lfclkmux = sel ? LFEXTCLK_SEL_EXTERNAL : LFEXTCLK_SEL_INTERNAL;
}

static inline LfExtClkSel
lfclkmux_get_lfextclk_sel(void)
{
	return (aon->lfclkmux & LFCLKMUX_LFEXTCLK_SEL) ?
		LFEXTCLK_SEL_EXTERNAL : LFEXTCLK_SEL_INTERNAL;
}

static inline LfExtClkMuxStatus
lfclkmux_get_lfextclk_mux_status(void)
{
	return ((s32)aon->lfclkmux < 0) ? LFEXTCLK_MUX_STATUS_SOFTWARE :
		LFEXTCLK_MUX_STATUS_EXTERNAL;
}

/*
 * PMU INSTRUCTION FORMAT REGISTER (pmu(sleep/wakeup)iX)
 */

static inline void
pmu_set_ix(PmuProgram prog, u32 idx, u32 inst)
{
	volatile u32 *slot;
	if (idx >= 8) return;
	slot = prog ? &aon->pmusleepi[idx] : &aon->pmuwakeupi[idx];
	*slot = inst;
}

static inline u32
pmu_get_ix(PmuProgram prog, u32 idx)
{
	volatile u32 *slot;
	if (idx >= 8) return (u32)-1;
	slot = prog ? &aon->pmusleepi[idx] : &aon->pmuwakeupi[idx];
	return *slot;
}

/*
 * PMU INTERRUPT ENABLE REGISTER (pmuie)
 */

static inline void
pmu_set_ie(u32 msk)
{
	aon->pmuie = msk & PMU_IE;
}

static inline u32
pmu_get_ie(void)
{
	return aon->pmuie;
}

/*
 * PMU CAUSE REGISTER (pmucause)
 */

static inline PmuCauseWakeup
pmu_get_cause_wakeup(void)
{
	return (PmuCauseWakeup)(aon->pmucause & PMU_CAUSE_WAKEUP);
}

static inline PmuCauseReset
pmu_get_cause_reset(void)
{
	return (PmuCauseReset)(aon->pmucause & PMU_CAUSE_RESET);
}

/*
 * PMU SLEEP REGISTER (pmusleep)
 */

static inline void
pmu_set_sleep(void)
{
	aon->pmusleep = 0;
}

/* PMU HELPERS */

static inline u32
pmu_prep_i(u32 delay, bool out0en, bool out1en, bool corerst, bool hfclkrst,
		bool isolate)
{
	return (delay & PMU_IX_DELAY) |
		(out0en ? PMU_IX_PMU_OUT_0_EN : 0) |
		(out1en ? PMU_IX_PMU_OUT_1_EN : 0) |
		(corerst ? PMU_IX_CORERST : 0) |
		(hfclkrst ? PMU_IX_HFCLKRST : 0) |
		(isolate ? PMU_IX_ISOLATE : 0);
}

static inline void
pmu_unlock(void)
{
	aon->pmukey = PMU_UNLOCK;
}

/*
 * AON CONFIGURATION REGISTER (aoncfg)
 */

static inline void
aon_get_cfg(AonCfg *cfg)
{
	u32 reg = aon->aoncfg;

	cfg->bandgap = (reg & AON_CFG_HAS_BANDGAP) != 0;
	cfg->bod = (reg & AON_CFG_HAS_BOD) != 0;
	cfg->ldo = (reg & AON_CFG_HAS_LDO) != 0;
	cfg->lfrcosc = (reg & AON_CFG_HAS_LFRCOSC) != 0;
	cfg->lfrosc = (reg & AON_CFG_HAS_LFROSC) != 0;
	cfg->lfxosc = (reg & AON_CFG_HAS_LFXOSC) != 0;
	cfg->por = (reg & AON_CFG_HAS_POR) != 0;
}

#endif /* LIBFE310_AON_H */
