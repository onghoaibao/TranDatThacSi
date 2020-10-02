
#ifndef __HEADER__
#define __HEADER__

#include "Arduino.h"
#include "Pins.h"
#include "SD.h"
#include "SPI.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include "SoftwareSerial.h"
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <map>
#include <LiquidCrystal_I2C.h>

String ip;
int te1, te2, te3 = 0;

const int SIZE_MAC = 6;
String rx_data[3] = {};
String listmac[SIZE_MAC] = {};

// Main function
int CouterTime = 0;
String sTable = "";
int nLine = 0;
void setupFunction();
long convertHexToDec(String sdt);
void wait(int t);

// Server Function
void initServerLocal();
void handleClientServer();
String getHTML();

// LCD Function
void initLCD();
void showLCD(String dt, int row);
void DisplayDataOnLCD(String t1, String t2, String t3, String t11, String t22, String t33, String dat, String tim, String ip);
void showDateIP(String dt);
void displayLCD(String s, int row, int col);

// SD-Card Function
void initSDcard();
void saveData(String pos, String t1, String t2, String t3, String _time_, bool st);
void saveDataToFile(String sData);
void printDirectory(File dir);

// Bluetooth-HM10 Function
void initHM10();
String readDataiBeacon();
String iBeaconScanner();
void clearBuffer();

// 74HC595 function
void initRegister();
void Bit1();
void Bit0();
void Latch();
void WriteByte(byte data);
void LevelOneAlarm(int t);
void LevelTwoAlarm(int t);
void ConnectWifiAlarm();
void turnOffArlam();


// NTPC function
String time_now;
String date_now;
String getRealTime();
void initNTP();
String getTimeFormat();
String getDateFormat();

// FS Function
String contentMac;
void initFS();
boolean saveFile(String fileName, const char* content, uint16_t len);
String getStringFile(String fileName);
void removeContentFile(String fileName);
String listAllFile();
bool isExistFile(String filename);
void getAllMacByFile();
void setNameByMac();
void getListMac();

// Map Data
typedef std::array<String, 3> RelArr;
typedef std::map<String, RelArr> MapiBeacon;
typedef std::map<String, String> MapName;
MapiBeacon mapData;
MapName mapName;

//Other function
void handleData(String sData);
long convertHexToDec(String sdt);
void initMapData();

byte degree[8] = {
  0B01110,
  0B01010,
  0B01110,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000
};
#endif
