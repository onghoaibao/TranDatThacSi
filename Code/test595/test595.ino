const byte pin = D0;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT);
  digitalWrite(pin, 1);
  delay(500);
  WriteByte(0x7F);
 // WriteByte(0xDF);   // Cam + coi ON
//  WriteByte(0xBF);   // Do + Coi ON
//  WriteByte(0x7F);   // Coi + Do + Cam = OFF
  delay(500);
  ConnectWifi();
}

void ConnectWifi() {
  WriteByte(0x9F);
  delay(200);
  WriteByte(0x7F);
  delay(200);
  WriteByte(0x9F);
  delay(200);
  WriteByte(0x7F);
  delay(200);
}
void loop() {
  // put your main code here, to run repeatedly:

  // 2led
  
//  for (int i = 0; i < 10; i++) {
//    WriteByte(0x7F);
//    delay(250);
//    WriteByte(0x9F); // CAM and Do and Coi
//    delay(250);
//  }
  
//  WriteByte(0x00);
//  delay(5000);

  //coi + led cam
//  for (int i = 0; i < 10; i++) {
//    WriteByte(0x20);
//    //turnOffLed();
//    delay(250);
//    WriteByte(0x70);
//    delay(250);
//  }
//
//  //coi + led do
//  for (int i = 0; i < 10; i++) {
//    WriteByte(0x10);
//    //turnOffLed();
//    delay(250);
//    WriteByte(0x70);
//    delay(250);
//  }

  //  for (int i = 0; i < 10; i++) {
  //    WriteByte(0x00);
  //    delay(500);
  //    WriteByte(0xB0);
  //    delay(500);
  //  }
  //
  //  for (int i = 0; i < 10; i++) {
  //    WriteByte(0x00);
  //    delay(1000);
  //    WriteByte(0xF0);
  //    delay(1000);
  //  }
  //
  //  for (int i = 0; i < 10; i++) {
  //    WriteByte(0x00);
  //    delay(250);
  //    WriteByte(0xD0);
  //    delay(250);
  //  }
  //
  //  for (int i = 0; i < 10; i++) {
  //    WriteByte(0x00);
  //    delay(250);
  //    WriteByte(0xB0);
  //    delay(250);
  //  }
}


void turnOffLed() {
  digitalWrite(pin, 1);
}

void Bit1() {
  digitalWrite(pin, 0);
  delayMicroseconds(1);
  digitalWrite(pin, 1);
  delayMicroseconds(15);
}

void Bit0() {
  digitalWrite(pin, 0);
  delayMicroseconds(15);
  digitalWrite(pin, 1);
  delayMicroseconds(30);
}

void lacth() {
  digitalWrite(pin, 0)  ;
  delayMicroseconds(200);
  digitalWrite(pin, 1);
  delayMicroseconds(300);
}


void WriteByte(byte data) {
  byte temp = data;
  for (int i = 0; i < 8; i++) {
    //int t = temp << i;
    if (data & (1 << i)) {
      Bit1();
    }
    else {
      Bit0();
    }
  }
  lacth();
}
