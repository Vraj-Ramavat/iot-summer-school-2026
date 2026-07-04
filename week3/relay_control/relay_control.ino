/**
 * @file relay_control.ino
 * @author Vraj Ramavat
 * @brief Temperature-triggered relay controller (AC Simulation) with hysteresis and manual override.
 * Submitted for Q27.
 */

#include "DHT.h"

// Pin definitions
#define DHTPIN 2
#define DHTTYPE DHT11

const int RELAY_PIN = 8;        // Connected to relay driver (simulated by LED)
const int OVERRIDE_BUTTON = 3;  // Manual override button

// Temperature Thresholds with Hysteresis
const float TEMP_HIGH_THRESHOLD = 32.0; // AC turns ON
const float TEMP_LOW_THRESHOLD = 28.0;  // AC turns OFF

DHT dht(DHTPIN, DHTTYPE);

// System states
bool relayState = LOW;
bool manualOverride = false;

// Time tracking
unsigned long lastSensorRead = 0;
const unsigned long SENSOR_READ_INTERVAL = 2000; // Read DHT every 2s

// Debounce variables
bool lastBtnState = LOW;
unsigned long lastDebounceTime = 0;
const unsigned long DEBOUNCE_DELAY = 50;

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(OVERRIDE_BUTTON, INPUT); // Assumes external pull-down resistor
  
  digitalWrite(RELAY_PIN, LOW); // Start with relay off
  
  Serial.begin(9600);
  Serial.println("--- Relay AC Simulation Controller Booted ---");
  Serial.println("Auto mode thresholds: ON > 32.0 C | OFF < 28.0 C");
  Serial.println("Press manual button to override and toggle relay.");
  
  dht.begin();
}

void loop() {
  unsigned long currentMillis = millis();

  // 1. Debounce and read Manual Override Button
  int btnRead = digitalRead(OVERRIDE_BUTTON);
  if (btnRead != lastBtnState) {
    if (currentMillis - lastDebounceTime > DEBOUNCE_DELAY) {
      lastBtnState = btnRead;
      if (btnRead == HIGH) {
        // Toggle manual override mode
        manualOverride = !manualOverride;
        
        if (manualOverride) {
          // Invert current relay state and keep it locked
          relayState = !relayState;
          digitalWrite(RELAY_PIN, relayState);
          Serial.print("[OVERRIDE] Manual override ACTIVE. Relay forced to: ");
          Serial.println(relayState == HIGH ? "ON (AC Running)" : "OFF (AC Stopped)");
        } else {
          Serial.println("[OVERRIDE] Manual override INACTIVE. Returning to Auto Mode.");
          // Force immediate re-evaluation in Auto Mode
          lastSensorRead = 0;
        }
      }
    }
    lastDebounceTime = currentMillis;
  }

  // 2. Periodic sensor reading and automatic control (only if override is inactive)
  if (currentMillis - lastSensorRead >= SENSOR_READ_INTERVAL) {
    lastSensorRead = currentMillis;
    
    float temperature = dht.readTemperature();
    
    if (isnan(temperature)) {
      Serial.println("[ERROR] Failed to read from DHT sensor!");
      return;
    }

    Serial.print("[LOG] Temp: ");
    Serial.print(temperature, 1);
    Serial.print(" C | Relay Mode: ");
    Serial.print(manualOverride ? "MANUAL" : "AUTO");
    Serial.print(" | Relay State: ");
    Serial.println(relayState == HIGH ? "ON" : "OFF");

    if (!manualOverride) {
      bool previousState = relayState;

      // Hysteresis control logic
      if (temperature > TEMP_HIGH_THRESHOLD) {
        relayState = HIGH;
      } 
      else if (temperature < TEMP_LOW_THRESHOLD) {
        relayState = LOW;
      }

      // Actuate relay and log changes
      if (relayState != previousState) {
        digitalWrite(RELAY_PIN, relayState);
        Serial.print("[AUTO TRANSITION] Temp reached ");
        Serial.print(temperature, 1);
        Serial.print(" C. Relay changed to: ");
        Serial.println(relayState == HIGH ? "ON (AC cooling)" : "OFF (AC off)");
      }
    }
  }
}
