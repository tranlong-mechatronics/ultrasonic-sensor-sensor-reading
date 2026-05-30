#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <secrets.h>
#include "SonarSensor.h" 

WebServer server(80);
const int ledPin = 2;

void handleRoot() {
    server.send(200, "text/plain", "Hello");
}

void setup() {
    pinMode(ledPin, OUTPUT);
    Serial.begin(115200);
    initSonar(); 

    WiFi.begin(SECRET_SSID, SECRET_PASSWORD);
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
    
    server.on("/", handleRoot);
    server.begin();
    
    
    Serial.println("Timestamp(ms),Distance(cm)");
}

void loop() {
    server.handleClient();

    int sonarDistance = readDistance();
  
    unsigned long timeStamp = millis(); 
    
    Serial.print(timeStamp);
    Serial.print(",");        
    Serial.println(sonarDistance); 
    
    delay(200);
}