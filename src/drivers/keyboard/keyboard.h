#ifndef KEY_BOARD_H
#define KEY_BOARD_H

#include "../../include/types.h"

#define KB_DATA			0x60
#define KB_CTL_STATUS	0x64

#define	KEYBOARD_IRQ	1

void init_keyboard();
void irq_handler_keyboard(int nIrq);
void waitForStroke();

U16 nKeyboardBufSize;

struct keyboard_buf
{
	U16 nCurrDataSize;
	char zCharBuf[16];
};

struct keyboard_buf sKbBuf;

#endif
