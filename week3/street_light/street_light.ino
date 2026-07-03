/**
 * @file street_light.ino
 * @author Vraj Ramavat
 * @brief Smart street light system using LDR light sensor and PIR motion sensor.
 * Submitted for Q23.
 */

// Pin definitions
const int LDR_PIN = A0;      // Analog input for LDR
const int PIR_PIN = 2;       // Digital input for PIR
const int LED_PIN = 6;       // PWM pin for LED control

// Configuration parameters
const int LDR_THRESHOLD = 400;      // Below this is considered "dark" (night)
const unsigned long MOTION_TIME = 30000; // Motion hold duration (30 seconds)

// State variables
enum StreetLightState {
  STATE_DAY,
  STATE_NIGHT_DIM,
  STATE_NIGHT_BRIGHT
};

StreetLightState currentState = STATE_DAY;
unsigned long motionTriggerTime = 0;
bool previousPirState = LOW;
int previousLdrRaw = 0;

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("--- Smart Street Light Controller Initialized ---");
  logEvent("System booted. Operational check starting.");
}

void loop() {
  unsigned long currentMillis = millis();
  int ldrValue = analogRead(LDR_PIN);
  bool motionDetected = digitalRead(PIR_PIN) == HIGH;
  
  bool isDark = (ldrValue < LDR_THRESHOLD);

  switch (currentState) {
    case STATE_DAY:
      // LED is OFF
      analogWrite(LED_PIN, 0);

      // If it gets dark, transit to Night Dim state
      if (isDark) {
        logEvent("Ambient light fell below threshold. Switched to NIGHT MODE.");
        currentState = STATE_NIGHT_DIM;
      }
      break;

    case STATE_NIGHT_DIM:
      // LED is dimmed to 20% (approx 51 out of 255)
      analogWrite(LED_PIN, 51);

      // If PIR detects motion, trigger full brightness
      if (motionDetected) {
        logEvent("Motion detected. Increasing brightness to 100%.");
        currentState = STATE_NIGHT_BRIGHT;
        motionTriggerTime = currentMillis;
      }
      // If it becomes light again, transit to Day
      else if (!isDark) {
        logEvent("Daylight detected. Switched to DAY MODE.");
        currentState = STATE_DAY;
      }
      break;

    case STATE_NIGHT_BRIGHT:
      // LED is at full brightness (255)
      analogWrite(LED_PIN, 255);

      // If motion is re-triggered, reset timer
      if (motionDetected) {
        if (!previousPirState) {
          logEvent("Motion re-detected. Resetting 30s timer.");
        }
        motionTriggerTime = currentMillis;
      }

      // If no motion for more than 30s, dim back to 20%
      if (currentMillis - motionTriggerTime >= MOTION_TIME) {
        logEvent("30s timeout reached with no motion. Dimming LED to 20%.");
        currentState = STATE_NIGHT_DIM;
      }
      // If it becomes light again (e.g. flashlight test), transit to Day
      else if (!isDark) {
        logEvent("Daylight detected. Switched to DAY MODE.");
        currentState = STATE_DAY;
      }
      break;
  }

  previousPirState = motionDetected;
  previousLdrRaw = ldrValue;
  
  // Wait a small amount of time to stabilize
  delay(50);
}

// Function to print logs with timestamp [HH:MM:SS]
void logEvent(const char* desc) {
  unsigned long totalSeconds = millis() / 1000;
  unsigned long seconds = totalSeconds % 60;
  unsigned long totalMinutes = totalSeconds / 60;
  unsigned long minutes = totalMinutes % 60;
  unsigned long hours = totalMinutes / 60 % 24;

  Serial.print("[");
  if (hours < 10) Serial.print("0");
  Serial.print(hours);
  Serial.print(":");
  if (minutes < 10) Serial.print("0");
  Serial.print(minutes);
  Serial.print(":");
  if (seconds < 10) Serial.print("0");
  Serial.print(seconds);
  Serial.print("] EVENT: ");
  Serial.println(desc);
}
