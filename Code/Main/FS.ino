#include "Header.h"

#define SIZE 60
#define SIZE_SSID 30
#define SIZE_PASS 20
#define ADDRESS_SSID_WIFI 0
#define ADDRESS_PASS_WIFI 35

void initFS() {
  SPIFFS.begin();
  //removeFile("/table.html");
  //listAllFile();
  getAllMacByFile();
  contentMac = getStringFile("setmac.txt");
  setNameByMac();
  for (int i = 0; i < 10; i++) {
    Serial.println("Mac: " + listmac[i] + "  len: " + String(listmac[i].length()));
  }
}

boolean saveFile(String fileName, const char* content, uint16_t len) {
  File f = SPIFFS.open(String("/") + fileName, "a");
  if (!f) {
    f.close();
    return false;
  }
  else {
    f.write(content, len);
  }
  f.close();
  return true;
}

String getStringFile(String fileName) {
  File f = SPIFFS.open(String("/") + fileName, "r");
  if (!f) {
    f.close();
    return "";
  }
  String ret = f.readString();
  f.close();
  return ret;
}

void removeContentFile(String fileName) {
  File f = SPIFFS.open(String("/") + fileName, "w");
  f.close();
}

String listAllFile() {
  String str = "";
  Dir dir = SPIFFS.openDir("/");
  while (dir.next()) {
    str += dir.fileName() + " ";
    Serial.println("File name: " + String(dir.fileName()));
  }
  return str;
}

void getAllMacByFile() {
  String str = getStringFile("setmac.txt");
  int i = 0;
  int newix = str.indexOf(":", i);
  int oldix = 0;
  while (newix != -1 && i < 10) {
    newix = str.indexOf(":", oldix + 1);
    if (newix != -1) {
      if (i == 0) {
        listmac[i] = str.substring(oldix, newix);
        i++;
      }
      else {
        listmac[i] = str.substring(newix - 12, newix);
        i++;
      }
    }
    oldix = newix;
  }
}

void setNameByMac() {
  String ives = contentMac;
  int idStart = 0;
  int idStop  = 0;
  for (int i = 0; i < 10; i++) {
    idStart = ives.indexOf(":", idStart + 1);
    idStop  = ives.indexOf("\n", idStop + 1);
    if (idStart != -1 && idStop != -1) {
      String rs = ives.substring(idStart + 1, idStop - 1);
      mapName[listmac[i]] = rs;
    }
  }
}

bool isExistFile(String filename) {
  String str = listAllFile();
  return (str.indexOf(filename) != -1) ? true : false;
}

void removeFile(String fileName) {
  String s = listAllFile();
  if (s.indexOf(fileName) != -1) {
    bool b = SPIFFS.remove(fileName);
    Serial.println("Remove File name " +  fileName + " -> " + String(b));
  }
  else {
    Serial.println("File not exist");
  }
}

void writeEEPROM(String str, int _address, int _SIZE_) {
  int _size = str.length();
  if (_size <= _SIZE_) {
    clearEEPROM(_address, _SIZE_);
    delay(20);
    for (int i = 0; i < _size; i++) {
      EEPROM.write( _address + i, str.charAt(i));
    }
    delay(20);
    EEPROM.commit();
    return;
  }
  else {
    Serial.println("Cannot save data");
  }
}

String readEEPROM(int _address, int _size) {
  EEPROM.begin(SIZE);
  delay(50);
  String _buffer = "";
  for (int i = 0; i < _size; i++) {
    char c = (char)EEPROM.read(_address + i);
    if (c == NULL) {
      break;
    }
    _buffer += c;
  }
  Serial.println("Data of _buffer: " + _buffer + "  len: " + _buffer.length());
  return _buffer;
}

void clearEEPROM(int _address, int _size) {
  EEPROM.begin(SIZE);
  for (int i = 0; i < _size; i++) {
    EEPROM.write(_address + i, (char)NULL);
  }
  EEPROM.commit();
  delay(50);
}


void saveSSIDWifi(String ssid) {
  writeEEPROM(ssid, ADDRESS_SSID_WIFI, SIZE_SSID);
}

void savePASSWifi(String pass) {
  writeEEPROM(pass, ADDRESS_PASS_WIFI, SIZE_PASS);
}

void accessWifi(String ssid, String pass) {
  saveSSIDWifi(ssid);
  savePASSWifi(pass);
}

String getSSID_WIFI() {
  return readEEPROM(ADDRESS_SSID_WIFI, SIZE_SSID);
}
String getPASS_WIFI() {
  return readEEPROM(ADDRESS_PASS_WIFI, SIZE_PASS);
}
