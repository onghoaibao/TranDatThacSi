#include "Header.h"


void handleData(String sData) {
  initMapData();
  date_now = getDateFormat();
  time_now = getTimeFormat();
  String sSaveFile = "";
  for (int i = 0; i < SIZE_MAC; i++) {
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
        te1 = pos1; 
        te2 = pos2; 
        te3 = pos3;
        //DisplayDataOnLCD(mac.substring(8, 12));
        if ((te1 >= 90 || te2 >= 90 || te3 >= 90)) {
          LevelTwoAlarm(100);
        }
        else if ((te1 >= 60 || te2 >= 60 || te3 >= 60)) {
          LevelOneAlarm(100);
        }
        mapData[mac] = {{String(pos1), String(pos2), String(pos3)}};
        sSaveFile += mapName[mac] + "," + String(pos1) + "," + String(pos2) + "," +  String(pos3) + "," + time_now + "/" + date_now + "\n";
      }
      else {
        sSaveFile += mapName[mac] + "," + String(9999) + "," + String(9999) + "," +  String(9999) + "," + time_now + "/" + date_now + "\n";
      }
    }
  }
  getHTML();
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
  for (int i = 0; i < SIZE_MAC; i++) {
    String mac = listmac[i];
    if (mac != "") {
      mapData[mac] = {{"9999", "9999", "9999"}};
    }
  }
}
