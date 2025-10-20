/* See LICENSE file for copyright and license details. */

#ifndef LIBFE310_PERIPH_HW_OTP_H
#define LIBFE310_PERIPH_HW_OTP_H

#include <fe310/bits.h>

#define OTP_BASE 0x10010000

#define OTP_RSCTRL_SCALE GENMASK(2, 0)
#define OTP_RSCTRL_TAS BITMASK(3)
#define OTP_RSCTRL_TRP BITMASK(4)
#define OTP_RSCTRL_TACC BITMASK(5)

#endif /* LIBFE310_PERIPH_HW_OTP_H */
