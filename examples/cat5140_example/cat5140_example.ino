/**
 * @file cat5140-example.cpp
 * @author Nick Steele (GitHub @nichlock)
 * @brief Example code for the CAT5140 digital potentiometer library.
 *
 * This example code demonstrates how to use the CAT5140 digital potentiometer
 * library.
 *
 * CONNECTIONS:
 * - CAT5140 SDA pin to the Arduino SDA pin (A4 on the Uno).
 * - CAT5140 SCL pin to the Arduino SCL pin (A5 on the Uno).
 * - CAT5140 GND pin to ground.
 * - CAT5140 VCC pin to 5V (3.3V will also work).
 * - CAT5140 WP pin to VCC
 */

#include <Arduino.h>
#include <Wire.h>
#include <cat5140.h>

// Create a CAT5140 object with the default address (0x28) and Wire object.
CAT5140 cat5140;

void setup() {
  // Initialize the serial port.
  Serial.begin(115200);

  // Initialize the I2C bus.
  Wire.begin();

  // Wait for the serial port to be ready.
  while (!Serial) {
    delay(1);
  }

  // Verify connection by checking device ID.
  Serial.print("Connecting to CAT5140... ");
  uint8_t devid = cat5140.readDeviceId();
  if (devid != 0xD0) {
    Serial.println("Failed.");
    Serial.print("Device ID: 0x");
    Serial.println(devid, HEX);
    while (1) {
      delay(1000);
    }
  }

  Serial.println("Success.");
}

void loop() {
  for (int i = 0; i < 256; i++) {
    // Write a value to the CAT5140
    cat5140.writeWiper((uint8_t)i);

    // Read the value back from the CAT5140
    uint8_t value = cat5140.readWiper();

    // Print the value to the serial port
    Serial.println(value);

    // Wait some time before repeating
    delay(500);
  }
}
