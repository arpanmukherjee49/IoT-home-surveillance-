// Wokwi-ready ESP32 PIR Motion Detection with LED + Buzzer
#define PIR_PIN 27       // PIR OUT pin
#define LED_PIN 26       // LED pin
#define BUZZER_PIN 25    // Buzzer pin

// Debounce / cooldown
unsigned long lastTrigger = 0;
const unsigned long debounceMs = 3000; // 3 seconds cooldown
int pirState = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.println("System ready... Waiting for motion.");
}

void loop() {
  int val = digitalRead(PIR_PIN);

  if (val == HIGH && (millis() - lastTrigger > debounceMs)) {
    pirState = HIGH;
    lastTrigger = millis();

    Serial.println("⚠️ Motion detected!");

    digitalWrite(LED_PIN, HIGH);       // Turn on LED
    tone(BUZZER_PIN, 2000, 500);       // Buzzer beep (500ms)

    delay(1000);                       // Alert duration
    digitalWrite(LED_PIN, LOW);        // Turn off LED
  }
  else {
    pirState = LOW;
  }

  delay(50); // small delay for stability
}
