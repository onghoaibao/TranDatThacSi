
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

String rx_data[3] = {};
String listmac[10] = {};

// Main function
void setupFunction();
long convertHexToDec(String sdt);

// Server Function
void initServerLocal();
void handleClientServer();

// LCD Function
void initLCD();
void showLCD();

// SD-Card Function
void initSDcard();
void saveData(int t1, int t2, int t3, String _time_);
void printDirectory(File dir, int numTabs);

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

// NTPC function
String getRealTime();

// FS Function
void initFS();
boolean saveFile(String fileName, const char* content, uint16_t len);
String getStringFile(String fileName);
void removeContentFile(String fileName);
String listAllFile();
bool isExistFile(String filename);
void getAllMacByFile();

// Map Data
typedef std::array<String, 3> RelArr;
typedef std::map<String, RelArr> MapiBeacon;

MapiBeacon mapData;

#endif
