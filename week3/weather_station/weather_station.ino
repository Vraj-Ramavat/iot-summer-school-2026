/**
 * @file weather_station.ino
 * @author Vraj Ramavat
 * @brief Environmental monitoring station using DHT11/DHT22.
 * Submitted for Q21.
 */

#include "DHT.h"

// Pin definitions
#define DHTPIN 2
#define DHTTYPE DHT11 // Change to DHT22 if using DHT22

const int RED_LED = 11;
const int GREEN_LED = 10;

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

unsigned long previousMillis = 0;
const long interval = 2000; // Read every 2 seconds

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("--- DHT Weather Station Initialized ---");
  Serial.println("Format: timestamp_ms,temp_C,temp_F,humidity");
  
  dht.begin();
}

void loop() {
  unsigned long currentMillis = millis();

  // Read sensor non-blocking every 2 seconds
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Read humidity and temperature
    float h = dht.readHumidity();
    float t = dht.readTemperature(); // Celsius
    
    // Check if any reads failed
    if (isnan(h) || isnan(t)) {
      Serial.println("[ERROR] Failed to read from DHT sensor!");
      
      // Flash Red LED to show sensor error
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);
      return;
    }

    // Convert Celsius to Fahrenheit
    float f = dht.readTemperature(true);

    // Print to Serial in CSV format
    Serial.print(currentMillis);
    Serial.print(",");
    Serial.print(t, 1);
    Serial.print(",");
    Serial.print(f, 1);
    Serial.print(",");
    Serial.println(h, 1);

    // Threshold checks (Temp > 35C or Humidity > 80%)
    if (t > 35.0 || h > 80.0) {
      digitalWrite(RED_LED, HIGH);   // Alert state
      digitalWrite(GREEN_LED, LOW);
    } else {
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);  // Normal state
    }
  }
}
