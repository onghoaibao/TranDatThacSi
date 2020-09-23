#include "Header.h"

File SDCard;
void initSDcard() {
  pinMode(CS_SDC, OUTPUT);
  if (!SD.begin(CS_SDC)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");
}

void saveData(String pos, int t1, int t2, int t3, String _time_) {
  String data = pos + "," + String(t1) + "," + String(t2) + "," + String(t3) + "," + _time_;
  if (SD.exists("data.csv")) {
    SDCard = SD.open("data.csv", FILE_WRITE);
    if (SDCard) {
      SDCard.println(data);
      SDCard.close();
      Serial.println("Writing to file successfully!");
    }
  }
  else {
    SDCard = SD.open("data.csv", FILE_WRITE);
    SDCard.println(data);
    SDCard.close();
  }
}


void printDirectory(File dir, int numTabs) {
  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
