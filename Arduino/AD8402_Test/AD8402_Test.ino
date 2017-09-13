/*
  AD8402 Example
*/

// inslude the SPI library:
#include <SPI.h>


// set pin 10 as the slave select for the digital pot:
const int slaveSelectPin = 10;

void setup() {
  // set the slaveSelectPin as an output:
  pinMode (slaveSelectPin, OUTPUT);
  digitalWrite(slaveSelectPin, HIGH);
  // initialize SPI:
  SPI.begin();
  delay(100);
}

void loop() {
  for (int channel = 0; channel < 2; channel++) {
    for (int level = 0; level < 255; level++) {
      digitalPotWrite(channel, level);
      delay(1);
    }
    // wait a second at the top:
    delay(100);
    // change the resistance on this channel from max to min:
    for (int level = 0; level < 255; level++) {
      digitalPotWrite(channel, 255 - level);
      delay(1);
    }
  }
}

void digitalPotWrite(int channel, int value) {
  SPI.beginTransaction(SPISettings(4
  000000, MSBFIRST, SPI_MODE0));
  // take the SS pin low to select the chip:
  digitalWrite(slaveSelectPin, LOW);
  //  send in the address and value via SPI:
  SPI.transfer(channel);
  SPI.transfer(value);
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin, HIGH);
  SPI.endTransaction();
}
