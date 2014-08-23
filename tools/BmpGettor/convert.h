#ifndef _CONVERT_H_
#define _CONVERT_H_

typedef unsigned char  U8;
typedef unsigned short U16;
typedef unsigned int   U32;


/**** Get Color value in 5:6:5 format ****/
U8 f8to8(U8 u8,int color)
// u32 is the original pal, color is destination color,0=r,1=g,2=b
{    
   //calculate new value for 565
   int bits=5 + (color==1?1:0);  // r5 g6 b5
   U8 newValue=(u8*1.0/0xff)*((1<<bits)-1);   
   
   return newValue;
}

// make a new 565 palette with r,g,b
U16 to565pal(U8 r,U8 g,U8 b)
{
    U16 pal565=0;
    pal565 |= r<<(16-5);   // 5 bits
    pal565 |= g<<(11-6);   // 6 bits
    pal565 |= b;           // 5 bits
    printf("0x%x,0x%x,0x%x = ",r,g,b);
    return pal565;
}

#endif