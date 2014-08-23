#ifndef CLOCK_H
#define CLOCK_H

#include "../../include/types.h"


#define	CLOCK_IRQ	0

void init_clock();
void irq_handler_clock(int nIrq);

#endif
