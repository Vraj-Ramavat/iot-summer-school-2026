/**
 * @file keypad_lcd.ino
 * @author Vraj Ramavat
 * @brief Keypad and I2C LCD based password security system with lockout mechanism.
 * Submitted for Q28.
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// LCD Setup: Address 0x27, 16 Columns, 2 Rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Keypad Configuration
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; // Row pin connections
byte colPins[COLS] = {5, 4, 3, 2}; // Col pin connections

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Pin definitions
const int LED_GREEN = 10;
const int LED_RED = 11;
const int BUZZER_PIN = 12;

// Security settings
const char CORRECT_PIN[5] = "1234"; // 4-digit PIN + null terminator
char enteredPin[5] = "";
byte pinIndex = 0;
byte wrongAttempts = 0;

void setup() {
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Initialize LCD
  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
  Serial.println("--- Keypad Security Access System Initialized ---");
  
  resetSystem();
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    // Beep briefly on any key press
    tone(BUZZER_PIN, 1000, 50);

    // If '#' is pressed, clear the input
    if (key == '#') {
      resetPinInput();
      return;
    }

    // Process digits (exclude function letters and symbols)
    if (key >= '0' && key <= '9') {
      enteredPin[pinIndex] = key;
      pinIndex++;
      
      // Print asterisk on LCD
      lcd.setCursor(pinIndex + 5, 1); // Centered entry line
      lcd.print('*');

      if (pinIndex == 4) {
        enteredPin[4] = '\0'; // Add null terminator
        checkPin();
      }
    }
  }
}

// Check PIN validity
void checkPin() {
  delay(300); // Give user a brief feedback moment
  lcd.clear();

  if (strcmp(enteredPin, CORRECT_PIN) == 0) {
    // PIN correct: ACCESS GRANTED
    Serial.println("[SECURITY] Correct PIN entered. Access Granted.");
    lcd.setCursor(1, 0);
    lcd.print("ACCESS GRANTED");
    lcd.setCursor(4, 1);
    lcd.print("WELCOME!");
    
    digitalWrite(LED_GREEN, HIGH);
    
    // Success sound (harmonic arpeggio)
    tone(BUZZER_PIN, 523, 100); // Do
    delay(120);
    tone(BUZZER_PIN, 659, 100); // Mi
    delay(120);
    tone(BUZZER_PIN, 784, 150); // Sol
    
    delay(2000);
    wrongAttempts = 0;
    resetSystem();
  } 
  else {
    // PIN incorrect: ACCESS DENIED
    wrongAttempts++;
    Serial.print("[SECURITY] Incorrect PIN. Attempts: ");
    Serial.print(wrongAttempts);
    Serial.println("/3");

    lcd.setCursor(1, 0);
    lcd.print("ACCESS DENIED!");
    lcd.setCursor(0, 1);
    lcd.print("INVALID PIN code");

    digitalWrite(LED_RED, HIGH);
    
    // Alarm tone (low frequency flat buzz)
    tone(BUZZER_PIN, 150, 500);
    delay(2000);

    if (wrongAttempts >= 3) {
      lockoutSystem();
    } else {
      resetSystem();
    }
  }
}

// Lockout system for 10 seconds
void lockoutSystem() {
  Serial.println("[SECURITY] 3 Failed attempts. System locked out for 10s.");
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("SYSTEM LOCKED!");
  
  digitalWrite(LED_GREEN, LOW);
  
  for (int secondsLeft = 10; secondsLeft > 0; secondsLeft--) {
    lcd.setCursor(0, 1);
    lcd.print("Wait: ");
    lcd.print(secondsLeft);
    lcd.print(" seconds  ");

    // Flash Red LED and buzz briefly each second
    digitalWrite(LED_RED, HIGH);
    tone(BUZZER_PIN, 1000, 100);
    delay(500);
    digitalWrite(LED_RED, LOW);
    delay(500);
  }

  wrongAttempts = 0;
  resetSystem();
}

// Reset entry state
void resetPinInput() {
  pinIndex = 0;
  memset(enteredPin, 0, sizeof(enteredPin));
  lcd.setCursor(0, 1);
  lcd.print("      [____]    "); // Clean template line
}

// Reset entire visual state
void resetSystem() {
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);
  noTone(BUZZER_PIN);
  
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("ENTER PIN:");
  
  resetPinInput();
}
