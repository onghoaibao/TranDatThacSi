#include "Header.h"

int temp1, temp2, temp3;

void _timdiemnhiet() {
  myservo.write(90);
  analogWrite(6, 50);
  for (int i = 0; i <= 63; i++) {
    sensor.measure(true); // lấy giá trị mới từ cảm biến
    Pixel_Z = sensor.getTemperature(i); // gán giá trị vào biến Pixel_Z
    //int16_t Pixel_1= sensor.getTemperature(24);
    //int16_t Pixel_2= sensor.getTemperature(25);
    //int16_t Pixel_3= sensor.getTemperature(41);
    //int16_t Pixel_4= sensor.getTemperature(42);
    //int16_t Pixel_Z = (Pixel_1 + Pixel_2 + Pixel_3 + Pixel_4)/4;
    if (Pixel_Z >= 50){
      Serial.print("Pixel Temp ");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(Pixel_Z);
      //delay(1000);
    }
    delay(10);
  }
}

void _1diemnhiet(int pixel) {
  myservo.write(90);
  analogWrite(6, 100);
  sensor.measure(true); //get new readings from the sensor
  int16_t Pixel_Z = sensor.getTemperature(pixel);
  Serial.print("Nhiet Do Pixel ");
  //Serial.print(i);
  Serial.print(": ");
  Serial.println(Pixel_Z);
  delay(1000);
}

void _3diemnhietdo() {
  // ----- Quay từ trái sang phải -----//
  for (int i = 60; i <= 120; i++){
    myservo.write(i);
    delay(100);
    // ----- Điểm 1 -----//
    if (i == 60){
      analogWrite(6, 10);
      sensor.measure(true); //get new readings from the sensor
      temp1 = sensor.getTemperature(24);
      Serial.print("Nhiet Do diem 1: ");
      Serial.println(temp1);
      delay(500);
    }
    else{
      analogWrite(6, 0);
    }
    // ----- Điểm 2 -----//
    if (i == 90){
      analogWrite(6, 10);
      sensor.measure(true);
      temp2 = sensor.getTemperature(24);
      Serial.print("Nhiet Do diem 2: ");
      Serial.println(temp2);
      delay(500);
    }
    else
    {
      analogWrite(6, 0);
    }
  }

  for (int i = 120; i >= 60; i--) {
    myservo.write(i);
    delay(100);
    // ----- Điểm 3 -----//
    if (i == 120) {
      analogWrite(6, 10);
      sensor.measure(true);
      temp3 = sensor.getTemperature(24);
      Serial.print("Nhiet Do diem 3: ");
      Serial.println(temp3);
      delay(500);
    }
    else {
      analogWrite(6, 0);
    }

    // ----- Điểm 2 -----//
    if (i == 90) {
      analogWrite(6, 10);
      sensor.measure(true);
      int16_t Pixel_Z = sensor.getTemperature(24);
      Serial.print("Nhiet Do diem 2: ");
      Serial.println(Pixel_Z);
      delay(500);
    }
    else
    {
      analogWrite(6, 0);
    }
  }
}
void setup() {
  Serial.begin(9600);
  initBLE103();
  sensor.initialise (4);

  myservo.attach(8);    // Motor Servo

  pinMode(6, OUTPUT);   // Lazer
  pinMode(13, OUTPUT);  // Alarm LED
  digitalWrite(6, LOW);
  digitalWrite(10, LOW);

  myservo.write(60);    // khởi tạo vị trí ban đầu của servo.
  delay(5000);
}

void loop() {
  _3diemnhietdo();
  setDataToiBeacon(temp1, temp2, temp3);
}
