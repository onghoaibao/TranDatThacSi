#include "Header.h"

void setup() {
  Serial.begin(115200);
  Serial.println("\n------------------");
  //  initSDcard();
  initHM10();
  //  initLCD();
  //  initRegister();
  initFS();
  initServerLocal();
  delay(5000);
}
int i = 0;
void loop() {
  clearBuffer();
  String s = iBeaconScanner();
  handleData(s);
  // getUUIDByIBeacon(s);
  //Serial.println(s);
  //  String __time__ = getRealTime();
  //  if (__time__ != "") {
  //    handleClientServer();
  //    i++;
  //    Serial.println(__time__);
  //    handleClientServer();
  //    if (i == 3) {
  //      saveData(32, 33, 34, __time__);
  //      i = 0;
  //    }
  //    handleClientServer();
  //  }
  long i = 0;
  while (i < 5000) {
    delay(1);
    handleClientServer();
    i++;
  }
}

void handleData(String sData) {
  initMapData();
  for (int i = 0; i < 10; i++) {
    String mac = listmac[i];
    if (mac != "") {
      int ix = sData.indexOf(mac);
      if (ix != -1) {
        String sR = sData.substring(ix - 11, ix - 1);
        Serial.println(sR + " -- " + String(sR.length()));
        int major = sR.substring(0, 4).toInt();
        int minor = sR.substring(4, 8).toInt();
        int pos1 = major / 100;
        int pos2 = major % 100;
        int pos3 = minor % 100;       
        Serial.println("Temper pos 1: " + String(pos1));
        Serial.println("Temper pos 2: " + String(pos2));
        Serial.println("Temper pos 3: " + String(pos3));

        mapData[mac] = {{String(pos1), String(pos2), String(pos3)}};
      }
    }
  }
}


long convertHexToDec(String sdt) {
  char *endptr;
  char char_array[sdt.length() + 1];
  strcpy(char_array, sdt.c_str());
  long x = strtol(char_array, &endptr, 16);
  return x;
}

void initMapData() {
  for (int i = 0; i < 10; i++) {
    String mac = listmac[i];
    if (mac != "") {
      mapData[mac] = {{"9999", "9999", "9999"}};
    }
  }
}
