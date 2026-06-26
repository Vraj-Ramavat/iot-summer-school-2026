/**
 * @file traffic_light.ino
 * @author Vraj Ramavat
 * @brief Non-blocking traffic light simulator with pedestrian override.
 * Submitted for Q14.
 */

// Pin definitions
const int RED_LED = 10;
const int YELLOW_LED = 9;
const int GREEN_LED = 8;
const int PEDESTRIAN_BUTTON = 7;

// States definition
enum TrafficState {
  STATE_RED,
  STATE_YELLOW,
  STATE_GREEN,
  STATE_PEDESTRIAN_RED
};

TrafficState currentState = STATE_RED;
unsigned long lastStateChange = 0;
unsigned long stateDuration = 5000; // RED initially for 5 seconds

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(PEDESTRIAN_BUTTON, INPUT); // Assumes external pull-down resistor

  Serial.begin(9600);
  Serial.println("--- Traffic Light Controller Initialized ---");
  setLights(HIGH, LOW, LOW); // Start with RED
  printState("RED");
  lastStateChange = millis();
}

void loop() {
  unsigned long currentMillis = millis();

  // Read pedestrian button
  // If pressed and we are not already in RED or PEDESTRIAN_RED, trigger immediately
  if (digitalRead(PEDESTRIAN_BUTTON) == HIGH && 
      currentState != STATE_RED && 
      currentState != STATE_PEDESTRIAN_RED) {
    
    Serial.print("[");
    Serial.print(currentMillis);
    Serial.println("] EVENT: Pedestrian button pressed! Forcing RED immediately.");
    
    currentState = STATE_PEDESTRIAN_RED;
    setLights(HIGH, LOW, LOW);
    printState("PEDESTRIAN RED (Override)");
    lastStateChange = currentMillis;
    stateDuration = 8000; // Hold RED for 8 seconds
  }

  // Check state timer
  if (currentMillis - lastStateChange >= stateDuration) {
    lastStateChange = currentMillis;
    
    // State transitions
    switch (currentState) {
      case STATE_RED:
        currentState = STATE_YELLOW;
        setLights(LOW, HIGH, LOW);
        stateDuration = 2000; // YELLOW for 2 seconds
        printState("YELLOW");
        break;

      case STATE_YELLOW:
        currentState = STATE_GREEN;
        setLights(LOW, LOW, HIGH);
        stateDuration = 4000; // GREEN for 4 seconds
        printState("GREEN");
        break;

      case STATE_GREEN:
      case STATE_PEDESTRIAN_RED:
        // Transition back to RED (normal cycle)
        currentState = STATE_RED;
        setLights(HIGH, LOW, LOW);
        stateDuration = 5000; // RED for 5 seconds
        printState("RED");
        break;
    }
  }
}

// Helper to set LEDs
void setLights(int redVal, int yellowVal, int greenVal) {
  digitalWrite(RED_LED, redVal);
  digitalWrite(YELLOW_LED, yellowVal);
  digitalWrite(GREEN_LED, greenVal);
}

// Helper to print logs
void printState(const char* stateName) {
  Serial.print("[");
  Serial.print(millis());
  Serial.print("] STATE: ");
  Serial.println(stateName);
}
