//Simple Demo that demonstrates 'print' and 'println' new functionality.

#define DisplaySerial Serial

//-------Picaso DISPLAYS-------

#include "Goldelox_Serial_4DLib.h"
#include "Goldelox_Const4D.h"

//use Serial0 to communicate with the display.
Goldelox_Serial_4DLib Display(&DisplaySerial);

//---------END-----------------

void setup() {
  //For handling errors
  Display.Callback4D = mycallback ;

  //5 second timeout on all commands  
  Display.TimeLimit4D = 5000 ;
  
  DisplaySerial.begin(9600) ;

  //--------------------------------Optional reset routine-----------------------------------
  //Reset the Display using D4 of the Arduino (if using the new 4D Arduino Adaptor - Rev 2)
  //If using the old 4D Arduino Adaptor (Rev 1), change D4 to D2 below.
  //If using jumper wires, reverse the logic states below. 
  //Refer to the accompanying application note for important information.
  pinMode(4, OUTPUT);  // Set D4 on Arduino to Output (4D Arduino Adaptor V2 - Display Reset)
  digitalWrite(4, 1);  // Reset the Display via D4
  delay(100);
  digitalWrite(4, 0);  // unReset the Display via D4
  //-----------------------------------------END---------------------------------------------
  
  delay (5000); //let the display start up  

  Display.gfx_ScreenMode(LANDSCAPE);
  Display.SSTimeout(0) ;
  Display.SSSpeed(0) ;
  Display.SSMode(0) ;
  
  //Display.gfx_BGcolour(WHITE) ; //change background color to white
  Display.gfx_Cls();            //clear the screen

  char a = 'A';
  char a2 = 'B';
  int b = 1234;
  int b2 = -1234;
  long c = 123456;
  long c2 = -123456;
  String string = "This is string class";
  char charr[30] = "This is const char array";
  float d = 123.456789;
  float d2 = -123.456789;
  float nan = NAN;
  float inf = INFINITY;
  float ovf1 = 5294967040.0;
  float ovf2 = -5294967040.0;  
  
  Display.print(a); Display.print(' ');
  Display.println(a2);
  Display.print(b); Display.print(' ');
  Display.println(b2);
  Display.print(c); Display.print(' ');
  Display.println(c2);
  Display.println("This is String"); 
  Display.println(F("This is Flashstring"));  // COMMENT OUT FOR ARDUINO DUE, NOT SUPPORTED
  Display.println(string); 
  Display.println(charr);
  Display.println(d,6);
  Display.println(d2, 3);  
  Display.println(nan);
  Display.println(inf);  
  Display.println(ovf1);
  Display.println(ovf2);  

}

void loop() 
{

}

void mycallback(int ErrCode, unsigned char Errorbyte)
{
  // Pin 13 has an LED connected on most Arduino boards. Just give it a name
  int led = 13;
  pinMode(led, OUTPUT);
  while(1)
  {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(200);                // wait for 200 ms
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(200);                // wait for 200 ms
  }
}


