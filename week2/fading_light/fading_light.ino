/**
 * @file fading_light.ino
 * @author Vraj Ramavat
 * @brief PWM fading night light with three button-switchable modes.
 * Submitted for Q17.
 */

// Pin definitions
const int LED_PIN = 9;       // PWM-enabled pin
const int BUTTON_PIN = 2;    // Button pin for mode toggle

// Modes definition
enum LightMode {
  MODE_SLOW_BREATH,
  MODE_FAST_PULSE,
  MODE_SOS
};

LightMode currentMode = MODE_SLOW_BREATH;

// Button state variables
bool lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
const unsigned long DEBOUNCE_DELAY = 50; // 50ms debounce

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT); // Assumes external pull-down resistor
  
  Serial.begin(9600);
  Serial.println("--- PWM Fading Night Light Initialized ---");
  Serial.println("Current Mode: SLOW BREATHING (3-second cycle)");
}

void loop() {
  unsigned long currentMillis = millis();

  // 1. Debounce & read button to switch modes
  int reading = digitalRead(BUTTON_PIN);
  if (reading != lastButtonState) {
    if (currentMillis - lastDebounceTime > DEBOUNCE_DELAY) {
      lastButtonState = reading;
      if (reading == HIGH) {
        // Switch to the next mode
        if (currentMode == MODE_SLOW_BREATH) {
          currentMode = MODE_FAST_PULSE;
          Serial.println("Mode Changed: FAST PULSE (0.5-second cycle)");
        } else if (currentMode == MODE_FAST_PULSE) {
          currentMode = MODE_SOS;
          Serial.println("Mode Changed: SOS PATTERN (... --- ...)");
        } else {
          currentMode = MODE_SLOW_BREATH;
          Serial.println("Mode Changed: SLOW BREATHING (3-second cycle)");
        }
      }
    }
    lastDebounceTime = currentMillis;
  }

  // 2. Control LED intensity based on current mode
  int brightness = 0;
  float phase = 0.0;

  switch (currentMode) {
    case MODE_SLOW_BREATH:
      // 3-second cycle (3000ms)
      // Use sine wave to create breathing effect
      phase = (float)(currentMillis % 3000) / 3000.0 * 2.0 * PI;
      brightness = (sin(phase - PI/2.0) + 1.0) / 2.0 * 255.0;
      analogWrite(LED_PIN, brightness);
      break;

    case MODE_FAST_PULSE:
      // 0.5-second cycle (500ms)
      phase = (float)(currentMillis % 500) / 500.0 * 2.0 * PI;
      brightness = (sin(phase - PI/2.0) + 1.0) / 2.0 * 255.0;
      analogWrite(LED_PIN, brightness);
      break;

    case MODE_SOS:
      // Non-blocking SOS pattern
      // S: ... (3 dots = 150ms ON, 150ms OFF)
      // O: --- (3 dashes = 450ms ON, 150ms OFF)
      // S: ... (3 dots = 150ms ON, 150ms OFF)
      // Word Space: 1500ms
      unsigned long sosTime = currentMillis % 5550; // Total pattern duration: 5550ms
      
      if (sosTime < 150)         brightness = 255; // Dot 1
      else if (sosTime < 300)    brightness = 0;
      else if (sosTime < 450)    brightness = 255; // Dot 2
      else if (sosTime < 600)    brightness = 0;
      else if (sosTime < 750)    brightness = 255; // Dot 3
      else if (sosTime < 1200)   brightness = 0;   // Letter space
      else if (sosTime < 1650)   brightness = 255; // Dash 1
      else if (sosTime < 1800)   brightness = 0;
      else if (sosTime < 2250)   brightness = 255; // Dash 2
      else if (sosTime < 2400)   brightness = 0;
      else if (sosTime < 2850)   brightness = 255; // Dash 3
      else if (sosTime < 3300)   brightness = 0;   // Letter space
      else if (sosTime < 3450)   brightness = 255; // Dot 1
      else if (sosTime < 3600)   brightness = 0;
      else if (sosTime < 3750)   brightness = 255; // Dot 2
      else if (sosTime < 3900)   brightness = 0;
      else if (sosTime < 4050)   brightness = 255; // Dot 3
      else                       brightness = 0;   // Word space before repeating
      
      analogWrite(LED_PIN, brightness);
      break;
  }
}
