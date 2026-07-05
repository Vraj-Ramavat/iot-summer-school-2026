/**
 * @file servo_control.ino
 * @author Vraj Ramavat
 * @brief Potentiometer-controlled servo motor with manual button sweep override.
 * Submitted for Q25.
 */

#include <Servo.h>

// Pin definitions
const int SERVO_PIN = 9;
const int POT_PIN = A0;
const int BUTTON_PIN = 2;

Servo myServo;

// Variables
int previousAngle = -1;
bool isSweeping = false;

// Debouncing button
bool lastBtnState = LOW;
unsigned long lastDebounce = 0;
const unsigned long DEBOUNCE_DELAY = 50;

void setup() {
  myServo.attach(SERVO_PIN);
  pinMode(BUTTON_PIN, INPUT); // Assumes external pull-down resistor
  
  Serial.begin(9600);
  Serial.println("--- Potentiometer & Sweep Servo Controller Initialized ---");
  Serial.println("Rotate Potentiometer to control angle. Press Button for auto 0-180-0 sweep.");
}

void loop() {
  unsigned long currentMillis = millis();

  // Read button with debounce
  int btnRead = digitalRead(BUTTON_PIN);
  bool buttonPressed = false;
  
  if (btnRead != lastBtnState) {
    if (currentMillis - lastDebounce > DEBOUNCE_DELAY) {
      lastBtnState = btnRead;
      if (btnRead == HIGH) {
        buttonPressed = true;
      }
    }
    lastDebounce = currentMillis;
  }

  // Trigger manual sweep if button is pressed
  if (buttonPressed && !isSweeping) {
    runManualSweep();
  }

  // Potentiometer control state
  if (!isSweeping) {
    int potValue = analogRead(POT_PIN);
    // Map raw ADC (0-1023) to angle (0-180)
    int targetAngle = map(potValue, 0, 1023, 0, 180);

    // Only update and print if angle changes significantly (deadband of 1 degree)
    if (abs(targetAngle - previousAngle) > 1) {
      myServo.write(targetAngle);
      previousAngle = targetAngle;
      
      Serial.print("MODE: Manual Potentiometer | Angle: ");
      Serial.print(targetAngle);
      Serial.println(" deg");
    }
    delay(15); // Short delay for servo positioning
  }
}

// Function to perform a smooth sweep 0 -> 180 -> 0 degrees
void runManualSweep() {
  isSweeping = true;
  Serial.println("MODE: Auto-Sweep Triggered! Sweeping 0 -> 180...");

  // Sweep from 0 to 180
  for (int angle = 0; angle <= 180; angle++) {
    myServo.write(angle);
    if (angle % 10 == 0) {
      Serial.print("Auto-Sweep Angle: ");
      Serial.print(angle);
      Serial.println(" deg");
    }
    delay(15); // Control sweep speed
  }

  delay(200); // Brief pause at 180
  Serial.println("Sweeping 180 -> 0...");

  // Sweep from 180 to 0
  for (int angle = 180; angle >= 0; angle--) {
    myServo.write(angle);
    if (angle % 10 == 0) {
      Serial.print("Auto-Sweep Angle: ");
      Serial.print(angle);
      Serial.println(" deg");
    }
    delay(15);
  }

  Serial.println("Auto-Sweep Complete. Returning to Potentiometer control.");
  isSweeping = false;
  previousAngle = -1; // Force rewrite of pot value
}
