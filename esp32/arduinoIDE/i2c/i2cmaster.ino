#include "Wire.h"

#define I2C_DEV_ADDR 0x55  // defined I2C address

uint32_t i = 100; // counter variable

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Wire.begin();
}

void loop() {
  delay(5000);

  // Write message to the slave through I2C
  Wire.beginTransmission(I2C_DEV_ADDR);
  Wire.printf("Hi there, this data is sent from master! value: %lu", i++);
  uint8_t error = Wire.endTransmission(true);
  if (error == 0)
  Serial.printf("End of Transmission, with no error\n");

  // Read 16 bytes from the slave
  uint8_t bytesReceived = Wire.requestFrom(I2C_DEV_ADDR, 16);
  
  Serial.printf("requestFrom: %u\n", bytesReceived);
  if ((bool)bytesReceived) {  //If received more than zero bytes
    uint8_t temp[bytesReceived];
    Wire.readBytes(temp, bytesReceived);
    log_print_buf(temp, bytesReceived);
  }
}
