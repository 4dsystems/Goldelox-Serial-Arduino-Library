#if (ARDUINO >= 100)
	#include "Arduino.h" // for Arduino 1.0
#else
	#include "WProgram.h" // for Arduino 23
#endif

// Warning, ensure correct number of digits are specified, especially if -ve numbers are required as minus sign
// will overlay most significant digit if there are not enough digits.
void LedDigitsDisplay(Goldelox_Serial_4DLib Display, int16_t newval, word indexH, word indexL, word left, word top, word Digits, word MinDigits, word WidthDigit, word LeadingBlanks) ;
void LedDigitsDisplayD(Goldelox_Serial_4DLib Display, int16_t newval, word indexH, word indexL, word left, word top, word Digits, word MinDigits, word WidthDigit, word LeadingBlanks) ;
void LedDigitsDisplayR(Goldelox_Serial_4DLib Display, int16_t newval, word indexH, word indexL, word left, word top, word Digits, word MinDigits, word WidthDigit, word LeadingBlanks) ;
void LedDigitsDisplayL(Goldelox_Serial_4DLib Display, int16_t newval, word indexH, word indexL, word left, word top, word Digits, word MinDigits, word WidthDigit, word LeadingBlanks) ;
