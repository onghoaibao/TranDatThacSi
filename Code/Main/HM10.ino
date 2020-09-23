#include "Header.h"

SoftwareSerial HM10(RX_HM10, TX_HM10);

void initHM10() {
  HM10.begin(9600);
  sendAT("AT+ROLE1", true, 500);
  sendAT("AT+IMME1", true, 500);
  sendAT("AT+RESET", true, 500);
  delay(1000);
}

void sendAT(String cmd, bool res, int tim) {
  HM10.print(cmd);
  HM10.write(0x0D);
  HM10.write(0x0A);
  delay(tim);
  String s = getInfoRX();
  if (res) {
    Serial.println(s);
  }
}

void scanIBeacon() {
  sendAT("AT+DISI?", true, 5000);
}

String getInfoRX() {
  String rs = "";
  while (HM10.available() > 0) {
    char c = HM10.read();
    rs += c;
  }
  return rs;
}
