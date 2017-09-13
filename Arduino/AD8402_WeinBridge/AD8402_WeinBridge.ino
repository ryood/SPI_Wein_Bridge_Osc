/*
  Wein Bridge Control

  AD8402

  POTの出力電圧を読み取って
  Digi-Potのチャンネル1, 2の抵抗値を可変

  Pinの接続
  A0 POT1
  10 CS
  11 MOSI
  13 SCK
*/

// inslude the SPI library:
#include <SPI.h>

// set pin 10 as the slave select for the digital pot:
const int slaveSelectPin = 10;

byte v0;

void setup() {
  // set the slaveSelectPin as an output:
  pinMode (slaveSelectPin, OUTPUT);
  digitalWrite(slaveSelectPin, HIGH);
  // initialize SPI:
  SPI.begin();
  delay(1);

  Serial.begin(9600);  
  Serial.println("Wein Bridge Test.");
}

void loop() {
  int v = analogRead(0) / 4;
  if (v != v0) {
    v0 = v;
  
    Serial.print(v0);
    Serial.print("\n");
    
    digitalPotWrite(0, v0);
    digitalPotWrite(1, v0);
  }
}

void digitalPotWrite(int address, int value) {
  // take the SS pin low to select the chip:
  digitalWrite(slaveSelectPin, LOW);
  //  send in the address and value via SPI:
  SPI.transfer(address);
  SPI.transfer(value);
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin, HIGH);
}

