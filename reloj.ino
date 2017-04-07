/* 
 *  
 *  Reloj usando 4 digitos con display de 7 segmentos
 *  
 */

// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"
DS1307 rtc;

#include "SevSeg.h"
SevSeg sevseg; //Instantiate a seven segment controller object

void setup() {

  Wire.begin();
  rtc.begin();

  if (! rtc.isrunning()) {
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }
  
  byte numDigits = 4;
  byte digitPins[] = {11, 10, 9, 6};
  byte segmentPins[] = {0, 1, 4, 5, 12, 7, 8, 13};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE; // See README.md for options
  bool updateWithDelays = false; // Default. Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros);
  sevseg.setBrightness(90);
}

void loop() {

  DateTime now = rtc.now();

  int _hour = now.hour() * 100 + now.minute();
  
  sevseg.setNumber(_hour, 2);

  sevseg.refreshDisplay(); // Must run repeatedly
}

/// END ///
