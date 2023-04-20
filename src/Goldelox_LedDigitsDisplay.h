#if (ARDUINO >= 100)
	#include "Arduino.h" // for Arduino 1.0
#else
	#include "WProgram.h" // for Arduino 23
#endif

// WARNING, this code will crash if newval exceeds maximum displayable number
void LedDigitsDisplay(Goldelox_Serial_4DLib Display, word newval, word indexH, word indexL, word left, word top, word Digits, word MinDigits, word WidthDigit, word LeadingBlanks) ;
void LedDigitsDisplayD(Goldelox_Serial_4DLib Display, word newval, word indexH, word indexL, word left, word top, word Digits, word MinDigits, word WidthDigit, word LeadingBlanks) ;
void LedDigitsDisplayR(Goldelox_Serial_4DLib Display, word newval, word indexH, word indexL, word left, word top, word Digits, word MinDigits, word WidthDigit, word LeadingBlanks) ;
void LedDigitsDisplayL(Goldelox_Serial_4DLib Display, word newval, word indexH, word indexL, word left, word top, word Digits, word MinDigits, word WidthDigit, word LeadingBlanks) ;
