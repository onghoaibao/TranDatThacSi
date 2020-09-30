#include "Header.h"

void setup() {
  Serial.begin(115200);
  Serial.println("\n------------------");
  initSDcard();
  initHM10();
  //  initLCD();
  //  initRegister();
  initFS();
  initServerLocal();
  initNTP();
  delay(5000);
}

void loop() {
  String s = iBeaconScanner();
  handleData(s);
  wait(3000);
}
