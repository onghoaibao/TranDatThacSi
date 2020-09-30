#include "Header.h"


void handleData(String sData) {
  initMapData();
  date_now = getDateFormat();
  time_now = getTimeFormat();
  String sSaveFile = "";
  for (int i = 0; i < 10; i++) {
    String mac = listmac[i];
    if (mac != "") {
      int ix = sData.indexOf(mac);
      if (ix != -1) {
        String sR = sData.substring(ix - 11, ix - 1);
        Serial.println(sR + " -- " + String(sR.length()));
        String major = sR.substring(0, 4);
        String minor = sR.substring(4, 8);
        int majo = convertHexToDec(major);
        int mnor = convertHexToDec(minor);
        int pos1 = majo / 100;
        int pos2 = majo % 100;
        int pos3 = mnor;
        Serial.println("Temper pos 1: " + String(pos1));
        Serial.println("Temper pos 2: " + String(pos2));
        Serial.println("Temper pos 3: " + String(pos3));
        mapData[mac] = {{String(pos1), String(pos2), String(pos3)}};
        sSaveFile += mapName[mac] + "," + String(pos1) + "," + String(pos2) + "," +  String(pos3) + "," + time_now + "/" + date_now + "\n";
        //saveData(mapName[mac], String(pos1), String(pos2), String(pos3), time_now + "-" + date_now);
      }
      else{
        sSaveFile += mapName[mac] + "," + String(9999) + "," + String(9999) + "," +  String(9999) + "," + time_now + "/" + date_now + "\n";
      }
    }
  }
  Serial.println(sSaveFile);
  saveDataToFile(sSaveFile);
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
