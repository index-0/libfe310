/* See LICENSE file for copyright and license details. */

#ifndef LIBFE310_PLIC_H
#define LIBFE310_PLIC_H

#include <fe310/types.h>
#include <fe310/vendor/plic.h>

typedef enum {
	PLIC_IRQ_NONE = 0,
	PLIC_IRQ_AON_WDOG,
	PLIC_IRQ_AON_RTC,
	PLIC_IRQ_UART0,
	PLIC_IRQ_UART1,
	PLIC_IRQ_SPI0,
	PLIC_IRQ_SPI1,
	PLIC_IRQ_SPI2,
	PLIC_IRQ_GPIO0,
	PLIC_IRQ_GPIO1,
	PLIC_IRQ_GPIO2,
	PLIC_IRQ_GPIO3,
	PLIC_IRQ_GPIO4,
	PLIC_IRQ_GPIO5,
	PLIC_IRQ_GPIO6,
	PLIC_IRQ_GPIO7,
	PLIC_IRQ_GPIO8,
	PLIC_IRQ_GPIO9,
	PLIC_IRQ_GPIO10,
	PLIC_IRQ_GPIO11,
	PLIC_IRQ_GPIO12,
	PLIC_IRQ_GPIO13,
	PLIC_IRQ_GPIO14,
	PLIC_IRQ_GPIO15,
	PLIC_IRQ_GPIO16,
	PLIC_IRQ_GPIO17,
	PLIC_IRQ_GPIO18,
	PLIC_IRQ_GPIO19,
	PLIC_IRQ_GPIO20,
	PLIC_IRQ_GPIO21,
	PLIC_IRQ_GPIO22,
	PLIC_IRQ_GPIO23,
	PLIC_IRQ_GPIO24,
	PLIC_IRQ_GPIO25,
	PLIC_IRQ_GPIO26,
	PLIC_IRQ_GPIO27,
	PLIC_IRQ_GPIO28,
	PLIC_IRQ_GPIO29,
	PLIC_IRQ_GPIO30,
	PLIC_IRQ_GPIO31,
	PLIC_IRQ_PWM0_0,
	PLIC_IRQ_PWM0_1,
	PLIC_IRQ_PWM0_2,
	PLIC_IRQ_PWM0_3,
	PLIC_IRQ_PWM1_0,
	PLIC_IRQ_PWM1_1,
	PLIC_IRQ_PWM1_2,
	PLIC_IRQ_PWM1_3,
	PLIC_IRQ_PWM2_0,
	PLIC_IRQ_PWM2_1,
	PLIC_IRQ_PWM2_2,
	PLIC_IRQ_PWM2_3,
	PLIC_IRQ_I2C,
} PlicIrq;

typedef enum {
	PLIC_PRIORITY_0,
	PLIC_PRIORITY_1,
	PLIC_PRIORITY_2,
	PLIC_PRIORITY_3,
	PLIC_PRIORITY_4,
	PLIC_PRIORITY_5,
	PLIC_PRIORITY_6,
	PLIC_PRIORITY_7,
} PlicPriority;

void plic_dispatch(void);
void plic_hook(PlicIrq irq, void (*fn)(void));
void plic_unhook(PlicIrq irq);

/*
 * PLIC INTERRUPT PRIORITY REGISTER (priority)
 */

static inline void
plic_priority(PlicIrq irq, PlicPriority priority)
{
	if (irq == PLIC_IRQ_NONE) return;
	(*(volatile u32 *)(PLIC_BASE_PRIORITY + 4 * irq)) = priority;
}

/*
 * PLIC INTERRUPT PENDING REGISTERS (pending1 and pending 2)
 */

static inline bool
plic_is_ip(PlicIrq irq)
{
	return ((*(volatile u32 *)(PLIC_BASE_IP + 4 * (irq / 32))) &
		(1 << (irq % 32))) != 0;
}

static inline u64
plic_get_ip(void)
{
	volatile u32 *ip = (volatile u32 *)PLIC_BASE_IP;
	return ((u64)ip[1] << 32) | ip[0];
}

/*
 * PLIC INTERRUPT ENABLE REGISTERS (enable1 and enable2)
 */

static inline void
plic_set_ie(bool en, PlicIrq irq)
{
	if (en)
		(*(volatile u32 *)(PLIC_BASE_IE + 4 * (irq / 32))) |=
			1 << (irq % 32);
	else
		(*(volatile u32 *)(PLIC_BASE_IE + 4 * (irq / 32))) &=
			~(1 << (irq % 32));
}

static inline bool
plic_is_ie(PlicIrq irq)
{
	return ((*(volatile u32 *)(PLIC_BASE_IE + 4 * (irq / 32))) &
		(1 << (irq % 32))) != 0;
}

static inline u64
plic_get_ie(void)
{
	volatile u32 *ie = (volatile u32 *)PLIC_BASE_IE;
	return ((u64)ie[1] << 32) | ie[0];
}

static inline void
plic_ie(u64 msk)
{
	volatile u32 *ie = (volatile u32 *)PLIC_BASE_IE;
	ie[0] = msk; ie[1] = msk >> 32;
}

/*
 * PLIC INTERRUPT PRIORITY THRESHOLD REGISTER (threshold)
 */

static inline void
plic_threshold(PlicPriority priority)
{
	(*(volatile u32 *)(PLIC_BASE_THRESHOLD)) = priority;
}

static inline PlicPriority
plic_get_threshold(void)
{
	return (*(volatile u32 *)(PLIC_BASE_THRESHOLD));
}

/*
 * PLIC CLAIM/COMPLETE REGISTER (claim/complete)
 */

static inline PlicIrq
plic_claim(void)
{
	return (*(volatile u32 *)(PLIC_BASE_CLAIM));
}

static inline void
plic_complete(PlicIrq irq)
{
	if (irq == PLIC_IRQ_NONE) return;
	(*(volatile u32 *)(PLIC_BASE_CLAIM)) = irq;
}

#endif /* LIBFE310_PLIC_H */
