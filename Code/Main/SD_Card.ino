#include "Header.h"

File SDCard;
void initSDcard() {
  pinMode(CS_SDC, OUTPUT);
  if (!SD.begin(CS_SDC)) {
    Serial.println("Card failed, or not present");
    return;
  }
  saveData("Ten Thiet Bi", "Vi Tri 1", "Vi Tri 2", "Vi Tri 3", "Ngay/Gio\n");
  Serial.println("card initialized.");
}

void saveDataToFile(String sData) {
  SDCard = SD.open("data.csv", FILE_WRITE);
  if (SDCard) {
    SDCard.print(sData);
    SDCard.close();
    Serial.println("Writing to file successfully!");
  }
  SDCard = SD.open("/");
  printDirectory(SDCard);
}

void saveData(String pos, String t1, String t2, String t3, String _time_) {
  String data = pos + "," + t1 + "," + t2 + "," + t3 + "," + _time_;
  if (SD.exists("data.csv")) {
    SDCard = SD.open("data.csv", FILE_WRITE);
    if (SDCard) {
      SDCard.print(data);
      SDCard.close();
      Serial.println("Writing to file successfully!");
    }
  }
  else {
    SDCard = SD.open("data.csv", FILE_WRITE);
    SDCard.println(data);
    SDCard.close();
    Serial.println("Writting Header text to file successfully!");
  }
}

void printDirectory(File dir) {
  while (true) {
    File entry =  SDCard.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    Serial.print("File Name: ");
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry);
    } else {
      Serial.print("  Size: ");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
