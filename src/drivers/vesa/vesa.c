#include "vesa.h"
#include "../../kernel/lib.h"
#include "../../kernel/kernel.h"
#include "../../kernel/interrupt.h"

U16 rgb(U8 red, U8 green, U8 blue)
{
    union
    {
        U16 color ;

        struct {
          U8 b : 5 ;
          U8 g : 6 ;
          U8 r : 5 ;
        }_data;
    } u;

    u._data.r = red   % 0x20 ;
    u._data.g = green % 0x40 ;
    u._data.b = blue  % 0x20 ;

    return u.color;
}

void putpixel(U16 x, U16 y, U16 color)
{
    if( x > (VESA_X_MAX) || y > (VESA_Y_MAX) )
    {   return; }

    *((U16*)(*(U32*)(VESA_VIDEO_MEM_ADDR_PTR)) + y * VESA_X_MAX + x) = color;
}

/*
void draw_line(U16 x0, U16 y0, U16 x1, U16 y1, U16 color)
{
    
    //  Check Param Boundary
    if( x0 > (VESA_X_MAX - 1) || y0 > (VESA_Y_MAX - 1) )
    {   return; }

    if( x1 > (VESA_X_MAX - 1) || y1 > (VESA_Y_MAX - 1) )
    {   return; }

     //  Perpendicular Line
    if(x0 == x1)
    {
        U16 nTopY    =  (y0 < y1) ? y0 : y1;
        U16 nBottomY =  (y0 > y1) ? y0 : y1;

        for(U16 i = nTopY; i<= nBottomY; i++)
        {
            putpixel(x0, i, color);            
        }
    }
    else
    {
        float slope = (y1 - y0) * 1.0 /(x1 - x0);

        //  By x-axis
        U16 nLeftX  = (x0 < x1) ? x0 : x1;
        U16 nRightX = (x0 > x1) ? x0 : x1;
        U16 nTopY    =  (y0 < y1) ? y0 : y1;
        U16 nBottomY =  (y0 > y1) ? y0 : y1;

        for(U16 i = nLeftX; i <= nRightX; i++)
        {
            // TODO : Very weird, *slope is always 0.
            U16 nCurrY = nTopY + (U16) ((i - nLeftX) * slope);
            putpixel(i, nCurrY, color);            
        }
    }
}
*/

void fill_square(U16 x0, U16 y0, U16 nWidth, U16 nHeight, U16 color)
{
   
    for(U16 i = x0; i <= x0 + nWidth; i++)
    for(U16 j = y0; j <= y0 + nHeight; j++)
    {
        putpixel(i, j, color);        
    }
}

void draw_square(U16 x0, U16 y0, U16 nWidth, U16 nHeight, U16 color)
{
    //  Draw Horizon
    for(U16 i = x0; i <= x0 + nWidth; i++)
    {
        putpixel(i, y0, color);
        putpixel(i, y0 + nHeight, color);
    }

    //  Draw Vertical
    for(U16 i = y0; i <= y0 + nHeight; i++)
    {
        putpixel(x0, i, color);
        putpixel(x0 + nWidth, i, color);
    }
}

void clear_screen(U16 color)
{
    fill_square(0, 0, VESA_X_MAX - 1, VESA_Y_MAX - 1, color);
}

void draw_horizon_line(U16 x, U16 y, U16 nWidth, U16 color)
{
    for(U16 i = 0; i<= nWidth; i++)
    {
        putpixel(x + i, y, color);
    }
}

void draw_vertical_line(U16 x, U16 y, U16 nHeight, U16 color)
{
    for(U16 i = 0; i<= nHeight; i++)
    {
        putpixel(x, y + i, color);
    }
}

void display_pic(U16 x0, U16 y0, U16 nWidth, U16 nHeight, U16* pData)
{     
    /*  
    for(U16 i = 0; i< (nWidth * nHeight); i++)
    {
            putpixel(x0 + i % nWidth, y0 + i / nWidth, pData[i]);
    }    
    */
    for(U16 iH = 0; iH < nHeight; iH ++ )
    for(U16 iW = 0; iW < nWidth; iW ++ )
    {
     putpixel(x0 + iW, y0 + iH, pData[iH * nWidth + iW]);
    }
}
