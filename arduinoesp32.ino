// esp32_home_surveillance.ino
#include <WiFi.h>
#include <HTTPClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "YOUR_BLYNK_TOKEN";   // Replace with your Blynk token
char ssid[] = "YOUR_WIFI_SSID";     // Replace with your WiFi SSID
char pass[] = "YOUR_WIFI_PASS";     // Replace with your WiFi password

const int pirPin = 27;              // PIR sensor pin
unsigned long lastTrigger = 0;
const unsigned long debounceMs = 7000; // 7-second cooldown

const char* serverIP = "PC_IP_ADDRESS"; // Replace with your PC IPv4 address
const int serverPort = 5000;

void setup() {
  Serial.begin(115200);
  pinMode(pirPin, INPUT);
  Blynk.begin(auth, ssid, pass);
  Serial.println("ESP32 Home Surveillance Ready");
}

void loop() {
  Blynk.run();
  int motion = digitalRead(pirPin);

  if (motion == HIGH && (millis() - lastTrigger > debounceMs)) {
    lastTrigger = millis();
    Serial.println("Motion detected!");
    Blynk.notify("🚨 Motion detected! Capturing image...");
    triggerCamera();
  }
}

void triggerCamera() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String("http://") + serverIP + ":" + serverPort + "/capture";
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode > 0) {
      Serial.printf("HTTP Response code: %d\n", httpCode);
      Serial.println(http.getString());
    } else {
      Serial.println("HTTP request failed");
    }
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}
