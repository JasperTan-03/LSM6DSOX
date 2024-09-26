#include "C:\Users\jaspe\OneDrive\Documents\Arduino\LSM6DSOX\src\LSM6DSOXSensor.h"

// Create an instance of the sensor
TwoWire i2c = Wire;
LSM6DSOXSensor sensor(&i2c);

// Interrupt pin number
const int interruptPinNumber = 2;

// Interrupt pin
LSM6DSOX_SensorIntPin_t interruptPin = LSM6DSOX_INT1_PIN;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize the sensor
  if (sensor.begin() != 0) {
    Serial.println("Failed to initialize the sensor!");
    while (1);
  }

  // Enable tap detection
  sensor.Enable_Single_Tap_Detection(interruptPin);

  // Configure the interrupt pin
  pinMode(interruptPinNumber, INPUT);
}

void loop() {
  // Check if the interrupt pin is triggered
  if (digitalRead(interruptPinNumber) == HIGH) {
    // Create a variable to hold the event status
    LSM6DSOX_Event_Status_t eventStatus;

    // Get the event status
    sensor.Get_X_Event_Status(&eventStatus);

    // Check if a tap event is detected
    if (eventStatus.TapStatus) {
      Serial.println("Tap detected!");
    }
  }
}