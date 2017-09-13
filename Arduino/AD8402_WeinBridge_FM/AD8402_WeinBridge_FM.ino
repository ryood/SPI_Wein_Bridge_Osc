/*
  Wein Bridge Saw

  AD8402

  ノコギリ波で周波数変調
  POTの値を読み取って変調の周期を可変
  
  Digi-Potのチャンネル1, 2の抵抗値を可変

  Pinの接続
  A0 POT1
  10 CS
  11 MOSI
  13 SCK
*/

#include <SPI.h>
#include <MsTimer2.h>

// set pin 10 as the slave select for the digital pot:
const int slaveSelectPin = 10;

uint8_t f0 = 0; // 初期周波数設定
uint8_t period = 1; // テンポ設定

void setup() {
  // set the slaveSelectPin as an output:
  pinMode (slaveSelectPin, OUTPUT);
  digitalWrite(slaveSelectPin, HIGH);
  // initialize SPI:
  SPI.begin();
  delay(1);

  Serial.begin(9600);  
  Serial.println("Wein Bridge FM (Saw Wave) Test.");

  MsTimer2::set(period, generateEnvelope);
  MsTimer2::start();
}

void loop() {
  int _f0 = analogRead(1) / 4;
  int _period = analogRead(0) / 128;
  if (_f0 != f0 || _period != period) {
    f0 = _f0;
    period = _period;
    
    MsTimer2::stop();
    MsTimer2::set(period, generateEnvelope);
    MsTimer2::start();

    Serial.print(f0);
    Serial.print("\t");
    Serial.print(period);
    Serial.print("\n");
  }
}

void generateEnvelope()
{
  static uint8_t cnt = 0;

  if (cnt < f0) {
    cnt = f0;
  }
  digitalPotWrite(0, cnt);
  digitalPotWrite(1, cnt);
  cnt++;
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

