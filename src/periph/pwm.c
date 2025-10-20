/* See LICENSE file for copyright and license details. */

#include <fe310/periph/gpio.h>
#include <fe310/periph/pwm.h>

volatile Pwm *const pwm0 __attribute__((used)) = (volatile Pwm *)PWM0_BASE;
volatile Pwm *const pwm1 __attribute__((used)) = (volatile Pwm *)PWM1_BASE;
volatile Pwm *const pwm2 __attribute__((used)) = (volatile Pwm *)PWM2_BASE;

void
pwm_iof(volatile Pwm *pwm, bool en, bool pwm0, bool pwm1, bool pwm2, bool pwm3)
{
	gpio_cfg(en ? GPIO_IOF1 : GPIO_DISABLE,
		pwm_msk_iof(pwm, pwm0, pwm1, pwm2, pwm3));
}

u32
pwm_prep_cmp0(volatile Pwm *pwm, u32 hfclk, u32 freq, u32 *scale)
{
	const u32 w = ((1 << (pwm_device(pwm) ? 16 : 8)) - 1);
	u32 cmp0, cdiv, s;

	if (scale == NULL || freq == 0) return 0;

	for (s = 0; s <= PWM_CFG_SCALE; ++s) {
		cdiv = hfclk >> s;
		cmp0 = cdiv / freq;
		if (cmp0 == 0) break;
		if (cmp0 <= w) {
			*scale = s;
			return cmp0;
		}
	}

	*scale = 0;
	return 0;
}

u32
pwm_prep_cmpx(u32 cmp0, u32 duty)
{
	if (cmp0 == 0) return 0;
	if (duty > 100) duty = 100;
	return duty * (cmp0 - 1) / 100;
}
