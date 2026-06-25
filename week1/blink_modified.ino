/**
 * @file blink_modified.ino
 * @author Vraj Ramavat
 * @brief Blinks an LED 3 times fast, then pauses for 2 seconds.
 * Submitted for Collaborative Fork & Pull Request task (Q7).
 */

const int LED_PIN = 13;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Blink 3 times fast
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(200); // 200ms ON
    digitalWrite(LED_PIN, LOW);
    delay(200); // 200ms OFF
  }
  
  // Pause for 2 seconds (2000 milliseconds)
  delay(2000);
}
