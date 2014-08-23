#ifndef LIB_H
#define LIB_H

#include "../include/types.h"

//	Return the string length
int hex2a(U32 nValue, char* zDestBuf);
void memset(char* pBuf, char nValue, U32 nSize);

//  From ASM
void print(char *, int pos, int color);
void c_print(char *pData, int x, int y, int color);

#endif
