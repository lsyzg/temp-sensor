/* SevSeg Humidity Display
 Modified from SevSeg Counter Example
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
 This example displays humidity readings from a DHT11 sensor on a 4-digit
 7-segment display showing percentage with one decimal place.
 */

#include "SevSeg.h"
#include <DHT11.h>

SevSeg sevseg; //Instantiate a seven segment controller object
DHT11 dht11(2); // DHT11 sensor on pin 2

void setup() {
  Serial.begin(9600);
  
  byte numDigits = 4;
  byte digitPins[] = {6, 7, 8, 9};
  byte segmentPins[] = {10, 11, 12, 13, 14, 15, 16, 19};
  
  bool resistorsOnSegments = true; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected
  
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);
  
  Serial.println("Humidity Display Starting...");
}

void loop() {
  // Attempt to read the humidity value from the DHT11 sensor
  int humidity = dht11.readHumidity();
  
  // Check the result of the reading
  // If there's no error, display the humidity value
  if (humidity != DHT11::ERROR_CHECKSUM && humidity != DHT11::ERROR_TIMEOUT) {
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
    
    // Display humidity with 1 decimal place (e.g., 65.0% shows as 65.0)
    // Multiply by 10 to shift decimal place for display
    sevseg.setNumber(humidity * 10, 1);
  } else {
    // Print error message and display error code on 7-segment
    Serial.println(DHT11::getErrorString(humidity));
    
    // Display "Err" or error pattern (8888) on the display
    sevseg.setNumber(8888, 0); // Show 8888 as error indicator
  }
  
  sevseg.refreshDisplay(); // Must run repeatedly
  
  // Small delay before next reading
  delay(100);
}

/// END ///