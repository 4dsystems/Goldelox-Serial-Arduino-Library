Copy the Goldelox_Serial_4DLib folder to your Arduino 'libraries' folder
Copy the GoldeloxBigDemo folder to your Arduino 'projects' folder

NB!
There is an issue with SoftwareSerial in Arduino 1.0.2 + 1.0.3 and
possibly above which affects Goldelox Displays, refer here:-
https://github.com/arduino/Arduino/issues/1195 to fix you must edit
SoftwareSerial.cpp and find the setTX function and change the first two
statements so it becomes:-

void SoftwareSerial::setTX(uint8_t tx)
{
pinMode(tx, INPUT_PULLUP);
pinMode(tx, OUTPUT);