#include "Header.h"
ESP8266WebServer sv(9090);

const char* NAME_WIFI_ESP8266 = "Temperature";
const char* PASS_WIFI_ESP8266  = "123456789";

String ssid =  " BoBa2_4GHz";
String pass =  "Thang06@";

void handleClientServer() {
  sv.handleClient();
}

void initServerLocal() {
  ssid =  getSSID_WIFI();
  pass =  getPASS_WIFI();
  sTable = getStringFile("tabledata.html");
  sTable.replace("[DATE]", date_now);
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
    CouterTime++;
    Serial.println("Size now: " + String(CouterTime));
    sTable = getStringFile("tabledata.html");
    sTable.replace("[DATE]", date_now);
    String data  = "";
    int mspSize = mapData.size();
    for (int i = 0; i < mspSize; i++) {
      if (i == 0) {
        data += String("<tr>") +
        String("<th>") + String(mapName[listmac[i]]) + String("</th>") +
        String("<th>") + String(mapData[listmac[i]][0]) + String("</th>") +
        String("<th>") + String(mapData[listmac[i]][1]) + String("</th>") +
        String("<th>") + String(mapData[listmac[i]][2]) + String("</th>") +
        String("<th rowspan=\"") + String(mspSize) + String("\">") + String(time_now) + String("</th>") + String("</tr>");
      }
      else {
        data += String("<tr>") +
                String("<th>") + String(mapName[listmac[i]]) + String("</th>") +
                String("<th>") + String(mapData[listmac[i]][0]) + String("</th>") +
                String("<th>") + String(mapData[listmac[i]][1]) + String("</th>") +
                String("<th>") + String(mapData[listmac[i]][2]) + String("</th>") + String("</tr>");
      }
    }
    sTable += data + "</table></body></html>";
    Serial.println("Size tabledata.html: " + String(sTable.length()));
    sTable = sTable.length() > 20000 ? "" : sTable;
    sv.send(200, "text/html", sTable);
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

String scanWifi() {
  String sBetween = "";
  int num = WiFi.scanNetworks();
  for (int i = 0; i < num; i++) {
    String sSSID = WiFi.SSID(i).c_str();
    sBetween += String("<option value='") + sSSID + String("'>") + sSSID + String("</option>") + "\n";
  }
  return sBetween;
}

//
//  sv.on("/login", [] {
//    sv.send(200, "text/html", getStringFile("login.html"));
//  });
//
//  sv.on("/configHTTP", HTTP_ANY, [] {
//    //Serial.println(String("Accept: ") + ++count);
//    sv.send(200, "text/html",
//    "<meta charset='utf-8'>"
//    "<html>"
//    "<head>"
//    "<title>Configuration HTTP For ESP8266</title>"
//    "</head>"
//    "<body>"
//    "<form method='POST' action='/configHTTP' enctype='multipart/form-data'>"
//    "<h2>Configuration HTTP For ESP8266 (ConfigHTTP.txt)</h2>"
//    "<input type='file' name='SelectFile'>"
//    "<input type='submit' name='SubmitFile' value='Send File'>"
//    "</form>"
//    "</body>"
//    "</html");
//  }, [] {
//    HTTPUpload& file = sv.upload();
//    if (file.status == UPLOAD_FILE_START) {
//      Serial.println("Start File: " + file.filename);
//      removeContentFile(file.filename);
//    }
//    else if (file.status == UPLOAD_FILE_WRITE) {
//      Serial.println("File dang ghi: " + file.filename);
//      saveFile(file.filename, (const char*)file.buf, file.currentSize);
//    }
//    else if (file.status == UPLOAD_FILE_END) {
//      Serial.println("File da ghi xong\n-------------\n" + getStringFile("configHTTP.txt"));
//    }
//  });
//
//  sv.on("/setupWifi", [] {
//    String sTemp = sv.arg("bLogin");
//    Serial.println(String("bLo: ") + sTemp);
//    if (bLogin != "1") {
//      bLogin = sTemp;
//    }
//    delay(100);
//    if (bLogin == "1") {
//      //      String sBetween =  scanWifi();
//      String sSetup = getStringFile("setupWifi.html");
//      //      sSetup.replace("[###]", sBetween);
//      sv.send(200, "text/html", sSetup);
//    }
//    else{
//      sv.send(200, "text/html", "<h1>Permission denied</h1>");
//    }
//  });
//
//  sv.on("/transFile", HTTP_ANY, [] {
//    //Serial.println(String("Accept: ") + ++count);
//    sv.send(200, "text/html",
//    "<meta charset='utf-8'>"
//    "<html>"
//    "<head>"
//    "<title>Truyen File Den ESP8266</title>"
//    "</head>"
//    "<body>"
//    "<form method='POST' action='/transFile' enctype='multipart/form-data'>"
//    "<h2>Config File login.html</h2>"
//    "<input type='file' name='SelectFile'>"
//    "<input type='submit' name='SubmitFile' value='Send File'>"
//    "</form>"
//    "<form method='POST' action='/transFile' enctype='multipart/form-data'>"
//    "<h2>Config File setupWifi.html</h2>"
//    "<input type='file' name='SelectFile'>"
//    "<input type='submit' name='SubmitFile' value='Send File'>"
//    "</form>"
//    "</body>"
//    "</html");
//  }, [] {
//    HTTPUpload& file = sv.upload();
//    if (file.status == UPLOAD_FILE_START) {
//      Serial.println("Start File: " + file.filename);
//      removeContentFile(file.filename);
//    }
//    else if (file.status == UPLOAD_FILE_WRITE) {
//      Serial.println("File dang ghi: " + file.filename);
//      saveFile(file.filename, (const char*)file.buf, file.currentSize);
//    }
//  });
//  sv.begin();
//}
//
//void handleClientServer() {
//  sv.handleClient();
//}
//
//int t = 5;
//void client_Sendata(String maThietbi, String pos) {
//  WiFiClientSecure client;
//  client.setInsecure();
//  if (!client.connect(__host__, __httpsPort__))
//  {
//    Serial.println("connection failed");
//    client.setInsecure();
//    return;
//  }
//  String url = "/macros/s/AKfycbxsMad8bqrkqXUkajFobCX3C9-BXrgkPXDoE1QJqN3tprFn7SIo/exec?maThietBi=" + maThietbi + "&vitri=" + pos + String(t);
//  t+4;
//  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
//               "Host: " + __host__ + "\r\n" +
//               "Connection: close\r\n\r\n");
//  Serial.print("Requesting URL: ");
//  Serial.println(url);
//  delay(500);
//  String section = "header";
//  while (client.available())
//  {
//    String line = client.readStringUntil('\r');
//    Serial.print(line);
//  }
//  Serial.println();
//  Serial.println("closing connection");
//}
//
//String getStatusMaThietBi(String maThietbi) {
//  WiFiClientSecure client;
//  client.setInsecure();
//  if (!client.connect(__host__, __httpsPort__))
//  {
//    Serial.println("connection failed");
//    client.setInsecure();
//    return "connection failed";
//  }
//  String url = "/macros/s/AKfycbxsMad8bqrkqXUkajFobCX3C9-BXrgkPXDoE1QJqN3tprFn7SIo/exec?maThietBi=" + maThietbi;
//
//  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
//               "Host: " + __host__ + "\r\n" +
//               "Connection: close\r\n\r\n");
//  Serial.print("Requesting URL: ");
//  Serial.println(url);
//  delay(500);
//  String section = "header";
//  String sOut = "";
//  long t = 0;
//  while (client.available()){
//    sOut = client.readStringUntil('\r');
//    Serial.print(sOut);
//    t++;
//    delay(1);
//    if (t >= 2000) {
//      break;
//    }
//  }
//  Serial.println();
//  Serial.println("closing connection");
//  return sOut;
//}
