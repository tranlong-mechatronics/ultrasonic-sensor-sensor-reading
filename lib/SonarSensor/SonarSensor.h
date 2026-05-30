#ifndef SONAR_SENSOR_H
#define SONAR_SENSOR_H

#include <Arduino.h>

// Định nghĩa chân cắm của cảm biến
const int trigPin = 27;
const int echoPin = 14;

// Khai báo các hàm sẽ sử dụng
void initSonar();
int readDistance();

#endif