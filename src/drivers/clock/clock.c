#include "clock.h"
#include "../../kernel/lib.h"
#include "../../kernel/kernel.h"
#include "../../kernel/interrupt.h"

void init_clock()
{
	set_irq_handler(CLOCK_IRQ, irq_handler_clock);
	enable_irq(CLOCK_IRQ);
}

void irq_handler_clock(int nIrq)
{	
	char buf[2] = {'*','\0'};

	static int x = 0;
    c_print(buf, x++, 19, LIGHT_BLUE);
}
