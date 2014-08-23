#include "keyboard.h"
#include "../../kernel/lib.h"
#include "../../kernel/kernel.h"
#include "../../kernel/interrupt.h"

static int nKeyStrokeTimes = 0;

void init_keyboard()
{
	set_irq_handler(KEYBOARD_IRQ, irq_handler_keyboard);
	enable_irq(KEYBOARD_IRQ);

	nKeyboardBufSize = 16;

	sKbBuf.nCurrDataSize = 0;
	memset(sKbBuf.zCharBuf, 0, nKeyboardBufSize);
}

void irq_handler_keyboard(int nIrq)
{	
	char ckey = in_port(KB_DATA);
	
	if(sKbBuf.nCurrDataSize < nKeyboardBufSize)
	{
		sKbBuf.zCharBuf[sKbBuf.nCurrDataSize] = ckey;		
	}
	else
	{
		//	If the buffer is full, reset the buffer.
		sKbBuf.nCurrDataSize = 0;
		sKbBuf.zCharBuf[sKbBuf.nCurrDataSize] = ckey;
	}

	sKbBuf.nCurrDataSize++;
}

void waitForStroke()
{
	//	Blocking if no data 
	while(sKbBuf.nCurrDataSize == 0){};
	
	sKbBuf.nCurrDataSize = 0;
}

