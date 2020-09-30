#include "Header.h"

const byte TX_BLE103 = 3;
const byte RX_BLE103 = 2;
const byte ReS_BLE13 = 4;

SoftwareSerial BLE103(RX_BLE103, TX_BLE103);

void initBLE103(){
  pinMode(ReS_BLE13, OUTPUT);
  digitalWrite(ReS_BLE13, 1);
  BLE103.begin(57600);
  digitalWrite(ReS_BLE13, 0);
  getResBLE103(500);
  modeBLE103();
}

void modeBLE103(){
  BLE103.print("+++a");
  delay(1000);
  setCommandBLE("AT+MODE=B", 200);
  delay(100);
  setCommandBLE("AT+Z", 200);
  delay(100);
}

void setCommandBLE(String cmd, int t){
    BLE103.print(cmd);
    BLE103.write(0x0D);
    BLE103.write(0x0A);
    getResBLE103(t);
}

String getResBLE103(int t){
  String rs = "";
  delay(t);
  while(BLE103.available() > 0){
    char c = BLE103.read();
    rs += c;
  }
  return rs;
}

void setDataToiBeacon(int tmp1, int tmp2, int tmp3){
  String cmd = IBEACON_COMMAND + String(tmp1*100 + tmp2) + "," + String(tmp3) + ",175";
  setCommandBLE(cmd, 500);
  setCommandBLE("AT+Z", 500);
}
