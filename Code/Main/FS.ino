#include "Header.h"

#define SIZE 60
#define SIZE_SSID 30
#define SIZE_PASS 20
#define ADDRESS_SSID_WIFI 0 
#define ADDRESS_PASS_WIFI 35

boolean saveFile(String fileName, const char* content, uint16_t len) {
  SPIFFS.begin();
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
  SPIFFS.begin();
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
  SPIFFS.begin();
  File f = SPIFFS.open(String("/") + fileName, "w");
  f.close();
}

void listALlFile(String path){
  String str = "";
  Dir dir = SPIFFS.openDir("/");
  while (dir.next()) {
      str = dir.fileName();
      Serial.println("File name: " + String(str));
  }
}

void removeFile(String fileName){
  bool b = SPIFFS.remove(fileName);
  Serial.println("Remove File name " +  fileName + " -> " + String(b));
}

void writeEEPROM(String str, int _address, int _SIZE_){
  int _size = str.length();
  if(_size <= _SIZE_){
      clearEEPROM(_address, _SIZE_);   
      delay(20);
      for(int i=0; i<_size; i++){
        EEPROM.write( _address + i, str.charAt(i));
      }
      delay(20);
      EEPROM.commit();   
      return;
  }
  else{
    Serial.println("Cannot save data");
  }
}

String readEEPROM(int _address, int _size){
  EEPROM.begin(SIZE);
  delay(50);
  String _buffer = "";
  for(int i=0; i<_size; i++){
    char c = (char)EEPROM.read(_address + i);
    if(c == NULL){
       break;
    }
    _buffer += c;
  }
  Serial.println("Data of _buffer: " + _buffer + "  len: " + _buffer.length());
  return _buffer;
}

void clearEEPROM(int _address, int _size){
  EEPROM.begin(SIZE);
  for(int i=0; i<_size; i++){
    EEPROM.write(_address + i, (char)NULL);
  }
  EEPROM.commit();
  delay(50);
}


void saveSSIDWifi(String ssid){
  writeEEPROM(ssid, ADDRESS_SSID_WIFI, SIZE_SSID);
}

void savePASSWifi(String pass){
  writeEEPROM(pass, ADDRESS_PASS_WIFI, SIZE_PASS);
}

void accessWifi(String ssid, String pass){
  saveSSIDWifi(ssid);
  savePASSWifi(pass);
}

String getSSID_WIFI(){
  return readEEPROM(ADDRESS_SSID_WIFI, SIZE_SSID);
}
String getPASS_WIFI(){
  return readEEPROM(ADDRESS_PASS_WIFI, SIZE_PASS);
}
