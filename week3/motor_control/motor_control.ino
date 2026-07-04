/**
 * @file motor_control.ino
 * @author Vraj Ramavat
 * @brief DC Motor speed and direction control using L298N driver and buttons.
 * Submitted for Q26.
 */

// L298N Driver Pins
const int ENA_PIN = 6;  // PWM speed control
const int IN1_PIN = 7;  // Direction control pin 1
const int IN2_PIN = 8;  // Direction control pin 2

// Control Inputs
const int POT_PIN = A0;      // Speed control pot
const int BTN_DIR_PIN = 2;   // Direction toggle button
const int BTN_STATE_PIN = 3; // Start/Stop toggle button

// Operational State Variables
bool motorRunning = false;
bool isForward = true;
int currentPwm = 0;

// Debouncing variables
bool lastDirBtn = LOW;
bool lastStateBtn = LOW;
unsigned long lastDebounceTime = 0;
const unsigned long DEBOUNCE_DELAY = 50;

// Serial output throttling
unsigned long lastLogTime = 0;
const unsigned long LOG_INTERVAL = 500; // Log status every 500ms

void setup() {
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  
  pinMode(BTN_DIR_PIN, INPUT);   // Assumes external pull-down resistors
  pinMode(BTN_STATE_PIN, INPUT);

  Serial.begin(9600);
  Serial.println("--- L298N DC Motor Controller Initialized ---");
  Serial.println("Button on pin 3: Start/Stop | Button on pin 2: Change Direction");
  
  // Initialize motor in stopped state
  stopMotor();
}

void loop() {
  unsigned long currentMillis = millis();

  // 1. Read Inputs
  int potValue = analogRead(POT_PIN);
  int dirRead = digitalRead(BTN_DIR_PIN);
  int stateRead = digitalRead(BTN_STATE_PIN);

  // 2. Debounce and Process Buttons
  if (currentMillis - lastDebounceTime > DEBOUNCE_DELAY) {
    // Start/Stop button pressed
    if (stateRead == HIGH && lastStateBtn == LOW) {
      motorRunning = !motorRunning;
      lastDebounceTime = currentMillis;
      Serial.print("[BUTTON] Motor state toggled: ");
      Serial.println(motorRunning ? "RUNNING" : "STOPPED");
    }
    
    // Direction button pressed
    if (dirRead == HIGH && lastDirBtn == LOW) {
      isForward = !isForward;
      lastDebounceTime = currentMillis;
      Serial.print("[BUTTON] Direction state toggled: ");
      Serial.println(isForward ? "FORWARD" : "REVERSE");
    }
  }
  
  lastStateBtn = stateRead;
  lastDirBtn = dirRead;

  // 3. Update Motor State
  currentPwm = map(potValue, 0, 1023, 0, 255);

  if (motorRunning) {
    if (isForward) {
      digitalWrite(IN1_PIN, HIGH);
      digitalWrite(IN2_PIN, LOW);
    } else {
      digitalWrite(IN1_PIN, LOW);
      digitalWrite(IN2_PIN, HIGH);
    }
    analogWrite(ENA_PIN, currentPwm);
  } else {
    stopMotor();
  }

  // 4. Log status periodically (non-blocking)
  if (currentMillis - lastLogTime >= LOG_INTERVAL) {
    lastLogTime = currentMillis;

    int speedPercent = map(currentPwm, 0, 255, 0, 100);
    
    Serial.print("MOTOR STATUS: ");
    Serial.print(motorRunning ? "RUNNING" : "STOPPED");
    Serial.print(" | Speed: ");
    Serial.print(motorRunning ? speedPercent : 0);
    Serial.print("% (PWM: ");
    Serial.print(motorRunning ? currentPwm : 0);
    Serial.print(") | Direction: ");
    Serial.println(isForward ? "FORWARD" : "REVERSE");
  }
}

void stopMotor() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  analogWrite(ENA_PIN, 0);
}
