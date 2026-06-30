/**
 * @file serial_command.ino
 * @author Vraj Ramavat
 * @brief Command receiver via Serial Monitor to control built-in LED.
 * Submitted for Q16.
 */

const int LED_PIN = 13;
unsigned long totalBlinks = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Start with LED off
  
  Serial.begin(9600);
  Serial.println("=========================================");
  Serial.println("Serial Command Interface Initialized");
  Serial.println("Supported Commands:");
  Serial.println("  LED_ON   - Turn built-in LED on");
  Serial.println("  LED_OFF  - Turn built-in LED off");
  Serial.println("  BLINK_X  - Blink LED X times (X = 1 to 9)");
  Serial.println("  STATUS   - Print current status of LED and counters");
  Serial.println("  RESET    - Restart blink counter to 0");
  Serial.println("=========================================");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim(); // Remove leading/trailing whitespaces or carriage returns (\r)
    
    if (input.length() == 0) return; // Skip empty inputs
    
    if (input.equalsIgnoreCase("LED_ON")) {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("SUCCESS: LED is turned ON");
    } 
    else if (input.equalsIgnoreCase("LED_OFF")) {
      digitalWrite(LED_PIN, LOW);
      Serial.println("SUCCESS: LED is turned OFF");
    } 
    else if (input.startsWith("BLINK_") || input.startsWith("blink_")) {
      // Check if command format is correct (BLINK_X where length is 7)
      if (input.length() == 7) {
        char valChar = input.charAt(6);
        if (valChar >= '1' && valChar <= '9') {
          int count = valChar - '0';
          Serial.print("SUCCESS: Blinking LED ");
          Serial.print(count);
          Serial.println(" times...");
          
          blinkLED(count);
        } else {
          Serial.println("ERROR: BLINK parameter must be a digit between 1 and 9");
        }
      } else {
        Serial.println("ERROR: Invalid BLINK command format. Use BLINK_X");
      }
    } 
    else if (input.equalsIgnoreCase("STATUS")) {
      int ledState = digitalRead(LED_PIN);
      Serial.println("--- SYSTEM STATUS ---");
      Serial.print("LED Pin 13 State: ");
      Serial.println(ledState == HIGH ? "HIGH (ON)" : "LOW (OFF)");
      Serial.print("Total Blinks Triggered: ");
      Serial.println(totalBlinks);
      Serial.println("---------------------");
    } 
    else if (input.equalsIgnoreCase("RESET")) {
      totalBlinks = 0;
      Serial.println("SUCCESS: Blink counter reset to 0");
    } 
    else {
      Serial.print("ERROR: Unknown command '");
      Serial.print(input);
      Serial.println("'");
    }
  }
}

// Function to blink LED X times
void blinkLED(int times) {
  // Store initial LED state to restore it later
  int initialState = digitalRead(LED_PIN);
  
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(250);
    digitalWrite(LED_PIN, LOW);
    delay(250);
    totalBlinks++;
  }
  
  // Restore initial LED state
  digitalWrite(LED_PIN, initialState);
}
