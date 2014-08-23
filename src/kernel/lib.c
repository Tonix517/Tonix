#include "lib.h"

void c_print(char *pData, int x, int y, int color)
{
	print(pData, (y * 80 + x)*2, color);
}

int hex2a(U32 nHexValue, char* pBuf)
{

	//  Add "0x"
     int nCurrPos = 0;
     pBuf[nCurrPos++] = '0';
     pBuf[nCurrPos++] = 'x';
     
	 //	Is number printing started? as 0x00100 can be 0x100
	 int bStarted = 0;

     //  Transform
     int nShift = 0;     
     for(nShift = 28; nShift >=0; nShift-=4)
     {
          char nCurrByte = (nHexValue >> nShift) & 0xF;

          if(nCurrByte != 0)
          {
               if( (nCurrByte > 0) && (nCurrByte <= 9) ) 
               {
                   pBuf[nCurrPos++] = '0' + (nCurrByte - 0);
               }
               else if( (nCurrByte >= 10) && (nCurrByte <= 15))
               {
                   pBuf[nCurrPos++] = 'A' + (nCurrByte - 10);
               }

			   bStarted = 1;
          }
		  else
		  {
			if(nShift < 28 && bStarted)
			{
				pBuf[nCurrPos++] = '0';
			}
		  }
     }

	 return nCurrPos;
}

//	TODO : ASM will be much faster
void memset(char* pBuf, char nValue, U32 nSize)
{	
	for(int i = 0; i<nSize; i++)
	{
		pBuf[i] = nValue;
	}
}
