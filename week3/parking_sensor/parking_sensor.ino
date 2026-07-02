/**
 * @file parking_sensor.ino
 * @author Vraj Ramavat
 * @brief Non-blocking ultrasonic parking alert system with adaptive LED/Buzzer indicators.
 * Submitted for Q22.
 */

// Pin definitions
const int TRIG_PIN = 9;
const int ECHO_PIN = 8;
const int LED_RED = 12;
const int LED_YELLOW = 11;
const int LED_GREEN = 10;
const int BUZZER_PIN = 7;

// Variables for non-blocking timing
unsigned long lastMeasureTime = 0;
const unsigned long MEASURE_INTERVAL = 100; // Measure distance every 100ms

unsigned long lastBuzzerToggle = 0;
bool buzzerState = LOW;

unsigned long lastFlashToggle = 0;
bool flashState = LOW;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(9600);
  Serial.println("--- Ultrasonic Parking Sensor Initialized ---");
}

void loop() {
  unsigned long currentMillis = millis();
  static float distanceCm = 100.0;

  // 1. Non-blocking sensor measurement trigger
  if (currentMillis - lastMeasureTime >= MEASURE_INTERVAL) {
    lastMeasureTime = currentMillis;

    // Send trigger pulse
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Read response pulse duration
    // pulseIn is configured with 20000us timeout (approx 340cm range max) to limit blocking
    long duration = pulseIn(ECHO_PIN, HIGH, 20000); 

    if (duration > 0) {
      // Calculate distance in cm
      distanceCm = (duration * 0.034) / 2.0;
    } else {
      // Out of range or timeout
      distanceCm = 999.0; 
    }
  }

  // 2. Alert logic based on distance
  if (distanceCm > 50.0) {
    // SAFE State
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);
    noTone(BUZZER_PIN);
    
    // Throttle printing SAFE to avoid spamming Serial
    static unsigned long lastSafePrint = 0;
    if (currentMillis - lastSafePrint >= 1000) {
      Serial.print("Distance: ");
      Serial.print(distanceCm);
      Serial.println(" cm | Status: SAFE");
      lastSafePrint = currentMillis;
    }
  } 
  else if (distanceCm >= 20.0 && distanceCm <= 50.0) {
    // Warning State: Yellow LED ON, buzzer beeps every 500ms
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_RED, LOW);
    
    if (currentMillis - lastBuzzerToggle >= 500) {
      lastBuzzerToggle = currentMillis;
      buzzerState = !buzzerState;
      if (buzzerState) {
        tone(BUZZER_PIN, 1000); // 1kHz tone
      } else {
        noTone(BUZZER_PIN);
      }
    }
    
    static unsigned long lastWarningPrint = 0;
    if (currentMillis - lastWarningPrint >= 500) {
      Serial.print("Distance: ");
      Serial.print(distanceCm);
      Serial.println(" cm | Status: WARNING (Slow Alert)");
      lastWarningPrint = currentMillis;
    }
  } 
  else if (distanceCm >= 10.0 && distanceCm < 20.0) {
    // Danger State: Red LED ON, buzzer beeps every 200ms
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, HIGH);
    
    if (currentMillis - lastBuzzerToggle >= 200) {
      lastBuzzerToggle = currentMillis;
      buzzerState = !buzzerState;
      if (buzzerState) {
        tone(BUZZER_PIN, 1200); // 1.2kHz tone
      } else {
        noTone(BUZZER_PIN);
      }
    }
    
    static unsigned long lastDangerPrint = 0;
    if (currentMillis - lastDangerPrint >= 200) {
      Serial.print("Distance: ");
      Serial.print(distanceCm);
      Serial.println(" cm | Status: DANGER (Fast Alert)");
      lastDangerPrint = currentMillis;
    }
  } 
  else {
    // Critical State: All LEDs flash rapidly, buzzer continuous ON
    tone(BUZZER_PIN, 1500); // Continuous 1.5kHz alarm
    
    if (currentMillis - lastFlashToggle >= 100) {
      lastFlashToggle = currentMillis;
      flashState = !flashState;
      digitalWrite(LED_GREEN, flashState);
      digitalWrite(LED_YELLOW, flashState);
      digitalWrite(LED_RED, flashState);
    }
    
    static unsigned long lastCriticalPrint = 0;
    if (currentMillis - lastCriticalPrint >= 100) {
      Serial.print("Distance: ");
      Serial.print(distanceCm);
      Serial.println(" cm | Status: CRITICAL STOP!");
      lastCriticalPrint = currentMillis;
    }
  }
}
