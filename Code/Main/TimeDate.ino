#include "Header.h"

const long utcOffsetInSeconds = 7 * 3600;

String weekDays[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
String months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

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
  //Serial.println("Current time: " + currentTime);
  //Serial.println("");
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
  //Serial.println("Current date: " + currentDate);
  return currentDate;
}


void wait(int t) {
  long i = 0;
  long k=0;
  while (i < t) {
    delay(1);
    handleClientServer(); 
    if ((te1 >= 90 || te2 >= 90 || te3 >= 90) && k == 500) {
      LevelTwoAlarm(100);
      k = 0;
    }
    else if ((te1 >= 60 || te2 >= 60 || te3 >= 60) && k == 500) {
      LevelOneAlarm(100);
      k = 0;
    }
    i++;
    k++;
  }
  String dt = date_now + String("  ") + time_now;
  displayLCD(String(" ") + dt.substring(0, dt.length() - 3), 0, 0);
}
