/*
AUTHOR: ROBERT LINNEMANN
CLASS: ECEN 495
LATEST UPDATE: 11/11/22
DESCRIPTION:
THIS CODE READS DISTANCE DATA FROM 4 SENSORS AND 

*/

#include "Adafruit_VL53L0X.h"
#include "PluggableUSBHID.h"
#include "USBKeyboard.h"

// DEFINE THE ADDRESSES OF THE SENSORS
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define LOX3_ADDRESS 0x32
#define LOX4_ADDRESS 0x34

// DEFINING THE VALUES OF THE SHUTDOWN PINS
#define SHT_LOX1 1
#define SHT_LOX2 2
#define SHT_LOX3 3
#define SHT_LOX4 0

// OBJECTS FROM THE LIBRARY
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox4 = Adafruit_VL53L0X();

// INIT OF KEYBOARD IN USBKEYBOARD LIBRARY
USBKeyboard Keyboard;

// STORAGE FOR MEASURED VALUES
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;
VL53L0X_RangingMeasurementData_t measure3;
VL53L0X_RangingMeasurementData_t measure4;

// ARRAYS TO STORE THE STATE OF EACH NOTE FOR EACH SENSOR
int sensorState1[2];
int sensorState2[2];
int sensorState3[2];
int sensorState4[2];

/*

    SDA => Pin 6 (GP4)
    SCL => Pin 7 (GP5)
    XSHUT1 => Pin 10 (GP7)
    XSHUT2 => Pin 9 (GP6)
    XSHUT3 => Pin 12 (GP9)

 */

// ASSIGNING THE ADDRESS TO EACH OF THE SENSORS
void setID() {
  // SET ALL SHUT DOWN PINS LOW
  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  digitalWrite(SHT_LOX4, LOW);
  delay(10);

  // SET ALL SHIT DOWN PINS HIGH 
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  digitalWrite(SHT_LOX3, HIGH);
  digitalWrite(SHT_LOX4, HIGH);
  delay(10);

  // TURNING ON THE FIRST SENSOR
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  digitalWrite(SHT_LOX4, LOW);

  // INIT FOR SENSOR 1
  if(!lox1.begin(LOX1_ADDRESS)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while(1);
  }
  delay(10);

  // TURNING ON THE SECOND SENSOR
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);
  // INIT SENSOR 2
  if(!lox2.begin(LOX2_ADDRESS)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while(1);
  }
  delay(10);

  // TURNING ON THE THIRD SENSOR
  digitalWrite(SHT_LOX3, HIGH);
  delay(10);

  // INIT SENSOR 3
  if(!lox3.begin(LOX3_ADDRESS)) {
    Serial.println(F("Failed to boot third VL53L0X"));
    while(1);
  }

  // TURN ON THE FOURTH SENSOR
  digitalWrite(SHT_LOX4, HIGH);
  delay(10);

  // INIT SENSOR 4
  if(!lox4.begin(LOX4_ADDRESS)) {
    Serial.println(F("Failed to boot fourth VL53L0X"));
    while(1);
  }
}

// READING THE VALUE OF THE SENSORS
// DESCRIPTION IS WRITTEN FOR THE FIRST SENSOR AND SAME LOGIC CONTINUES FOR THE REST
void read_dual_sensors() {

  lox1.rangingTest(&measure1, false);
  lox2.rangingTest(&measure2, false); 
  lox3.rangingTest(&measure3, false);
  lox4.rangingTest(&measure4, false);   

  // READ THE VALUE OF THE FIRST SENSOR
  Serial.print(F("1: "));
  if(measure1.RangeStatus != 4) { 
    Serial.print(measure1.RangeMilliMeter);
    Serial.print("\n");
    if(measure1.RangeMilliMeter < 70){
      if(sensorState1[0] == 1){ //CHECK TO SEE IF THIS NOTE WAS THE LAST ONE THAT WAS PLAYED
        // IF THIS NOTE WAS ALREADY PLAYED THEN DO NOTHING 
      }
      else{
        // IF THIS IS A NEW NOTE THEN PLAY IT
        Keyboard.printf("jjjjjjjjjjj"); // PLAY THE NOTE
        sensorState1[0] = 1; // UPDATE THE ARRAY TO STATE THAT THE NOTE WAS PLAYED
        sensorState1[1] = 0; // ENSURE THAT THE PROGRAM DOES NOT THINK THE OTHER NOTE ON THE SENSOR WAS PLAYED
      }
    }
    else if(measure1.RangeMilliMeter > 70 && measure1.RangeMilliMeter  < 100){ // SAME AS ABOVE BUT FOR THE OTHER NOTE ON THE SENSOR
      if (sensorState1[1] == 1){ 
        // DO NOTHING
      }
      else{
        Keyboard.printf("kkkkkkkkkkk");
        sensorState1[0] = 0;
        sensorState1[1] = 1;
      }
    }
    else if (measure1.RangeMilliMeter > 100){ // IF THERE IS NOTHING BEING PLAYED THEN RESET THE VALUES IN THE ARRAY
      sensorState1[0] = 0;
      sensorState1[1] = 0;
    }
  }
  else {
    Serial.print(F("Out of range")); // SHOULD NEVER BE THE CASE SO IF THIS IS SEEN THEN SOMETHING IS WRONG
  }
  Serial.print(F(" ")); // PRINT NEW SPACE

  // READ THE VALUE OF THE SECOND SENSOR
  Serial.print(F("2: "));
  if(measure2.RangeStatus != 4) {
    Serial.print(measure2.RangeMilliMeter);
    Serial.print("\n");
    if(measure2.RangeMilliMeter < 50){
      if (sensorState2[0] == 1){
        // DO NOTHING
      }
      else{
        Keyboard.printf("ggggggggggg");
        sensorState2[0] = 1;
        sensorState2[1] = 0;
      }
    }
    else if(measure2.RangeMilliMeter > 50 && measure2.RangeMilliMeter  < 75){
      if (sensorState2[1] == 1){
        // DO NOTHING
      }
      else{
        Keyboard.printf("hhhhhhhhhhh");
        sensorState2[0] = 0;
        sensorState3[1] = 1;
      }
    }
    else if (measure2.RangeMilliMeter > 80){
      sensorState2[0] = 0;
      sensorState2[1] = 0;
    }
  }
  else {
    Serial.print(F("Out of range"));
  }
  Serial.print(F(" "));

  // READ THE VALUE OF THE THIRD SENSOR
  Serial.print(F("3: "));
  if(measure3.RangeStatus != 4) {
    Serial.print(measure3.RangeMilliMeter);
    Serial.print("\n");
    if(measure3.RangeMilliMeter < 85){
      if (sensorState3[0] == 1){
        // DO NOTHING
      }
      else{
        Keyboard.printf("ddddddddddd");
        sensorState3[0] = 1;
        sensorState3[1] = 0;
      }
    }
    else if(measure3.RangeMilliMeter > 85 && measure3.RangeMilliMeter  < 118){
      if (sensorState3[1] == 1){
        // DO NOTHING
      }
      else{
        Keyboard.printf("fffffffffff");
        sensorState3[0] = 0;
        sensorState3[0] = 1;
      }
    }
    else if(measure3.RangeMilliMeter > 120){
      sensorState3[0] = 0;
      sensorState3[1] = 0;
    }
  }
  else {
    Serial.print(F("Out of range"));
  }
  Serial.print(F(" "));

  // READ THE VALUE OF THE FOURTH SENSOR
  Serial.print(F("4: "));
  if(measure4.RangeStatus != 4) {
    Serial.print(measure4.RangeMilliMeter);
    Serial.print("\n");
    if(measure4.RangeMilliMeter < 55){
      if(sensorState4[0] == 1){
        // DO NOTHING
      }
      else{
        Keyboard.printf("aaaaaaaaaaa");
        sensorState4[0] = 1;
        sensorState4[1] = 0;
      }
    }
    else if(measure4.RangeMilliMeter > 55 && measure4.RangeMilliMeter  < 90){
      if (sensorState4[1] == 1){
        // DO NOTHING
      }
      else{
        Keyboard.printf("sssssssssss");
        sensorState4[0] = 0;
        sensorState4[1] = 1;
      }
    }
    else if(measure4.RangeMilliMeter > 100){
      sensorState4[0] = 0;
      sensorState4[1] = 0;
    }
  }
  else {
    Serial.print(F("Out of range"));
  }
}

void setup() {
  Serial.begin(115200);

  // WAITS UNTIL THE SERIAL PORT IS OPENED
  while (! Serial) { delay(1); }

  // SETUP THE SHUT DOWN PINS
  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);
  pinMode(SHT_LOX3, OUTPUT);
  pinMode(SHT_LOX4, OUTPUT);

  // I THINK THIS WAS FOR BUTTONS CAN BE TAKEN OUT ===================================================================================
  pinMode(29, INPUT);

  Serial.println(F("Shutdown pins inited..."));

  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  digitalWrite(SHT_LOX4, LOW);

  Serial.println(F("All in reset mode...(pins are low)"));

  Serial.println(F("Starting..."));
  setID();

}

void loop() {

  read_dual_sensors();
  delay(10);

}
