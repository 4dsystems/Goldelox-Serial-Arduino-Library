#if (ARDUINO >= 100)
  #include "Arduino.h" // for Arduino 1.0
#else
  #include "WProgram.h" // for Arduino 23
#endif

#include "Goldelox_Serial_4DLib.h"
#include "Goldelox_Const4D.h"

void PrintDisk(Goldelox_Serial_4DLib Display, long offset, word msglen, word msgid)
{
    long addr ;
    uint8_t ch ;
    addr = offset ;
    addr += (long) msglen * (long) msgid ;
    Display.media_SetAdd(addr >> 16, addr & 0xffff);
    do
    {
      ch = Display.media_ReadByte() ;
      Display.putCH(ch) ;
    } while (ch != 0) ;
}

