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

// address we will assign if multiple sensors are present
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define LOX3_ADDRESS 0x33
#define LOX4_ADDRESS 0x34

// set the pins to shutdown
#define SHT_LOX1 1
#define SHT_LOX2 2
#define SHT_LOX3 3
#define SHT_LOX4 4


// objects for the vl53l0x
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox4 = Adafruit_VL53L0X();


USBKeyboard Keyboard;

// this holds the measurement
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;
VL53L0X_RangingMeasurementData_t measure3;
VL53L0X_RangingMeasurementData_t measure4;


int sensorState1;
int sensorState2;
int sensorState3;
int sensorState4;

/*
    Reset all sensors by setting all of their XSHUT pins low for delay(10), then set all XSHUT high to bring out of reset
    Keep sensor #1 awake by keeping XSHUT pin high
    Put all other sensors into shutdown by pulling XSHUT pins low
    Initialize sensor #1 with lox.begin(new_i2c_address) Pick any number but 0x29 and it must be under 0x7F. Going with 0x30 to 0x3F is probably OK.
    Keep sensor #1 awake, and now bring sensor #2 out of reset by setting its XSHUT pin high.
    Initialize sensor #2 with lox.begin(new_i2c_address) Pick any number but 0x29 and whatever you set the first sensor to

    CHECK THIS
    ---------------------------------
    SDA => Pin 6 (GP4)
    SCL => Pin 7 (GP5)
    XSHUT1 => Pin 2 (GP1)
    XSHUT2 => Pin 4 (GP2)
    XSHUT3 => Pin 5 (GP3)
    XSHUT4 => Pin 6 (GP4)
*/

void setID() {
  // all reset
  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  digitalWrite(SHT_LOX4, LOW);
  delay(10);
    
  // all unreset
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  digitalWrite(SHT_LOX3, HIGH);
  digitalWrite(SHT_LOX4, HIGH);
  delay(10);

  // activating LOX1 and resetting LOX2
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  digitalWrite(SHT_LOX4, LOW);

  // initing LOX1
  if(!lox1.begin(LOX1_ADDRESS)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while(1);
  }
  delay(10);

  // activating LOX2
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  //initing LOX2
  if(!lox2.begin(LOX2_ADDRESS)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while(1);
  }
  delay(10);

  // activating LOX3
  digitalWrite(SHT_LOX3, HIGH);
  delay(10);

  //initing LOX3
  if(!lox3.begin(LOX3_ADDRESS)) {
    Serial.println(F("Failed to boot third VL53L0X"));
    while(1);
  }
    
  // activating LOX4
  digitalWrite(SHT_LOX4, HIGH);
  delay(10);

  //initing LOX4
  if(!lox4.begin(LOX4_ADDRESS)) {
    Serial.println(F("Failed to boot fourth VL53L0X"));
    while(1);
  }
  
}

void read_dual_sensors() {

  lox1.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!
  lox2.rangingTest(&measure2, false); // pass in 'true' to get debug data printout!
  lox3.rangingTest(&measure3, false); // pass in 'true' to get debug data printout!
  lox4.rangingTest(&measure4, false); // pass in 'true' to get debug data printout!
  
  // print sensor one reading    
  Serial.print(F("1: "));
  if(measure1.RangeStatus != 4) {     // if not out of range
    Serial.print(measure1.RangeMilliMeter);
    Serial.print("\n");
    if(measure1.RangeMilliMeter < 200){
      if(sensorState1 == 1){
        //Do Nothing
      }
      else{
        Keyboard.printf("qqqqqqqqqqq");
        sensorState1 = 1;
      }
    }
    else if(measure1.RangeMilliMeter > 300 && measure1.RangeMilliMeter  < 400){
      if(sensorState1 == 2){
        //Do Nothing
      }
      else{
        Keyboard.printf("wwwwwwwwwww");
        sensorState1 = 2;
      }
    }
  }
  else {
    Serial.print(F("Out of range"));
  }
  Serial.print(F(" "));

  // print sensor two reading
  Serial.print(F("2: "));
  if(measure2.RangeStatus != 4) {
    Serial.print(measure2.RangeMilliMeter);
    Serial.print("\n");
    if(measure2.RangeMilliMeter < 200){
      if(sensorState2 == 1){
        //Do Nothing
      }
      else{
        Keyboard.printf("ttttttttttt");
        sensorState2 = 1;
      }
    }
    else if(measure2.RangeMilliMeter > 200 && measure2.RangeMilliMeter  < 400){
      if(sensorState2 == 2){
        //Do Nothing
      }
      else{
        Keyboard.printf("yyyyyyyyyyy");
        sensorState2 = 2;
      }
    }
  }
  else {
    Serial.print(F("Out of range"));
  }
  Serial.print(F(" "));

  //print sensor 3 reading
  Serial.print(F("3: "));
  if(measure3.RangeStatus != 4) {
    Serial.print(measure3.RangeMilliMeter);
    Serial.print("\n");
    if(measure3.RangeMilliMeter < 200){
      if(sensorState3 == 1){
        //Do Nothing
      }
      else{
        Keyboard.printf("ooooooooooo");
        sensorState3 = 1;
      }
    }
    else if(measure3.RangeMilliMeter > 200 && measure3.RangeMilliMeter  < 400){
      if(sensorState3 == 2){
        //Do Nothing
      }
      else{
        Keyboard.printf("ppppppppppp");
        sensorState3 = 2;
      }
    }
  } 
  else {
    Serial.print(F("Out of range"));
  }   
  Serial.print(F(" "));

  //print sensor 4 reading
  Serial.print(F("4: "));
  if(measure4.RangeStatus != 4) {
    Serial.print(measure4.RangeMilliMeter);
    Serial.print("\n");
    if(measure4.RangeMilliMeter < 200){
      if(sensorState4 == 1){
        //Do Nothing
      }
      else{
        Keyboard.printf("ooooooooooo");
        sensorState4 = 1;
      }
    }
    else if(measure4.RangeMilliMeter > 200 && measure4.RangeMilliMeter  < 400){
      if(sensorState4 == 2){
        //Do Nothing
      }
      else{
        Keyboard.printf("ppppppppppp");
        sensorState4 = 2;
      }
    }
  } 
  else {
    Serial.print(F("Out of range"));
  } 
}

void setup() {
  Serial.begin(115200);

  // wait until serial port opens for native USB devices (MAKES YOU NEED PUTTY)
  while (! Serial) { delay(1); }

  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);
  pinMode(SHT_LOX3, OUTPUT);
  pinMode(SHT_LOX4, OUTPUT);

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
  delay(100);
}
