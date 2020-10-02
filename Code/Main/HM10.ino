#include "Header.h"

SoftwareSerial HM10(RX_HM10, TX_HM10);

void initHM10() {
  pinMode(RX_HM10, INPUT);
  pinMode(TX_HM10, OUTPUT);
  HM10.begin(9600, SWSERIAL_8N1, RX_HM10, TX_HM10, false, 512);
  delay(1000);
  sendAT("AT+ROLE1", true, 500);
  sendAT("AT+IMME1", true, 500);
  sendAT("AT+SCAN3", true, 500);
  sendAT("AT+RESET", true, 500);
}

void sendAT(String cmd, bool res, int tim) {
  HM10.print(cmd);
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

String iBeaconScanner() {
  clearBuffer();
  String sData = "";
  String sdt = "";
  long _time = 0;
  Serial.print("\r\n");
  sendAT("AT+RESET", true, 1000);
  HM10.print("AT+DISI?");
  wait(3000);
  int i = 0;
  while (1) {
    handleClientServer();
    while (HM10.available() > 0) {     
      char c = HM10.read();
      //Serial.print(c);
      sData += c;
      sData.replace("OK+DISC:00000000:00000000000000000000000000000000:0000000000:", "");
      _time = 0;
      handleClientServer();
    }
    if (sData.indexOf("OK+DISCE") != -1 && _time >= 2000) {
      Serial.println("sData iBeacon: " + sData + "\n");
      break;
    }
    _time++;
    delay(1);
  }
  return sData;
}



void clearBuffer() {
  while (HM10.available() > 0) {
    char c = HM10.read();
  }
}

void getUUIDByIBeacon(String sData) {
  int i = 0;
  String listTemp[3] = {};
  int f1 = sData.indexOf("OK+DISC:");
  int f2 = sData.indexOf("OK+DISC:", f1 + 1);
  while (f1 != -1) {
    String sSub = sData.substring(f1, f2);
    if (sSub.indexOf("OK+DISCE") != -1) {
      String s1 = sData.substring(f1 + 17, sData.length() - 7);
      listTemp[i] = s1;
      break;
    }
    else {
      String s1 = sData.substring(f1 + 17, f2);
      listTemp[i] = s1;
    }
    f1 = sData.indexOf("OK+DISC:", f1 + 1);
    f2 = sData.indexOf("OK+DISC:", f1 + 1);
    i += 1;
  }

  for (int k = 0; k < 3; k++) {
    Serial.println("K=" + String(k) + "  " + listTemp[k]);
  }
}

long convertHEXtoInt(String data) {
  if (data.length() <= 5) {
    char buf[5] = {};
    data.toCharArray(buf, 5);
    long lValue = strtoul(buf, 0, HEX);
    return lValue;
  }
  return 99;
}
