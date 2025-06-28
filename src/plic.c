/* See LICENSE file for copyright and license details. */

#include <fe310/plic.h>

static void (*isr_table[PLIC_CNT_IRQ + 1])(void);

void
plic_dispatch(void)
{
	PlicIrq irq = plic_claim();

	if (irq == PLIC_IRQ_NONE) return;
	if (isr_table[irq]) isr_table[irq]();
	plic_complete(irq);
}

void
plic_hook(PlicIrq irq, void (*fn)(void))
{
	if (irq == PLIC_IRQ_NONE || irq > PLIC_CNT_IRQ) return;
	isr_table[irq] = fn;
}

void
plic_unhook(PlicIrq irq)
{
	if (irq == PLIC_IRQ_NONE || irq > PLIC_CNT_IRQ) return;
	isr_table[irq] = (void (*)(void))0;
}
