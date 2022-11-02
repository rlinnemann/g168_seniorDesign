/*
This code reads from four sensors
The distances are translated to keycommands
if it already printed a value, dont print the same one again
WANT TO ADD
-----------
button that stops 
reverb on and off button
*/

#include "Adafruit_VL53L0X.h"
#include "PluggableUSBHID.h"
#include "USBKeyboard.h"

USBKeyboard Keyboard;

int keys[] = {4,5,6,7,8};//gpio 4 and 5

void setup() {
 Serial.begin(115200);
 // put your setup code here, to run once:
 for (int i = 4; i < 9; ++i) {
 // initilize pins
 pinMode(i, INPUT);
 }
}
void loop() {
 // put your main code here, to run repeatedly:
 for (int i = 4; i < 9; ++i) {
 // check buttons
 if(readButton(i)) {
 doAction(i); 
 }
 }
}

boolean readButton(int pin) {
 // check and debounce buttons
   if (digitalRead(pin) == HIGH) {
     delay(50);
   if (digitalRead(pin) == HIGH) {
    return true;
   }
   }
  return false;
}


void doAction(int pin) {
 // perform tasks
 switch (pin) {
 case 4:
  Keyboard.key_code(' ', KEY_SHIFT);//start recording
  delay(100);
 break;
  
 case 5:
  Keyboard._putc(RIGHT_ARROW);//increase octave by one
  delay(100);
 break;

 case 6:
  Keyboard._putc(LEFT_ARROW);//decrease octave by one
  delay(100);
 break;

 case 7:
  Keyboard.key_code('n',KEY_CTRL);//open a new session
  delay(100);
 break;

 case 8:
  Keyboard.key_code(1,KEY_ALT);//Mute/unmute, NOTE(havent gotten this one to work yet)
  delay(100);
 break;
 
 default:
  Serial.println("Doing Nothing");
 break;

 }
}
