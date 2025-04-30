/* See LICENSE file for copyright and license details. */

#ifndef FE310_GPIO_H
#define FE310_GPIO_H

#include "atomic.h"
#include "types.h"
#include "vendor/gpio.h"

typedef enum {
	GPIO_DS_LO = 0,
	GPIO_DS_HI = 1,
} GpioDs;

typedef enum {
	GPIO_INPUT,
	GPIO_INPUT_PULLUP,
	GPIO_OUTPUT,
	GPIO_IOF0,
	GPIO_IOF1,
} GpioMode;

typedef struct Gpio {
	volatile u32 input_val;
	volatile u32 input_en;
	volatile u32 output_en;
	volatile u32 output_val;
	volatile u32 pue;
	volatile u32 ds;
	volatile u32 rise_ie;
	volatile u32 rise_ip;
	volatile u32 fall_ie;
	volatile u32 fall_ip;
	volatile u32 high_ie;
	volatile u32 high_ip;
	volatile u32 low_ie;
	volatile u32 low_ip;
	volatile u32 iof_en;
	volatile u32 iof_sel;
	volatile u32 out_xor;
	volatile u32 passthru_high_ie;
	volatile u32 passthru_low_ie;
} Gpio;

extern volatile Gpio *const gpio;

static inline __attribute__((always_inline)) void
gpio_init(GpioMode mode, u32 msk)
{
	switch (mode) {
	case GPIO_INPUT:
		amoand_w(&gpio->iof_en, ~msk);
		amoand_w(&gpio->output_en, ~msk);
		amoand_w(&gpio->pue, ~msk);
		amoor_w(&gpio->input_en, msk);
		break;
	case GPIO_INPUT_PULLUP:
		amoand_w(&gpio->iof_en, ~msk);
		amoand_w(&gpio->output_en, ~msk);
		amoor_w(&gpio->input_en, msk);
		amoor_w(&gpio->pue, msk);
		break;
	case GPIO_OUTPUT:
		amoand_w(&gpio->iof_en, ~msk);
		amoand_w(&gpio->input_en, ~msk);
		amoand_w(&gpio->pue, ~msk);
		amoor_w(&gpio->output_en, msk);
		break;
	case GPIO_IOF0:
		amoand_w(&gpio->input_en, ~msk);
		amoand_w(&gpio->output_en, ~msk);
		amoand_w(&gpio->pue, ~msk);
		amoand_w(&gpio->iof_sel, ~msk);
		amoor_w(&gpio->iof_en, msk);
		break;
	case GPIO_IOF1:
		amoand_w(&gpio->input_en, ~msk);
		amoand_w(&gpio->output_en, ~msk);
		amoand_w(&gpio->pue, ~msk);
		amoor_w(&gpio->iof_sel, msk);
		amoor_w(&gpio->iof_en, msk);
		break;
	default:
		return;
	}
}

static inline u32
gpio_get(u32 msk)
{
	return gpio->input_val & msk;
}

static inline void
gpio_set(u32 msk)
{
	amoor_w(&gpio->output_val, msk);
}

static inline void
gpio_clr(u32 msk)
{
	amoand_w(&gpio->output_val, ~msk);
}

static inline void
gpio_tgl(u32 msk)
{
	amoxor_w(&gpio->output_val, msk);
}

static inline void
gpio_xor(bool en, u32 msk)
{
	if (en)
		amoor_w(&gpio->out_xor, msk);
	else
		amoand_w(&gpio->out_xor, ~msk);
}

static inline void
gpio_ds(GpioDs ds, u32 msk)
{
	if (ds)
		amoor_w(&gpio->ds, msk);
	else
		amoand_w(&gpio->ds, ~msk);
}

#endif /* FE310_GPIO_H */
