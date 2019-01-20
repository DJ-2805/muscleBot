#include <SparkFun_ADXL345.h>         // SparkFun ADXL345 Library
#include <SoftwareSerial.h>

ADXL345 adxl = ADXL345(10);           // USE FOR SPI COMMUNICATION, ADXL345(CS_PIN);
SoftwareSerial BT(7, 6);              // RX | TX: choose whatever, it doesn't matter

const long BTBaudRate = 38400; 
const long BTPeriod = 10; // millisec
const int LEFT = 4;
const int RIGHT = 2;
char movement;
int buffer = 25;

/******************** SETUP ********************/
void setup(){
  BT.begin(BTBaudRate);
  
  Serial.begin(9600);                 // Start the serial terminal
  Serial.println("Hello World!");
  Serial.println();

  adxl.powerOn();                     // Power on the ADXL345

  adxl.setRangeSetting(2);           // Give the range settings
  // Accepted values are 2g, 4g, 8g or 16g
  // Higher Values = Wider Measurement Range
  // Lower Values = Greater Sensitivity
  adxl.setSpiBit(0);                  // Configure the device to be in 4 wire SPI mode when set to '0' or 3 wire SPI mode when set to 1
                                      // Default: Set to 1
                                      // SPI pins on the ATMega328: 11, 12 and 13 as reference in SPI Library

  adxl.setActivityXYZ(1, 0, 0);       // Set to activate movement detection in the axes "adxl.setActivityXYZ(X, Y, Z);" (1 == ON, 0 == OFF)
  adxl.setActivityThreshold(75);      // 62.5mg per increment   // Set activity   // Inactivity thresholds (0-255)

  adxl.setInactivityXYZ(1, 0, 0);     // Set to detect inactivity in all the axes "adxl.setInactivityXYZ(X, Y, Z);" (1 == ON, 0 == OFF)
  adxl.setInactivityThreshold(75);    // 62.5mg per increment   // Set inactivity // Inactivity thresholds (0-255)
  adxl.setTimeInactivity(10);         // How many seconds of no activity is inactive?

  adxl.setTapDetectionOnXYZ(0, 0, 1); // Detect taps in the directions turned ON "adxl.setTapDetectionOnX(X, Y, Z);" (1 == ON, 0 == OFF)

  // Set values for what is considered a TAP and what is a DOUBLE TAP (0-255)
  adxl.setTapThreshold(50);           // 62.5 mg per increment
  adxl.setTapDuration(15);            // 625 μs per increment
  adxl.setDoubleTapLatency(80);       // 1.25 ms per increment
  adxl.setDoubleTapWindow(200);       // 1.25 ms per increment

  // Set values for what is considered FREE FALL (0-255)
  adxl.setFreeFallThreshold(7);       // (5 - 9) recommended - 62.5mg per increment
  adxl.setFreeFallDuration(30);       // (20 - 70) recommended - 5ms per increment

  // Setting all interupts to take place on INT1 pin
  //adxl.setImportantInterruptMapping(1, 1, 1, 1, 1);     // Sets "adxl.setEveryInterruptMapping(single tap, double tap, free fall, activity, inactivity);"
  // Accepts only 1 or 2 values for pins INT1 and INT2. This chooses the pin on the ADXL345 to use for Interrupts.
  // This library may have a problem using INT2 pin. Default to INT1 pin.

  // Turn on Interrupts for each mode (1 == ON, 0 == OFF)
  adxl.InactivityINT(1);
  adxl.ActivityINT(1);
  adxl.FreeFallINT(1);
  adxl.doubleTapINT(1);
  adxl.singleTapINT(1);

  //attachInterrupt(digitalPinToInterrupt(interruptPin), ADXL_ISR, RISING);   // Attach Interrupt

}

void loop() {
  // EGM Muscle Readings
  double sensorValue = analogRead(A0);
  Serial.println(sensorValue);

  // Accelerometer Readings
  int x,y,z;
  adxl.readAccel(&x, &y, &z);         // Read the accelerometer values and store them in variables declared above x,y,z

  // checking if muscle was flexed
  if(sensorValue >= 800 && !BT.available()) {
    if((-300+buffer > z && -300-buffer <= z) && (buffer > y && -1*buffer <= y)) {
      movement = 'd';
    }
    else if((-300+buffer > z && -300-buffer <= z) && (200+buffer > y && 200-buffer <= y)) {
      movement = 'a';
    }
    else if((200+buffer > x && 200-buffer < x) && (buffer > z && -1*buffer < z)) {
      movement = 'w';
    }
    else if((-300+buffer > x && 300-buffer < x) && (buffer > z && -1*buffer < z)) {
      movement = 's';
    }
  } else {
    movement = 'a';
    movement = BT.write(movement);
    Serial.println(movement);
  }

  delay(100);
}
