#include "Header.h"

void setup() {
  Serial.begin(115200);
  Serial.println("\n------------------");
//  initSDcard();
//  initHM10();
//  initLCD();
//  initRegister();
  initServerLocal();
  delay(5000);
}
int i = 0;
void loop() {
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
  handleClientServer();
}
