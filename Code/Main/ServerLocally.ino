#include "Header.h"
ESP8266WebServer sv(9090);

const char* NAME_WIFI_ESP8266 = "Temperature";
const char* PASS_WIFI_ESP8266  = "123456789";

String ssid =  " BoBa2_4GHz";
String pass =  "Thang06@";
String sHTML = "";
int j, k;

void handleClientServer() {
  sv.handleClient();
}

void initServerLocal() {
  ssid =  getSSID_WIFI();
  pass =  getPASS_WIFI();
  sHTML = getStringFile("tabledata.html");
  //  sTable.replace("[DATE]", date_now);
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(NAME_WIFI_ESP8266, PASS_WIFI_ESP8266);
  WiFi.begin(ssid, pass);
  int timeout = 0;
  while (WiFi.status() != WL_CONNECTED) {
    if (timeout == 40) {
      Serial.print("\nCannot Connect to BoBa2_4GHz Wifi\n");
      break;
    }
    delay(500);
    Serial.print(".");
    timeout++;
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  sv.on("/trainsfile", HTTP_ANY, [] {
    //Serial.println(String("Accept: ") + ++count);
    sv.send(200, "text/html",
    "<meta charset='utf-8'>"
    "<html>"
    "<head>"
    "<title>Truyen File Den ESP8266</title>"
    "</head>"
    "<body>"
    "<form method='POST' action='/trainsfile' enctype='multipart/form-data'>"
    "<h2>Config File setupWifi.html</h2>"
    "<input type='file' name='SelectFile'>"
    "<input type='submit' name='SubmitFile' value='Send File'>"
    "</form>"
    "<form method='POST' action='/trainsfile' enctype='multipart/form-data'>"
    "<h2>Config File tabledata.html</h2>"
    "<input type='file' name='SelectFile'>"
    "<input type='submit' name='SubmitFile' value='Send File'>"
    "</form>"
    "</body>"
    "</html");
  }, [] {
    HTTPUpload& file = sv.upload();
    if (file.status == UPLOAD_FILE_START) {
      Serial.println("Start File: " + file.filename);
      removeContentFile(file.filename);
    }
    else if (file.status == UPLOAD_FILE_WRITE) {
      Serial.println("File dang ghi: " + file.filename);
      saveFile(file.filename, (const char*)file.buf, file.currentSize);
    }
    else if (file.status == UPLOAD_FILE_END) {
      Serial.println("File da ghi thanh cong");
    }
  });

  sv.on("/setupWifi", [] {
    String sBetween =  scanWifi();
    String sSetup = getStringFile("setupWifi.html");
    sSetup.replace("[###]", sBetween);
    sv.send(200, "text/html", sSetup);
  });

  sv.on("/setmac", HTTP_ANY, [] {
    //Serial.println(String("Accept: ") + ++count);
    sv.send(200, "text/html",
    "<meta charset='utf-8'>"
    "<html>"
    "<head>"
    "<title>Configuration Mac Address</title>"
    "</head>"
    "<body>"
    "<form method='POST' action='/setmac' enctype='multipart/form-data'>"
    "<h2>Configuration Mac Address (setmac.txt)</h2>"
    "<input type='file' name='SelectFile'>"
    "<input type='submit' name='SubmitFile' value='Send File'>"
    "</form>"
    "</body>"
    "</html");
  }, [] {
    HTTPUpload& file = sv.upload();
    if (file.status == UPLOAD_FILE_START) {
      Serial.println("Start File: " + file.filename);
      bool b = isExistFile(String(file.filename));
      if (b) {
        removeContentFile(file.filename);
      }
    }
    else if (file.status == UPLOAD_FILE_WRITE) {
      Serial.println("File dang ghi: " + file.filename);
      saveFile(file.filename, (const char*)file.buf, file.currentSize);
    }
    else if (file.status == UPLOAD_FILE_END) {
      Serial.println("File da ghi xong\n-------------\n" + getStringFile("configHTTP.txt"));
    }
  });

  sv.on("/tabledata", [] {
    String sT = sHTML;
    sT.replace("[DATE]", date_now);
    sT += sTable;
    sT += String("\n</table></body></html>");
    sv.send(200, "text/html", sT);
  });

  sv.on("/connectWifi", [] {
    String ssid = String(sv.arg("wifi"));
    String pass = String(sv.arg("pass"));
    accessWifi(ssid, pass);
    Serial.println(String("Wifi: ") + ssid + " len: " + String(ssid.length()));
    Serial.println(String("Pass: ") + pass + " len: " + String(pass.length()));
    getSSID_WIFI();
    getPASS_WIFI();
    sv.send(200, "text/html", "<h1>Wifi Is Connecting</h1>");
  });
  //start server
  sv.begin();
}

String getHTML() {
  String data = "";
  sTable = "";
  int mspSize = mapData.size();
  int y = 0;
  int icounter = 0;
  for (int i = 0; i < mspSize; i++) {
    int t1 = mapData[listmac[i]][0].toInt();
    int t2 = mapData[listmac[i]][1].toInt();
    int t3 = mapData[listmac[i]][2].toInt();
    if (i == 0) {
      nLine = nLine + mspSize;
      String stt = String("<tr>");
      String sn = String("<th>") + String(mapName[listmac[i]]) + String("</th>");
      String s1 = String(90 <= t1 ? "<th style=\"background-color:#FF0000;\">" : (60 <= t1 ? "<th style=\"background-color:#ffcc00;\">" : "<th style=\"background-color:#00cc00;\">")) + String(t1) + String("</th>");
      String s2 = String(90 <= t2 ? "<th style=\"background-color:#FF0000;\">" : (60 <= t2 ? "<th style=\"background-color:#ffcc00;\">" : "<th style=\"background-color:#00cc00;\">")) + String(t2) + String("</th>");
      String s3 = String(90 <= t3 ? "<th style=\"background-color:#FF0000;\">" : (60 <= t3 ? "<th style=\"background-color:#ffcc00;\">" : "<th style=\"background-color:#00cc00;\">")) + String(t3) + String("</th>");
      String sr = String("<th rowspan=\"") + String(mspSize) + String("\">") + String(time_now) + String("</th>") + String("</tr>");
      data = data + stt + sn + s1 + s2 + s3 + sr + String("\n");
      icounter++;
    }
    else {
      y++;
      String stt = String("<tr>");
      String sn = String("<th>") + String(mapName[listmac[i]]) + String("</th>");
      String s1 = String(90 <= t1 ? "<th style=\"background-color:#FF0000;\">" : (60 <= t1 ? "<th style=\"background-color:#ffcc00;\">" : "<th style=\"background-color:#00cc00;\">")) + String(t1) + String("</th>");
      String s2 = String(90 <= t2 ? "<th style=\"background-color:#FF0000;\">" : (60 <= t2 ? "<th style=\"background-color:#ffcc00;\">" : "<th style=\"background-color:#00cc00;\">")) + String(t2) + String("</th>");
      String s3 = String(90 <= t3 ? "<th style=\"background-color:#FF0000;\">" : (60 <= t3 ? "<th style=\"background-color:#ffcc00;\">" : "<th style=\"background-color:#00cc00;\">")) + String(t3) + String("</th>");
      data = data + stt + sn + s1 + s2 + s3 + String("</tr>") + String("\n");
      icounter++;
      if (icounter == mspSize) {
        sTable += data;
        Serial.println("Size tabledata.html: " + String(sTable.length()) + String("  j=") + String(j));
        data = "";
      }
    }
  }
  return "";
}

String scanWifi() {
  String sBetween = "";
  int num = WiFi.scanNetworks();
  for (int i = 0; i < num; i++) {
    String sSSID = WiFi.SSID(i).c_str();
    sBetween += String("<option value='") + sSSID + String("'>") + sSSID + String("</option>") + "\n";
  }
  return sBetween;
}
