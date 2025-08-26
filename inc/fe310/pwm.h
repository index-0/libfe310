/* See LICENSE file for copyright and license details. */

#ifndef LIBFE310_PWM_H
#define LIBFE310_PWM_H

#include <fe310/types.h>
#include <fe310/vendor/pwm.h>

#define PWMCMP0_BIT BITMASK(0)
#define PWMCMP1_BIT BITMASK(1)
#define PWMCMP2_BIT BITMASK(2)
#define PWMCMP3_BIT BITMASK(3)

typedef enum {
	PWMCMP0,
	PWMCMP1,
	PWMCMP2,
	PWMCMP3,
} PwmCmp;

typedef struct Pwm {
	volatile u32 cfg;
	u32 reserved0;
	volatile u32 count;
	u32 reserved1;
	volatile u32 s;
	u32 reserved2[3];
	volatile u32 cmp[4];
} Pwm;

extern volatile Pwm *const pwm0;
extern volatile Pwm *const pwm1;
extern volatile Pwm *const pwm2;

void pwm_iof(volatile Pwm *pwm, bool en,
	bool pwm0, bool pwm1, bool pwm2, bool pwm3);
u32 pwm_prep_cmp0(volatile Pwm *pwm, u32 hfclk, u32 freq, u32 *scale);
u32 pwm_prep_cmpx(u32 cmp0, u32 duty);

/*
 * PWM CONFIGURATION REGISTER (pwmcfg)
 */

static inline void
pwm_set_cfg_scale(volatile Pwm *pwm, u32 scale)
{
	pwm->cfg = (pwm->cfg & ~PWM_CFG_SCALE) | (scale & PWM_CFG_SCALE);
}

static inline u32
pwm_get_cfg_scale(volatile Pwm *pwm)
{
	return (pwm->cfg & PWM_CFG_SCALE);
}

static inline void
pwm_set_cfg_sticky(volatile Pwm *pwm, bool en)
{
	if (en)
		pwm->cfg |= PWM_CFG_STICKY;
	else
		pwm->cfg &= ~PWM_CFG_STICKY;
}

static inline bool
pwm_is_cfg_sticky(volatile Pwm *pwm)
{
	return (pwm->cfg & PWM_CFG_STICKY) != 0;
}

static inline void
pwm_set_cfg_zerocmp(volatile Pwm *pwm, bool en)
{
	if (en)
		pwm->cfg |= PWM_CFG_ZEROCMP;
	else
		pwm->cfg &= ~PWM_CFG_ZEROCMP;
}

static inline bool
pwm_is_cfg_zerocmp(volatile Pwm *pwm)
{
	return (pwm->cfg & PWM_CFG_ZEROCMP) != 0;
}

static inline void
pwm_set_cfg_deglitch(volatile Pwm *pwm, bool en)
{
	if (en)
		pwm->cfg |= PWM_CFG_DEGLITCH;
	else
		pwm->cfg &= ~PWM_CFG_DEGLITCH;
}

static inline bool
pwm_is_cfg_deglitch(volatile Pwm *pwm)
{
	return (pwm->cfg & PWM_CFG_DEGLITCH) != 0;
}

static inline void
pwm_set_cfg_en(volatile Pwm *pwm, bool en)
{
	if (en)
		pwm->cfg |= PWM_CFG_ENALWAYS;
	else
		pwm->cfg &= ~PWM_CFG_ENALWAYS;
}

static inline bool
pwm_is_cfg_en(volatile Pwm *pwm)
{
	return (pwm->cfg & PWM_CFG_ENALWAYS) != 0;
}

static inline void
pwm_set_cfg_oneshot(volatile Pwm *pwm, bool en)
{
	if (en)
		pwm->cfg |= PWM_CFG_ENONESHOT;
	else
		pwm->cfg &= ~PWM_CFG_ENONESHOT;
}

static inline bool
pwm_is_pwmcfg_oneshot_en(volatile Pwm *pwm)
{
	return (pwm->cfg & PWM_CFG_ENONESHOT) != 0;
}

static inline void
pwm_set_cfg_center(volatile Pwm *pwm, u32 cmp)
{
	pwm->cfg = (pwm->cfg & ~PWM_CFG_CMPnCENTER) |
		((cmp << CTZ(PWM_CFG_CMPnCENTER)) & PWM_CFG_CMPnCENTER);
}

static inline u32
pwm_get_cfg_center(volatile Pwm *pwm)
{
	return (pwm->cfg & PWM_CFG_CMPnCENTER) >> CTZ(PWM_CFG_CMPnCENTER);
}

static inline void
pwm_set_cfg_gang(volatile Pwm *pwm, u32 cmp)
{
	pwm->cfg = (pwm->cfg & ~PWM_CFG_CMPnGANG) |
		((cmp << CTZ(PWM_CFG_CMPnGANG)) & PWM_CFG_CMPnGANG);
}

static inline u32
pwm_get_cfg_gang(volatile Pwm *pwm)
{
	return (pwm->cfg & PWM_CFG_CMPnGANG) >> CTZ(PWM_CFG_CMPnGANG);
}

static inline void
pwm_clr_cfg_ip(volatile Pwm *pwm, u32 cmp)
{
	pwm->cfg |= ((cmp << CTZ(PWM_CFG_CMPnIP)) & PWM_CFG_CMPnIP);
}

static inline u32
pwm_get_cfg_ip(volatile Pwm *pwm)
{
	return (pwm->cfg & PWM_CFG_CMPnIP) >> CTZ(PWM_CFG_CMPnIP);
}

static inline void
pwm_cfg(volatile Pwm *pwm, bool en, u32 scale, bool sticky, bool zerocmp,
	bool deglitch, bool oneshot, u32 center, u32 gang)
{
	pwm->cfg = (scale & PWM_CFG_SCALE) |
		(sticky ? PWM_CFG_STICKY : 0) |
		(zerocmp ? PWM_CFG_ZEROCMP : 0) |
		(deglitch ? PWM_CFG_DEGLITCH : 0) |
		(en ? PWM_CFG_ENALWAYS : 0) |
		(oneshot ? PWM_CFG_ENONESHOT : 0) |
		((center << CTZ(PWM_CFG_CMPnCENTER)) & PWM_CFG_CMPnCENTER) |
		((gang << CTZ(PWM_CFG_CMPnGANG)) & PWM_CFG_CMPnGANG);
}

/*
 * PWM COUNT REGISTER (pwmcount)
 */

static inline void
pwm_count(volatile Pwm *pwm, u32 count)
{
	pwm->count = count;
}

static inline u32
pwm_get_count(volatile Pwm *pwm)
{
	return pwm->count;
}

/*
 * SCALED PWM COUNT REGISTER (pwms)
 */

static inline void
pwm_s(volatile Pwm *pwm, u32 s)
{
	pwm->s = s;
}

static inline u32
pwm_get_s(volatile Pwm *pwm)
{
	return pwm->s;
}

/*
 * PWM COMPARE REGISTERS (pwmcmp0-pwmcmp3)
 */

static inline void
pwm_cmp(volatile Pwm *pwm, PwmCmp cmp, u32 val)
{
	pwm->cmp[cmp] = val;
}

static inline u32
pwm_get_cmp(volatile Pwm *pwm, PwmCmp cmp)
{
	return pwm->cmp[cmp];
}

/*
 * HELPER
 */

static inline u32
pwm_device(volatile Pwm *pwm)
{
	if (pwm == pwm1) return 1;
	else if (pwm == pwm2) return 2;
	else return 0;
}

static inline u32
pwm_msk_iof(volatile Pwm *pwm, bool pwm0, bool pwm1, bool pwm2, bool pwm3)
{
	switch(pwm_device(pwm)) {
	case 0:
		return (pwm0 ? GPIO_PWM0_PWM0 : 0) |
			(pwm1 ? GPIO_PWM0_PWM1 : 0) |
			(pwm2 ? GPIO_PWM0_PWM2 : 0) |
			(pwm3 ? GPIO_PWM0_PWM3 : 0);
	case 1:
		return (pwm0 ? GPIO_PWM1_PWM0 : 0) |
			(pwm1 ? GPIO_PWM1_PWM1 : 0) |
			(pwm2 ? GPIO_PWM1_PWM2 : 0) |
			(pwm3 ? GPIO_PWM1_PWM3 : 0);
	case 2:
		return (pwm0 ? GPIO_PWM2_PWM0 : 0) |
			(pwm1 ? GPIO_PWM2_PWM1 : 0) |
			(pwm2 ? GPIO_PWM2_PWM2 : 0) |
			(pwm3 ? GPIO_PWM2_PWM3 : 0);
	default:
		return 0;
	}
}

#endif /* LIBFE310_PWM_H */
