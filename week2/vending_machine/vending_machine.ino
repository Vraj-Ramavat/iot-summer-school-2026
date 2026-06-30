/**
 * @file vending_machine.ino
 * @author Vraj Ramavat
 * @brief Vending machine finite state machine with 3-button controls and LEDs.
 * Submitted for Q18.
 * 
 * =======================================================================
 * STATE TRANSITION DIAGRAM
 * =======================================================================
 * 
 *          +-------------------------------------------------+
 *          |                                                 |
 *          v                                                 |
 *       [ IDLE ] <-----------------+                         |
 *          |                       |                         |
 *          | (Insert Coin Button)  | (Cancel Button)         |
 *          v                       |                         |
 *    [ COIN_INSERTED ] ------------+                         |
 *          |                                                 |
 *          | (Select Item Button)                            |
 *          v                                                 |
 *    [ ITEM_SELECTED ]                                       |
 *          |                                                 |
 *          | (Automatic transition after 1.5 seconds)         |
 *          v                                                 |
 *     [ DISPENSING ] ----------------------------------------+
 *          (Runs for 3 seconds, flashes LED, returns to IDLE)
 * 
 * =======================================================================
 */

// Pin definitions
const int BTN_COIN = 2;   // Insert Coin Button
const int BTN_SELECT = 3; // Select Item Button
const int BTN_CANCEL = 4; // Cancel Button

const int LED_IDLE = 10;   // Red LED (System Idle)
const int LED_READY = 9;   // Yellow LED (Credit loaded / item chosen)
const int LED_DISPENSE = 8; // Green LED (Dispensing)

// State enumeration
enum VendingState {
  IDLE,
  COIN_INSERTED,
  ITEM_SELECTED,
  DISPENSING
};

VendingState currentState = IDLE;
unsigned long stateTimer = 0;
const unsigned long SELECT_HOLD_TIME = 1500; // Time in ITEM_SELECTED state
const unsigned long DISPENSE_TIME = 3000;    // Time to dispense

// Debounce helper variables
bool lastCoinBtn = LOW;
bool lastSelectBtn = LOW;
bool lastCancelBtn = LOW;
unsigned long lastDebounce = 0;
const unsigned long DEBOUNCE_DELAY = 50;

void setup() {
  pinMode(BTN_COIN, INPUT);
  pinMode(BTN_SELECT, INPUT);
  pinMode(BTN_CANCEL, INPUT);
  
  pinMode(LED_IDLE, OUTPUT);
  pinMode(LED_READY, OUTPUT);
  pinMode(LED_DISPENSE, OUTPUT);

  Serial.begin(9600);
  Serial.println("=========================================");
  Serial.println("Vending Machine FSM Simulation Initialized");
  Serial.println("=========================================");
  
  transitionTo(IDLE);
}

void loop() {
  unsigned long currentMillis = millis();

  // Read and debounce buttons
  bool coinPressed = false;
  bool selectPressed = false;
  bool cancelPressed = false;

  int coinRead = digitalRead(BTN_COIN);
  int selectRead = digitalRead(BTN_SELECT);
  int cancelRead = digitalRead(BTN_CANCEL);

  if (currentMillis - lastDebounce > DEBOUNCE_DELAY) {
    if (coinRead == HIGH && lastCoinBtn == LOW) {
      coinPressed = true;
      lastDebounce = currentMillis;
    }
    if (selectRead == HIGH && lastSelectBtn == LOW) {
      selectPressed = true;
      lastDebounce = currentMillis;
    }
    if (cancelRead == HIGH && lastCancelBtn == LOW) {
      cancelPressed = true;
      lastDebounce = currentMillis;
    }
  }
  
  lastCoinBtn = coinRead;
  lastSelectBtn = selectRead;
  lastCancelBtn = cancelRead;

  // State processing
  switch (currentState) {
    case IDLE:
      if (coinPressed) {
        transitionTo(COIN_INSERTED);
      } else if (selectPressed) {
        Serial.println("[ERROR] Cannot select item: Insert coin first.");
      }
      break;

    case COIN_INSERTED:
      if (selectPressed) {
        transitionTo(ITEM_SELECTED);
      } else if (cancelPressed) {
        Serial.println("[EVENT] Refunding coin...");
        transitionTo(IDLE);
      }
      break;

    case ITEM_SELECTED:
      // Auto-transition to DISPENSING after SELECT_HOLD_TIME
      if (currentMillis - stateTimer >= SELECT_HOLD_TIME) {
        transitionTo(DISPENSING);
      }
      break;

    case DISPENSING:
      // Flash Green LED during dispensing
      if ((currentMillis / 250) % 2 == 0) {
        digitalWrite(LED_DISPENSE, HIGH);
      } else {
        digitalWrite(LED_DISPENSE, LOW);
      }

      // Auto-transition back to IDLE after DISPENSE_TIME
      if (currentMillis - stateTimer >= DISPENSE_TIME) {
        Serial.println("[EVENT] Dispensing complete! Thank you.");
        transitionTo(IDLE);
      }
      break;
  }
}

// Function to handle state transitions and their side effects
void transitionTo(VendingState newState) {
  currentState = newState;
  stateTimer = millis();

  // Reset LED States
  digitalWrite(LED_IDLE, LOW);
  digitalWrite(LED_READY, LOW);
  digitalWrite(LED_DISPENSE, LOW);

  switch (newState) {
    case IDLE:
      digitalWrite(LED_IDLE, HIGH);
      Serial.println("[TRANSITION] State: IDLE. Ready for new transaction. (Red LED ON)");
      break;

    case COIN_INSERTED:
      digitalWrite(LED_READY, HIGH);
      Serial.println("[TRANSITION] State: COIN INSERTED. Select your item or press Cancel. (Yellow LED ON)");
      break;

    case ITEM_SELECTED:
      digitalWrite(LED_READY, HIGH);
      digitalWrite(LED_IDLE, HIGH); // Turn both on for selection state representation
      Serial.println("[TRANSITION] State: ITEM SELECTED. Processing purchase... (Red & Yellow LEDs ON)");
      break;

    case DISPENSING:
      // Green LED flashes (handled inside loop), turn off others
      Serial.println("[TRANSITION] State: DISPENSING. Please wait for your item... (Green LED Flashing)");
      break;
  }
}
