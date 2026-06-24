/**
 * @file led_blink.ino
 * @author Vraj Ramavat
 * @brief Potentiometer-controlled LED blink rate with serial logging.
 * 
 * Reads an analog potentiometer voltage on pin A0 and maps it
 * to control the blinking rate of the pin 13 LED, logging results.
 */

const int LED_PIN = 13;
const int POT_PIN = A0;
unsigned long blinkCount = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(POT_PIN, INPUT);
  Serial.begin(9600);
  Serial.println("System Initialized: Potentiometer LED Blink Controller");
}

void loop() {
  int potValue = analogRead(POT_PIN);
  int delayMs = map(potValue, 0, 1023, 100, 2000);
  
  digitalWrite(LED_PIN, HIGH);
  delay(delayMs);
  
  digitalWrite(LED_PIN, LOW);
  delay(delayMs);
  
  blinkCount++;
  Serial.print("Blink count: ");
  Serial.print(blinkCount);
  Serial.print(" | Pot Raw: ");
  Serial.print(potValue);
  Serial.print(" | Delay: ");
  Serial.print(delayMs);
  Serial.println(" ms");
}
