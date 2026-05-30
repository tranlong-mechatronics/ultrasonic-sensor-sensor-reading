#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <secrets.h>
WebServer server(80); // Khởi tạo server chạy ở cổng số 80 (cổng chuẩn của giao thức HTTP)
const int ledPin = 2;
const char* ssid = SECRET_SSID;
const char* password = SECRET_PASSWORD;
const int trigPin = 27;
const int echoPin = 14;

void handleRoot() {
  // Trả về mã trạng thái 200 (Thành công), kiểu nội dung là văn bản thuần, và chữ "Hello"
  server.send(200, "text/plain", "Hello"); 
}

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  // Đã sửa thành != để máy hiểu lệnh so sánh
  while(WiFi.status() != WL_CONNECTED){ 
    Serial.println("[WIFI] Connecting...");
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }
  digitalWrite(ledPin, HIGH);
  Serial.println("[WIFI] Connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", handleRoot); // Nếu khách truy cập vào địa chỉ trang chủ "/", hãy chạy hàm handleRoot
  server.begin();             // Chính thức mở cửa Server
  Serial.println("[WIFI] Web server started!"); // Gắn tag logging chuẩn chỉnh
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop(){
  server.handleClient(); // Liên tục kiểm tra xem có thiết bị nào đang kết nối vào server không
  long duration;
  int distance;

  // Bước 1: Phát xung kích hoạt 10 micro giây
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Bước 2: Bấm giờ
  duration = pulseIn(echoPin, HIGH);

  // Bước 3: Tính khoảng cách ra cm
  distance = duration * 0.0343 / 2;

  // Tạm thời in kết quả ra Serial Monitor để kiểm tra trước
  Serial.print("Khoang cach: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(200); // Giãn cách giữa các lần đo để sóng không bị chồng chéo
}