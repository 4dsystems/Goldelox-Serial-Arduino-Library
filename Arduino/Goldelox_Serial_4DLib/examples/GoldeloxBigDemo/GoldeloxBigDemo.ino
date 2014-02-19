/*********************************************************************************************/
/*                                                                                           */
/*  Goldelox 4D Serial Sample                                                                */
/*                                                                                           */
/*  Date:            31 December 2012                                                        */
/*                                                                                           */
/*  Description:     Demonstrates Pretty much every 4D Serial command.                       */
/*                   This has been tested on an Arduino Duemilanove ATmega328 using Arduino  */
/*                   1.0.2                                                                   */
/*                   This program, by default, uses the hardware serial on pins 0 and 1 and  */
/*                   thus the 5 pin connector on the 4D Arduino Adapter, or the 4Display     */
/*                   Shield must be unplugged or jumpers removed before loading your sketch  */
/*                   and plugged back in after the error callback is called (i.e. the LED is */
/*                   flashing), then reset the Arduino using the Reset button or by bridging */
/*                   the reset pins (otherwise you will get a message like                   */
/*                   "avrdude: stk500_getsync(): not in sync: resp=0xe0")                    */
/*                                                                                           */
/*                   The library also supports other hardware serial ports, for the boards   */
/*                   that support them, as well as software serial.                          */
/*                                                                                           */
/*                   Define the serial port to use here, if using software serial set it to  */
/*                   something like SerialS.                                                 */
  #define DisplaySerial Serial
/*                                                                                           */
/*                   To use SoftwareSerial uncomment the following and set the pins you are  */
/*                   using correctly                                                         */
//#include <SoftwareSerial.h>
//SoftwareSerial DisplaySerial(2,3) ; // pin 2 = TX of display, pin3 = RX
/*                                                                                           */
/*                   If you are not using hardware serial on pins 0 and 1 you can use this   */
/*                   hardware port for logging messages. To do this uncomment the following  */
//#define LOG_MESSAGES
/*                                                                                           */
/*                   The 4Display Shield has its joystick connected directly to Arduino      */
/*                   Digital pins 2-6. If you are using the 4D Arduino Adapter, and/or have  */
/*                   done your own 'wiring' you could could potentially have a joysick       */
/*                   connected to IO1 of goldelox. To use that you need to uncomment the     */
/*                   next define. Beware of doubling up on the pins if using SoftwareSerial  */
/*                   If you do not have a joystick then comment out the call to test it, or  */
/*                   this program will get stuck.                                            */
//#define GOLDELOX_JOYSTICK
/*                                                                                           */
/*                   The following file needs to be opened with Graphics Composer(GC) and    */
/*                   'saved' to offset 0 of a uSD card in order to perform Media Tests.      */
/*                   PoGa Intro\GCI_Demo1\Images\GCI_DEMO1                                   */
/*                                                                                           */
/* Error Callback    In order to drastically reduce the amount of error checking you need    */
/*                   to do a callback exists to perform 'standard' error handling when an    */
/*                   occurs. If you want to do your own handling set Callback4D to NULL      */
/*                   otherwise set it to the address of the error routine                    */
/*                                                                                           */
/* Baud rate change  Because the stream class used within the library does not support       */
/*                   .end, or .begin the setbaudWait and SetThisBaudrate functions are       */
/*                   coded within this demo                                                  */
/*                                                                                           */
/*     NB!           There is an issue with SoftwareSerial in Arduino 1.0.2 + 1.0.3 and      */
/*                   possibly above which affects Goldelox Displays, refer here:-            */
/*                   https://github.com/arduino/Arduino/issues/1195 to fix you must edit     */
/*                   SoftwareSerial.cpp and find the setTX function and change the first two */
/*                   statements so it becomes:-                                              */
/*                                                                                           */
/*                   void SoftwareSerial::setTX(uint8_t tx)                                  */
/*                   {                                                                       */  
/*                     pinMode(tx, INPUT_PULLUP);                                            */
/*                     pinMode(tx, OUTPUT);                                                  */ 
/*                                                                                           */
/*********************************************************************************************/

#ifdef LOG_MESSAGES
  #define HWLOGGING Serial
#else
  #define HWLOGGING if (1) {} else Serial
#endif

#include "Goldelox_Serial_4DLib.h"
#include "GoldeloxBigDemo.h" 
#include "Goldelox_const4D.h"

Goldelox_Serial_4DLib Display(&DisplaySerial);

// globals for this program
int fmediatests ;

void SetThisBaudrate(int Newrate)
{
  int br ;
  DisplaySerial.flush() ;
  DisplaySerial.end() ;
  switch(Newrate)
  {
    case BAUD_110    : br = 110 ;
      break ;
    case BAUD_300    : br = 300 ;
      break ;
    case BAUD_600    : br = 600 ;
      break ;
    case BAUD_1200   : br = 1200 ;
      break ;
    case BAUD_2400   : br = 2400 ;
      break ;
    case BAUD_4800   : br = 4800 ;
      break ;
    case BAUD_9600   : br = 9600 ;
      break ;
    case BAUD_14400  : br = 14400 ;
      break ;
    case BAUD_19200  : br = 19200 ;
      break ;
    case BAUD_31250  : br = 31250 ;
      break ;
    case BAUD_38400  : br = 38400 ;
      break ;
    case BAUD_56000  : br = 56000 ;
      break ;
    case BAUD_57600  : br = 57600 ;
      break ;
    case BAUD_115200 : br = 115200 ;
      break ;
    case BAUD_128000 : br = 133928 ; // actual rate is not 128000 ;
      break ;
    case BAUD_256000 : br = 281250 ; // actual rate is not  256000 ;
      break ;
    case BAUD_300000 : br = 312500 ; // actual rate is not  300000 ;
      break ;
    case BAUD_375000 : br = 401785 ; // actual rate is not  375000 ;
      break ;
    case BAUD_500000 : br = 562500 ; // actual rate is not  500000 ;
      break ;
    case BAUD_600000 : br = 703125 ; // actual rate is not  600000 ;
      break ;
  }
  DisplaySerial.begin(br) ;
  delay(50) ; // Display sleeps for 100
  DisplaySerial.flush() ;
}

void setbaudWait(word  Newrate)
{
  DisplaySerial.print((char)(F_setbaudWait >> 8));
  DisplaySerial.print((char)(F_setbaudWait));
  DisplaySerial.print((char)(Newrate >> 8));
  DisplaySerial.print((char)(Newrate));
  SetThisBaudrate(Newrate); // change this systems baud rate to match new display rate, ACK is 100ms away
  Display.GetAck() ;
}

int trymount(void)
{
#define retries 15
  int i ;
  int j ;
  i = Display.media_Init() ;
  j = 0 ;
  if (!i)
  {
    Display.putstr("Pls insert uSD crd\n") ;
    while (   (!i)
          && (j < retries) )
    {
      Display.putstr(".") ;
      i = Display.media_Init() ;
      j++ ;
    }
    Display.putstr("\n") ;
  }
  if (j == retries)
    return FALSE ;
  else
    return TRUE ;
}

void gfx_Part1(void)
{
  int i ;
  Display.gfx_Cls() ;
  Display.txt_BGcolour(LIGHTGOLD) ;           // to ensure text goesn look odd
  Display.txt_FGcolour(RED) ;
  Display.putstr("gfx_A - gfx_L") ;
  HWLOGGING.println(F("gfx_A to gfx_L")) ;
  Display.txt_FGcolour(LIME) ;            // reset
  Display.gfx_ChangeColour(RED, LIME) ;
  Display.gfx_Circle(30,20,10,BLUE) ;
  Display.gfx_CircleFilled(60,20,10,BLUE) ;
  Display.gfx_Rectangle(40,50,80,60,RED) ;  // draw a rectange to show where we are clipping
  Display.gfx_ClipWindow(40,50,80,60) ;
  Display.gfx_Clipping(ON) ;                  // turn clipping on but just use it for text
  Display.gfx_MoveTo(20,51) ;
  Display.putstr("1234567890asdfghjkl") ;     // this is clipped
  Display.gfx_Clipping(OFF) ;
  delay(1000) ;
  HWLOGGING.println(F("Display off")) ;
  Display.gfx_Contrast(0) ;
  delay(1000) ;
  HWLOGGING.println(F("Display on + Brightness")) ;
  for (i = 1; i <= 16; i++)
  {
    Display.gfx_Contrast(i) ;
    delay(100) ;
  }
  //	Display.gfx_FrameDelay(6) ;
  HWLOGGING.print(F("X Res=")) ;
  HWLOGGING.print(Display.peekB(GFX_XMAX)+1) ;
  HWLOGGING.print(F(" Y Res= ")) ;
  HWLOGGING.print(Display.peekB(GFX_YMAX)+1) ;
  HWLOGGING.print(F("\nPixel at 60,20 is ")) ;
  HWLOGGING.print(Display.gfx_GetPixel(60, 20)) ;
  HWLOGGING.println(F("")) ;
  Display.gfx_Line(0,0,100,200,BLUE) ;
  Display.gfx_LinePattern(0x00aa) ;
  Display.gfx_Set(OBJECT_COLOUR, WHITE);
  Display.gfx_LineTo(90,40) ;
  Display.gfx_LinePattern(0) ;            // reset
  Display.gfx_BGcolour(BLACK) ;           // reset
  Display.txt_BGcolour(BLACK) ;           // reset
  Display.gfx_Contrast(8) ;
}

void gfx_Part2(void)
{
  int i ;
  int k ;
  int l ;
  word orbitx ;
  word orbity ;
  word vx[20] ;    // : array[0..19] of word ;
  word vy[20] ; //     : array[0..19] of word ;
  Display.gfx_Cls() ;
  Display.putstr("gfx_M - gfx_O") ;
  HWLOGGING.println(F("gfx_M to gfx_T")) ;
  k = 46 ;
  l = 32 ;
  Display.gfx_MoveTo(k, l);
  Display.gfx_CircleFilled(k,l,5,BLUE) ;
  i = -90;   // 12 o'clock position
  while (i<270)
  {
    Display.gfx_Orbit(i, 25, &orbitx, &orbity);
    k = 3;
    if ((i % 90) == 0 )
      k = 5;
    Display.gfx_Circle(orbitx , orbity, k, BLUE);
    i += 30;   // each 30 degreees
  }
  
  Display.gfx_OutlineColour(YELLOW) ;
  Display.gfx_RectangleFilled(80,10,95,60,LIME) ;
  Display.gfx_OutlineColour(0) ;                    // turn outline off
  
  delay(1000) ;
  Display.gfx_Cls() ;
  Display.putstr("gfx_P - gfx_P") ;
  HWLOGGING.println(F("gfx_P to gfx_P")) ;
  vx[0] = 18;   vy[0] = 55;
  vx[1] = 18;   vy[1] = 40;
  vx[2] = 25;   vy[2] = 40;
  vx[3] = 25;   vy[3] = 55;
  vx[4] = 46;   vy[4] = 63;
  vx[5] = 55;   vy[5] = 39;
  vx[6] = 64;   vy[6] = 63;
  vx[7] = 46;   vy[7] = 29;
  vx[8] = 55;   vy[8] = 35;
  vx[9] = 64;   vy[9] = 29;
  vx[10] = 80; vy[10] = 25;
  vx[11] = 80; vy[11] = 39;
  vx[12] = 70; vy[12] = 49;
  vx[13] = 90; vy[13] = 49;
  vx[14] = 80; vy[14] = 39;
  vx[15] = 71; vy[15] = 29;
  vx[16] = 80; vy[16] = 35;
  vx[17] = 89; vy[17] = 29;
  // house
  Display.gfx_Rectangle(3,25,33,55,RED);             // frame
  Display.gfx_Triangle(3,25,18,4,33,25,YELLOW);      // roof
  Display.gfx_Polyline(4, &vx[0], &vy[0], CYAN);     // door
  Display.gfx_PutPixel(20, 47, LIME) ;               // door knob
  // man
  Display.gfx_Circle(55, 13, 10, BLUE);              // head
  Display.gfx_Line(55, 25, 55, 39, BLUE);            // body
  Display.gfx_Polyline(3, &vx[4], &vy[4], CYAN);     // legs
  Display.gfx_Polyline(3, &vx[7], &vy[7], BLUE);     // arms
  // woman
  Display.gfx_Circle(80, 13, 10, PINK);              // head
  Display.gfx_Polyline(5, &vx[10], &vy[10], BROWN);  // dress
  Display.gfx_Line(74, 63, 76, 49, PINK);            // left arm
  Display.gfx_Line(82, 49, 86, 63, PINK);            // right arm
  Display.gfx_Polyline(3, &vx[15], &vy[15], SALMON); // dress
  delay(1000) ;
  Display.gfx_Cls() ;
  Display.putstr("gfx_P - gfx_T") ;
  HWLOGGING.println(F("gfx_P to gfx_T")) ;
  vx[0] = 45; vy[0] = 20;
  vx[1] = 55; vy[1] = 10;
  vx[2] = 95; vy[2] = 20;
  vx[3] = 60; vy[3] = 25;
  vx[4] = 95; vy[4] = 30;
  vx[5] = 55; vy[5] = 40;
  vx[6] = 45; vy[6] = 30;
  Display.gfx_Polygon(7, vx, vy, RED);
  
  Display.gfx_Rectangle(0,10, 10,60, AQUA) ;
  Display.gfx_RectangleFilled(20,10, 40,60, ORANGE) ;
//	Display.gfx_ScreenMode(LANDSCAPE) ;
//	Display.gfx_ScreenMode(PORTRAIT) ;
  Display.gfx_Transparency(ON) ;
  Display.gfx_TransparentColour(YELLOW) ;  // how do we 'test' this?
  Display.gfx_Triangle(50,60, 70,40, 90,60,YELLOW);
}

void Joystick_Tests(void)
{
#ifndef GOLDELOX_JOYSTICK
  #define DOWNPIN  2
  #define LEFTPIN  3
  #define RIGHTPIN 4
  #define FIREPIN  5
  #define UPPIN    6
  pinMode(DOWNPIN, INPUT_PULLUP);
  pinMode(LEFTPIN, INPUT_PULLUP);
  pinMode(RIGHTPIN, INPUT_PULLUP);
  pinMode(FIREPIN, INPUT_PULLUP);
  pinMode(UPPIN, INPUT_PULLUP);
#endif
  int i ;
  int oldi ;
  Display.gfx_Cls() ;
  HWLOGGING.println(F("Joystick Tests")) ;
  Display.putstr("Joystick Tests\nPress Fire to\nExit") ;
  Display.txt_FGcolour(RED) ;
  i = -1 ;
  while (i != FIRE)
  {
    oldi = i ;
#ifdef GOLDELOX_JOYSTICK
    i = Display.joystick() ;
#else
    if (digitalRead(DOWNPIN) == LOW)
      i = DOWN ;
    else if (digitalRead(LEFTPIN) == LOW)
      i = LEFT ;
    else if (digitalRead(RIGHTPIN) == LOW)
      i = RIGHT ;
    else if (digitalRead(FIREPIN) == LOW)
      i = FIRE ;
    else if (digitalRead(UPPIN) == LOW)
      i = UP ;
    else
      i = RELEASED ;
#endif
    if (i != oldi)
    {
      Display.txt_MoveCursor(5,3) ;
      switch (i)
      {
        case RELEASED : Display.putstr("Released") ;
          break ;
        case UP       : Display.putstr("   Up   ") ;
          break ;
        case LEFT     : Display.putstr("  Left  ") ;
          break ;
        case DOWN     : Display.putstr("  Down  ") ;
          break ;
        case RIGHT    : Display.putstr("  Right ") ;
          break ;
        case FIRE     : Display.putstr("  Fire  ") ;
          break ;
      }
    }
  }
  
  Display.txt_FGcolour(LIME) ;
}

void text_Tests(void)
{
  Display.gfx_Cls() ;
  HWLOGGING.println(F("Text Tests")) ;
  Display.putstr("Text Tests") ;
  
  Display.txt_Attributes(BOLD + INVERSE + ITALIC + UNDERLINED) ;
  Display.txt_Xgap(3) ;
  Display.txt_Ygap(3) ;
  Display.txt_BGcolour(YELLOW) ;
  Display.txt_FGcolour(WHITE) ;
  Display.txt_FontID(SYSTEM) ;
  Display.txt_MoveCursor(2, 0) ;
  Display.putstr("Hello There") ;
  
  Display.txt_MoveCursor(4, 1) ;
  Display.txt_Height(2) ;
  Display.txt_Width(1) ;
  Display.txt_Inverse(OFF) ;
  Display.txt_Italic(OFF) ;
  Display.txt_Opacity(TRANSPARENT) ;
  Display.txt_Set(TEXT_COLOUR, LIME) ;
  Display.txt_Underline(ON) ;
  Display.txt_Bold(OFF) ;
  Display.putstr("Hello There") ;
  Display.txt_Height(1) ;
  Display.txt_Width(1) ;
  Display.putCH('z') ;
  HWLOGGING.print(F("Char height=")) ;
  HWLOGGING.print(Display.charheight('w') ) ;
  HWLOGGING.print(F(" Width= ")) ;
  HWLOGGING.print(Display.charwidth('w') ) ;
  HWLOGGING.println(F("")) ;
  Display.txt_BGcolour(BLACK) ;
  Display.txt_FGcolour(LIME) ;
  Display.txt_FontID(SYSTEM) ;
  Display.txt_MoveCursor(0,0) ;      // reset
}

void Media_Tests(void)
{
  int i ;
  int j ;
  int k ;
  int l ;
  int m , handle ;
  Display.gfx_Cls() ;
  Display.putstr("Media Tests") ;
  HWLOGGING.println(F("Media Tests")) ;
  Display.media_SetAdd(3, 0x600) ;     // using addresses from .dat file
  Display.media_Image(20,20) ;
  delay(1000) ;
  Display.media_SetAdd(0, 0x3800) ;    // ditto
  Display.media_Video(0,0) ;
  Display.media_SetSector(1, 0) ;     // pic a sector not used by the 'above'
  Display.media_WriteByte(0x11) ;
  Display.media_WriteWord(0x2233) ;
  Display.media_Flush() ;            // should write 0xFF over the rest of the sector
  Display.media_SetSector(1, 0) ;
  HWLOGGING.print(Display.media_ReadByte()) ;
  HWLOGGING.print(Display.media_ReadWord()) ;
  HWLOGGING.print(Display.media_ReadWord());
  HWLOGGING.println(F("")) ;
}

void Image_Tests(void)
{
  char wks[512] ;
  char * Source ;
  int i, j, k, l ;
  Display.gfx_Cls() ;
// The following statement would work if Image were in RAM, but it isn't and it can't be on the Arduino it was written on, so we need to do it another way
//  Display.blitComtoDisplay(0, 0, Image[1], Image[3], (char *)&Image[6]) ;

  DisplaySerial.print((char)(F_blitComtoDisplay >> 8)) ;
  DisplaySerial.print((char)(F_blitComtoDisplay)) ;
  DisplaySerial.print((char)(0)) ;                  // x High
  DisplaySerial.print((char)(0)) ;                  // x Low
  DisplaySerial.print((char)(0)) ;                  // y High
  DisplaySerial.print((char)(0)) ;                  // y Low
  DisplaySerial.print((char)(Image[0])) ;           // Width high
  DisplaySerial.print((char)(Image[1])) ;           // Width low
  DisplaySerial.print((char)(Image[2])) ;           // Hight High
  DisplaySerial.print((char)(Image[3])) ;           // Height low  
  
  i = Image[1] * Image[3] * 2 ;                     // calculate image size, this assumes the width and height are only 1 byte
  k = 6 ;  // image starts at offset 6
  while (i != 0)
  {
    j = min(512, i) ;
    memcpy_P(wks, (char *)&Image[k], 512) ;
    Source = wks ;
    for (l = 0; l < j; l++)
    {
      DisplaySerial.write(*Source++) ;
    }
    i -= j ;
    k += j ;
  }
  Display.GetAck() ;
}

void Callback(int ErrCode, unsigned char ErrByte)
{
#ifdef LOG_MESSAGES
  const char *Error4DText[] = {"OK\0", "Timeout\0", "NAK\0", "Length\0", "Invalid\0"} ;
  HWLOGGING.print(F("Serial 4D Library reports error ")) ;
  HWLOGGING.print(Error4DText[ErrCode]) ;

  if (ErrCode == Err4D_NAK)
  {
    HWLOGGING.print(F(" returned data= ")) ;
    HWLOGGING.println(ErrByte) ;
  }
  else
    HWLOGGING.println(F("")) ;
  while(1) ; // you can return here, or you can loop
#else
// Pin 13 has an LED connected on most Arduino boards. Just give it a name
#define led 13
  while(1)
  {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(200);               // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(200);               // wait for a second
  }
#endif
}

void setup()
{
#ifdef LOG_MESSAGES
  HWLOGGING.begin(19200);
  HWLOGGING.print(F("\n\nBigDemo for Arduino\n"));
#endif
}

void loop()
{
  int i, rc ;
  char wks[20] ;
  Display.TimeLimit4D   = 5000 ; // 2 second timeout on all commands
  Display.Callback4D = Callback ; // NULL ;
  DisplaySerial.begin(9600) ;

  Display.gfx_Cls() ;
  fmediatests = trymount() ;
  Display.sys_GetModel(wks) ; // length is also returned, but we don't need that here
  HWLOGGING.print(F("Display model: ")) ;
  HWLOGGING.println(wks) ;
  Display.putstr("Model:\n") ;
  Display.putstr(wks) ;
  i = strlen(wks) ;
  HWLOGGING.print(F("SPE2 Version: ")) ;
  HWLOGGING.println(Display.sys_GetVersion()) ;
  HWLOGGING.print(F("PmmC Version: ")) ;
  HWLOGGING.println(Display.sys_GetPmmC()) ;
  if (fmediatests)
    HWLOGGING.println(F("Media tests will be done\n")) ;
  else
    HWLOGGING.println(F("Media tests cannot be done, missing uSD card\n")) ;
  
  delay(5000) ;
  
  gfx_Part1() ; // GFX Part 1 tests
  delay(5000) ;
  
  gfx_Part2() ; // GFX Part 2 tests
  delay(5000) ;
  
  text_Tests() ; // text tests
  delay(5000) ;
  
  Joystick_Tests() ;
  delay(5000) ;
  
  Image_Tests() ;
  delay(5000) ;
  
  if (fmediatests)
  {
    Media_Tests() ;
    delay(5000) ;
  }

//  Display.SSTimeout(1000) ;
//  Display.SSSpeed(1) ;
//  Display.SSMode(0) ;

//Display.BeeP(40,2000) ;
  Display.gfx_Cls() ;
  setbaudWait(BAUD_19200) ;
  Display.putstr("Hi at 19200\n") ;
  setbaudWait(BAUD_9600) ;
  Display.putstr("Back to 9600\n") ;
  delay(5000);
}
