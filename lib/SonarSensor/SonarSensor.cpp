#include "SonarSensor.h"

// Biến tĩnh để lưu lại khoảng cách hợp lệ của lần đo trước đó
static int lastValidDistance = 20; 

void initSonar() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

int readDistance() {
    // Phát xung kích hoạt 10 micro giây
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Bấm giờ sóng dội về (Thêm timeout 30000 micro giây để mạch không bị treo nếu mất sóng)
    long duration = pulseIn(echoPin, HIGH, 30000);

    // Tính khoảng cách ra cm
    int distance = duration * 0.0343 / 2;

    return distance;
}