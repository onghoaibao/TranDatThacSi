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

  sv.on("/tabledata", [] {
    String sTable = getStringFile("tabledata.html");
    Serial.println(sTable);
    String data  = "";

  //test table
  for(int i=12; i<30; i++){
    data += String("<tr>") + 
                  String("<th>") + String(i) + String("</th>") + 
                  String("<th>") + String(i) + String("</th>") + 
                  String("<th>") + String(i) + String("</th>") + 
                  String("<th>") + String(i) + String("</th>") + 
                  String("<th>") + String(i) + String("</th>") + 
                  String("<th>") + String(i) + String("</th>") + 
                  String("<th>") + String("20:20:") + String(i) + String("</th>") + 
                  String("</tr>");
  }                  
//getDataFromH10();
    sTable += data + "</table></body></html>";

    sv.send(200, "text/html", sTable);
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
