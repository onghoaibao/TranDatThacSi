#include "Header.h"

const long utcOffsetInSeconds = 7 * 3600;

String weekDays[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
String months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
// Set offset time in seconds to adjust for your timezone, for example:
// GMT +1 = 3600
// GMT +8 = 28800
// GMT -1 = -3600
// GMT 0 = 0

int oldSecond = 0;
String oldDateTime = "";
void initNTP() {
  timeClient.begin();
  timeClient.setTimeOffset(utcOffsetInSeconds);
}

String getTimeFormat() {
  timeClient.update();
  unsigned long epochTime = timeClient.getEpochTime();
  String formattedTime = timeClient.getFormattedTime();
  int currentHour = timeClient.getHours();
  int currentMinute = timeClient.getMinutes();
  int currentSecond = timeClient.getSeconds();
  String weekDay = weekDays[timeClient.getDay()];

  String currentTime = String(currentHour < 10 ? (String(0) + currentHour) : currentHour) + ":" +
                       String(currentMinute < 10 ? (String(0) + currentMinute) : currentMinute) + ":" + 
                       String(currentSecond < 10 ? (String(0) + currentSecond) : currentSecond);
  Serial.println("Current time: " + currentTime);
  Serial.println("");
  return  currentTime;
}

String getDateFormat() {
  timeClient.update();
  unsigned long epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime ((time_t *)&epochTime);
  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon + 1;
  String currentMonthName = months[currentMonth - 1];
  int currentYear = ptm->tm_year + 1900;
  String currentDate = String(monthDay < 10 ? String(0) + monthDay : monthDay) + "-" + String(currentMonth < 10 ? String(0) + currentMonth : currentMonth) + "-" + String(currentYear);
  Serial.println("Current date: " + currentDate);
  return currentDate;
}


void wait(int t) {
  long i = 0;
  while (i < t) {
    delay(1);
    handleClientServer();
    i++;
  }
}
