/**
 * @file data_logger.ino
 * @author Vraj Ramavat
 * @brief Multi-sensor data logging system for DHT11, LDR, and HC-SR04 sensors.
 * Submitted for Q24.
 */

#include "DHT.h"

// Pin definitions
#define DHTPIN 2
#define DHTTYPE DHT11

const int LDR_PIN = A0;
const int TRIG_PIN = 9;
const int ECHO_PIN = 8;

// Initialize DHT
DHT dht(DHTPIN, DHTTYPE);

unsigned long previousMillis = 0;
const long interval = 5000; // Log data every 5 seconds

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  Serial.begin(9600);
  Serial.println("--- Multi-Sensor Data Logger Booted ---");
  dht.begin();
}

void loop() {
  unsigned long currentMillis = millis();

  // Non-blocking log cycle
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // 1. Read DHT11
    float tempC = dht.readTemperature();
    float hum = dht.readHumidity();

    // 2. Read LDR and convert to percentage
    int ldrRaw = analogRead(LDR_PIN);
    // Standard mapping: 0 raw = Dark (0%), 1023 raw = Full light (100%)
    // Depending on pull-up/pull-down config, lower values might mean brighter.
    // Let's assume standard LDR pull-up where lower voltage (closer to GND) is bright,
    // or standard LDR pull-down where higher voltage is bright.
    // Let's map it: 0 to 1023 -> 0% to 100%
    int lightPercent = map(ldrRaw, 0, 1023, 0, 100);
    
    // Add lighting description
    const char* lightDesc;
    if (lightPercent < 30) lightDesc = "Dark";
    else if (lightPercent < 70) lightDesc = "Dim";
    else lightDesc = "Bright";

    // 3. Read HC-SR04
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH, 30000);
    int distance = (duration > 0) ? (duration * 0.034) / 2 : -1;

    // 4. Output log in required structured format
    Serial.println("=== SENSOR LOG ===");
    Serial.print("Time      : ");
    Serial.print(currentMillis);
    Serial.println(" ms");
    
    Serial.print("Temp      : ");
    if (isnan(tempC)) {
      Serial.print("ERR");
    } else {
      Serial.print(tempC, 1);
      Serial.print(" C");
    }
    Serial.print(" | Humidity: ");
    if (isnan(hum)) {
      Serial.println("ERR");
    } else {
      Serial.print(hum, 0);
      Serial.println("%");
    }

    Serial.print("Light     : ");
    Serial.print(lightPercent);
    Serial.print("% (");
    Serial.print(lightDesc);
    Serial.println(")");

    Serial.print("Distance  : ");
    if (distance == -1) {
      Serial.println("Out of Range");
    } else {
      Serial.print(distance);
      Serial.println(" cm");
    }
    Serial.println("==================");
  }
}
