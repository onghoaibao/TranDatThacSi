#include "Header.h"

const long utcOffsetInSeconds = 7 * 3600;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);


int oldSec = 0;
String getRealTime() {
  String rs = "";
  timeClient.update();
  int newSec = (int)timeClient.getSeconds();
  if (newSec != oldSec) {
    int Min = timeClient.getMinutes();
    int Hour = timeClient.getHours();
    rs = String(Hour < 10 ? "0" + String(Hour) : Hour) + ":" + 
         String(Min < 10 ? "0" + String(Min) : Min) + ":" + 
         String(newSec < 10 ? "0" + String(newSec) : newSec);
    oldSec = newSec;
  }
  return rs;
}
