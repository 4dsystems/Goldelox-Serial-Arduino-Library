#if (ARDUINO >= 100)
	#include "Arduino.h" // for Arduino 1.0
#else
	#include "WProgram.h" // for Arduino 23
#endif

#include "Goldelox_Serial_4DLib.h"
#include "Goldelox_Const4D.h"

// Warning, ensure correct number of digits are specified, especially if -ve numbers are required as minus sign
// will overlay most significant digit if there are not enough digits.
void LedDigitsDisplay(Goldelox_Serial_4DLib Display, int16_t newval, word indexH, word indexL, word left, word top, word Digits, word MinDigits, word WidthDigit, word LeadingBlanks)
{
  int16_t m, nv, i, lstb ;

  left = left + WidthDigit * (Digits-1) ;
  nv = newval ;
  lstb = 1 ;
  for (i = Digits; i > 0; i--)
  {
    m = nv % 10 ;
    if ( LeadingBlanks && (i <= Digits - MinDigits) )
    {
      if (nv == 0)
      {
        m = 10 ;
        if (lstb == 1) lstb = i ;
      }
    }
    Display.media_SetAdd(indexH, indexL) ;
    Display.media_VideoFrame(left, top, abs(m)) ;
    nv /= 10 ;
    left -= WidthDigit ;
  }
  if (newval < 0)
  {
    left += lstb * WidthDigit ;
    Display.media_SetAdd(indexH, indexL) ;
    Display.media_VideoFrame(left, top, 11) ;
  }

}

void LedDigitsDisplayD(Goldelox_Serial_4DLib Display, int16_t newval, word indexH, word indexL, word left, word top, word Digits, word MinDigits, word WidthDigit, word LeadingBlanks)
{
  int16_t i, m, lstb, nv ;

  left = left - WidthDigit * (Digits-1) ;
  nv = newval ;
  lstb = 1 ;
  for (i = Digits; i > 0; i--)
  {
    m = nv % 10 ;
    if ( LeadingBlanks && (i <= Digits - MinDigits) )
    {
      if (nv == 0)
      {
        m = 10 ;
        if (lstb == 1) lstb = i ;
      }
    }

    Display.media_SetAdd(indexH, indexL) ;
    Display.media_VideoFrame(left, top, abs(m)) ;
    nv /= 10 ;
    left += WidthDigit ;
  }
  if (newval < 0)
  {
    left -= lstb * WidthDigit ;
    Display.media_SetAdd(indexH, indexL) ;
    Display.media_VideoFrame(left, top, 11) ;
  }

}

void LedDigitsDisplayR(Goldelox_Serial_4DLib Display, int16_t newval, word indexH, word indexL, word left, word top, word Digits, word MinDigits, word WidthDigit, word LeadingBlanks)
{
  int16_t i, m, lstb, nv ;
  left = left - WidthDigit * (Digits-1) ;
  nv = newval ;
  lstb = 1 ;
  for (i = Digits; i > 0; i--)
  {
    m = nv % 10 ;
    if ( LeadingBlanks && (i <= Digits - MinDigits) )
    {
      if (nv == 0)
      {
        m = 10 ;
        if (lstb == 1) lstb = i ;
      }
    }

    Display.media_SetAdd(indexH, indexL) ;
    Display.media_VideoFrame(top, left, abs(m)) ;
    nv /= 10 ;
    left += WidthDigit ;
  }
  if (newval < 0)
  {
    left -= lstb * WidthDigit ;
    Display.media_SetAdd(indexH, indexL) ;
    Display.media_VideoFrame(top, left, 11) ;
  }

}

void LedDigitsDisplayL(Goldelox_Serial_4DLib Display, int16_t newval, word indexH, word indexL, word left, word top, word Digits, word MinDigits, word WidthDigit, word LeadingBlanks)
{
  int16_t i, m, lstb, nv ;

  top = top + WidthDigit * (Digits-1) ;
  nv = newval ;
  lstb = 1 ;
  for (i = Digits; i > 0; i--)
  {
    m = nv % 10 ;
    if ( LeadingBlanks && (i <= Digits - MinDigits) )
    {
      if (nv == 0)
      {
        m = 10 ;
        if (lstb == 1) lstb = i ;
      }
    }

    Display.media_SetAdd(indexH, indexL) ;
    Display.media_VideoFrame(left, top, abs(m)) ;
    nv /= 10 ;
    top -= WidthDigit ;
    }
  if (newval < 0)
  {
    top += lstb * WidthDigit ;
    Display.media_SetAdd(indexH, indexL) ;
    Display.media_VideoFrame(left, top, 11) ;
  }

}

