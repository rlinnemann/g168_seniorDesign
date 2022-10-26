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

int keys[] = {4,5};//gpio 4 and 5

void setup() {
 // put your setup code here, to run once:
 for (int i = 4; i < 6; ++i) {
 // initilize pins
 pinMode(i, INPUT);
 }
}
void loop() {
 // put your main code here, to run repeatedly:
 for (int i = 4; i < 6; ++i) {
 // check buttons
 if(readButton(i)) {
 doAction(i); 
 }
 }
}
boolean readButton(int pin) {
 // check and debounce buttons
 if (digitalRead(pin) == HIGH) {
 delay(100);
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
 Keyboard.printf("drive.google.com");
 break;
 case 5:
 Keyboard.printf("makeuseof.com");
 break;
 
 }
}
