#include "Header.h"

const byte pin = D0;


void initRegister(){
  pinMode(pin, OUTPUT);  
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
  WriteByte(0x20);
  delay(t);
  WriteByte(0x00);
  delay(t);
}

void LevelTwoAlarm(int t) {
  WriteByte(0x10);
  delay(t);
  WriteByte(0x00);
  delay(t);
}
