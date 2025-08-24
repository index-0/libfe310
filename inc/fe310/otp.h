/* See LICENSE file for copyright and license details. */

#ifndef LIBFE310_OTP_H
#define LIBFE310_OTP_H

#include <fe310/types.h>
#include <fe310/vendor/otp.h>

typedef struct Otp {
	volatile u32 lock;
	volatile u32 ck;
	volatile u32 oe;
	volatile u32 sel;
	volatile u32 we;
	volatile u32 mr;
	volatile u32 mrr;
	volatile u32 mpp;
	volatile u32 vrren;
	volatile u32 vppen;
	volatile u32 a;
	volatile u32 d;
	volatile u32 q;
	volatile u32 rsctrl;
} Otp;

extern volatile Otp *const otp;

/*
 * OTP READ SEQUENCER CONTROL (rsctrl)
 */

static inline void
otp_set_rsctrl_scale(u32 scale)
{
	otp->rsctrl |= (scale & OTP_RSCTRL_SCALE);
}

static inline u32
otp_get_rsctrl_scale(void)
{
	return otp->rsctrl & OTP_RSCTRL_SCALE;
}

static inline void
otp_set_rsctrl_tas(bool tas)
{
	if (tas)
		otp->rsctrl |= OTP_RSCTRL_TAS;
	else
		otp->rsctrl &= ~OTP_RSCTRL_TAS;
}

static inline bool
otp_is_rsctrl_tas_en(void)
{
	return (otp->rsctrl & OTP_RSCTRL_TAS) != 0;
}

static inline void
otp_set_rsctrl_trp(bool trp)
{
	if (trp)
		otp->rsctrl |= OTP_RSCTRL_TRP;
	else
		otp->rsctrl &= ~OTP_RSCTRL_TRP;
}

static inline bool
otp_is_rsctrl_trp_en(void)
{
	return (otp->rsctrl & OTP_RSCTRL_TRP) != 0;
}

static inline void
otp_set_rsctrl_tacc(bool tacc)
{
	if (tacc)
		otp->rsctrl |= OTP_RSCTRL_TACC;
	else
		otp->rsctrl &= ~OTP_RSCTRL_TACC;
}

static inline bool
otp_is_rsctrl_tacc_en(void)
{
	return (otp->rsctrl & OTP_RSCTRL_TACC) != 0;
}

static inline void
otp_rsctrl(u32 scale, bool tas, bool trp, bool tacc)
{
	otp->rsctrl = (scale & OTP_RSCTRL_SCALE) |
		(tas ? OTP_RSCTRL_TAS : 0) |
		(trp ? OTP_RSCTRL_TRP : 0) |
		(tacc ? OTP_RSCTRL_TACC : 0);
}

#endif /* LIBFE310_OTP_H */
