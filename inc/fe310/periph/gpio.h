/* See LICENSE file for copyright and license details. */

#ifndef LIBFE310_PERIPH_GPIO_H
#define LIBFE310_PERIPH_GPIO_H

#include <fe310/core/atomic.h>
#include <fe310/periph/hw/gpio.h>
#include <fe310/types.h>

typedef enum {
	GPIO_DS_LO = 0,
	GPIO_DS_HI = 1,
} GpioDs;

typedef enum {
	GPIO_INT_RISE,
	GPIO_INT_FALL,
	GPIO_INT_HIGH,
	GPIO_INT_LOW,
} GpioInt;

typedef enum {
	GPIO_DISABLE,
	GPIO_INPUT,
	GPIO_INPUT_PULLUP,
	GPIO_IOF0,
	GPIO_IOF1,
	GPIO_OUTPUT,
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
} Gpio;

extern volatile Gpio *const gpio;

static inline void __attribute__((always_inline))
gpio_cfg(GpioMode mode, u32 msk)
{
	switch (mode) {
	case GPIO_DISABLE:
		amoand_w(&gpio->input_en, ~msk);
		amoand_w(&gpio->output_en, ~msk);
		amoand_w(&gpio->pue, ~msk);
		amoand_w(&gpio->iof_sel, ~msk);
		amoand_w(&gpio->iof_en, ~msk);
		break;
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
	case GPIO_OUTPUT:
		amoand_w(&gpio->iof_en, ~msk);
		amoand_w(&gpio->input_en, ~msk);
		amoand_w(&gpio->pue, ~msk);
		amoor_w(&gpio->output_en, msk);
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

static inline u32 __attribute__((always_inline))
gpio_get_ip(GpioInt interrupt)
{
	switch (interrupt) {
	case GPIO_INT_RISE:
		return gpio->rise_ip;
	case GPIO_INT_FALL:
		return gpio->fall_ip;
	case GPIO_INT_HIGH:
		return gpio->high_ip;
	case GPIO_INT_LOW:
		return gpio->low_ip;
	default:
		return 0;
	}
}

static inline void __attribute__((always_inline))
gpio_ip(GpioInt interrupt, u32 msk)
{
	switch (interrupt) {
	case GPIO_INT_RISE:
		gpio->rise_ip = msk;
		break;
	case GPIO_INT_FALL:
		gpio->fall_ip = msk;
		break;
	case GPIO_INT_HIGH:
		gpio->high_ip = msk;
		break;
	case GPIO_INT_LOW:
		gpio->low_ip = msk;
		break;
	default:
		return;
	}
}

static inline void __attribute__((always_inline))
gpio_ie(GpioInt interrupt, bool en, u32 msk)
{
	if (en) gpio_ip(interrupt, msk);
	switch (interrupt) {
	case GPIO_INT_RISE:
		if (en) amoor_w(&gpio->rise_ie, msk);
		else amoand_w(&gpio->rise_ie, ~msk);
		break;
	case GPIO_INT_FALL:
		if (en) amoor_w(&gpio->fall_ie, msk);
		else amoand_w(&gpio->fall_ie, ~msk);
		break;
	case GPIO_INT_HIGH:
		if (en) amoor_w(&gpio->high_ie, msk);
		else amoand_w(&gpio->high_ie, ~msk);
		break;
	case GPIO_INT_LOW:
		if (en) amoor_w(&gpio->low_ie, msk);
		else amoand_w(&gpio->low_ie, ~msk);
		break;
	default:
		return;
	}
}

#endif /* LIBFE310_PERIPH_GPIO_H */
