#include "Header.h"
bool bInitAll = false;
void setup() {
  Serial.begin(115200);
  Serial.println("\n------------------");
  delay(3000);
  initNTP();
  initLCD();
  initSDcard();
  initHM10();
  initRegister();
  initFS();
  initServerLocal();
  delay(2000);
}

void loop() {
  String s = iBeaconScanner();
  handleData(s);
  wait(3000);
}
