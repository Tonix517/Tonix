#ifndef VESA_H
#define VESA_H

#include "../../include/types.h"

#define VESA_VIDEO_MEM_ADDR_PTR 0x7F00

#define VESA_X_MAX 800
#define VESA_Y_MAX 600

//  only the lower 5b for red is available
//  only the lower 6b for green is available
//  only the lower 5b for blud is available
//
//  It's a linear func, so don't use it in a loop if necessary
//
U16 rgb(U8 red, U8 green, U8 blue);

void putpixel(U16 x, U16 y, U16 color);

void draw_square(U16 x0, U16 y0, U16 nWidth, U16 nHeight, U16 color);
void fill_square(U16 x0, U16 y0, U16 nWidth, U16 nHeight, U16 color);

void draw_horizon_line(U16 x, U16 y, U16 nWidth, U16 color);
void draw_vertical_line(U16 x, U16 y, U16 nHeight, U16 color);

void clear_screen(U16 color);

void display_pic(U16 x0, U16 y0, U16 nWidth, U16 nHeight, U16* pData);

#endif
