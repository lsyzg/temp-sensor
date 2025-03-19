#include <DHT11.h>


/* SevSeg Counter Example

 Copyright 2017 Dean Reading

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.


 This example demonstrates a very simple use of the SevSeg library with a 4
 digit display. It displays a counter that counts up, showing deci-seconds.
 */

#include "SevSeg.h"
#include <DHT11.h>
SevSeg sevseg; //Instantiate a seven segment controller object

DHT11 dht11(2);

void setup() {
  byte numDigits = 4;
  // byte digitPins[] = {9, 10, 11, 12};
  byte digitPins[] = {6, 7, 8, 9};
  // byte segmentPins[] = {14, 15, 16, 17, 19, 20, 21, 22};
  byte segmentPins[] = {10, 11, 12, 13, 14, 15, 16, 19};
  
  bool resistorsOnSegments = true; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);
}

void loop() {
    // Attempt to read the temperature value from the DHT11 sensor.
    int temperature = dht11.readTemperature();
    // int sampling = 

    // Check the result of the reading.
    // If there's no error, print the temperature value.
    // If there's an error, print the appropriate error message.
    sevseg.setNumber(temperature, 0);
  sevseg.refreshDisplay(); // Must run repeatedly
}

/// END ///
