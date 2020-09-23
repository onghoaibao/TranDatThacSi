const byte pin = D0;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT);
  digitalWrite(pin, 1);
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
    writeByte(0x00);
    delay(500);
    writeByte(0xff);
    delay(500);
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


void writeByte(byte data) {
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
