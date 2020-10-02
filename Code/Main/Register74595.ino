#include "Header.h"

const byte pin = D0;
//  writeByte(0xDF);   // Cam + coi ON
//  writeByte(0xBF);   // Do + Coi ON
//  writeByte(0x7F);   // Coi + Do + Cam = OFF

void initRegister() {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, 1);
}

void Bit1() {
  digitalWrite(pin, 0);
  delayMicroseconds(1);
  digitalWrite(pin, 1);
  delayMicroseconds(15);
}

void Bit0() {
  digitalWrite(pin, 0);
  delayMicroseconds(15);
  digitalWrite(pin, 1);
  delayMicroseconds(30);
}

void Latch() {
  digitalWrite(pin, 0);
  delayMicroseconds(200);
  digitalWrite(pin, 1);
  delayMicroseconds(300);
}

void WriteByte(byte data) {
  for (int i = 0; i < 8; i++) {
    if (data & (1 << i)) {
      Bit1();
    }
    else {
      Bit0();
    }
  }
  Latch();
}

void LevelOneAlarm(int t) {
  int i = 0;
  WriteByte(0xDF);
  while (i < t) {
    handleClientServer();
    delay(1);
    i++;
  }
  i = 0;
  WriteByte(0x7F);
  while (i < t) {
    handleClientServer();
    delay(1);
    i++;
  }
}

void LevelTwoAlarm(int t) {
  int i = 0;
  WriteByte(0xBF);
  while (i < t) {
    handleClientServer();
    delay(1);
    i++;
  }
  i = 0;
  WriteByte(0x7F);
  while (i < t) {
    handleClientServer();
    delay(1);
    i++;
  }
}

void ConnectWifiAlarm() {
  WriteByte(0x9F);
  delay(200);
  WriteByte(0x7F);
  delay(200);
  WriteByte(0x9F);
  delay(200);
  WriteByte(0x7F);
  delay(200);
}

void turnOffArlam() {
  WriteByte(0x7F);
}
