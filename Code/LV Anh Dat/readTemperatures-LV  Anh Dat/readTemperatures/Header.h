#ifndef __HEADER__
#define __HEADER__
#include <Arduino.h>
#include <Wire.h> 
#include "MLX90621.h" 
#include <Servo.h> 
#include <SoftwareSerial.h>


MLX90621 sensor; 
Servo myservo;
int16_t Pixel_Z;

// Init BLE103
String IBEACON_COMMAND = "AT+IBEACON=B9407F30F5F8466EAFF925556B57FE18,";
void initBLE103();
void setCommandBLE(String cmd, int t);
void modeBLE103();
void setDataToiBeacon(int tmp1, int tmp2, int tmp3);
String getResBLE103(int t);
#endif
