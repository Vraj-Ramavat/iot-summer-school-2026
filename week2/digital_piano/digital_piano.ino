/**
 * @file digital_piano.ino
 * @author Vraj Ramavat
 * @brief 4-key digital piano with buzzer, chord detection, and scale toggle.
 * Submitted for Q15.
 */

// Pin definitions
const int BTN_1 = 2; // Do
const int BTN_2 = 3; // Re
const int BTN_3 = 4; // Mi / Me
const int BTN_4 = 5; // Fa
const int BTN_MODE = 6; // Mode toggle (Major/Minor)
const int BUZZER_PIN = 11; // Passive Buzzer

// Scale modes
enum ScaleMode {
  SCALE_MAJOR,
  SCALE_MINOR
};

ScaleMode currentScale = SCALE_MAJOR;
bool modeBtnPrevState = LOW;
unsigned long lastModeDebounce = 0;
const unsigned long DEBOUNCE_DELAY = 50;

// Notes frequencies (Hz)
// Major scale: Do (262), Re (294), Mi (330), Fa (349), Sol (392)
// Minor scale: Do (262), Re (294), Me (311), Fa (349), Sol (392)
const int FREQ_DO = 262;
const int FREQ_RE = 294;
const int FREQ_MI_MAJOR = 330;
const int FREQ_MI_MINOR = 311; // E-flat (Me)
const int FREQ_FA = 349;
const int FREQ_SOL = 392; // Chord substitute

void setup() {
  pinMode(BTN_1, INPUT);
  pinMode(BTN_2, INPUT);
  pinMode(BTN_3, INPUT);
  pinMode(BTN_4, INPUT);
  pinMode(BTN_MODE, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(9600);
  Serial.println("--- Digital Piano Initialized ---");
  Serial.println("Mode: MAJOR Scale (Do, Re, Mi, Fa)");
}

void loop() {
  unsigned long currentMillis = millis();

  // 1. Debounce and read Mode Button
  int modeBtnRead = digitalRead(BTN_MODE);
  if (modeBtnRead != modeBtnPrevState) {
    if (currentMillis - lastModeDebounce > DEBOUNCE_DELAY) {
      modeBtnPrevState = modeBtnRead;
      if (modeBtnRead == HIGH) {
        // Toggle scale
        if (currentScale == SCALE_MAJOR) {
          currentScale = SCALE_MINOR;
          Serial.println("Scale toggled to: MINOR Scale (Do, Re, Me, Fa)");
        } else {
          currentScale = SCALE_MAJOR;
          Serial.println("Scale toggled to: MAJOR Scale (Do, Re, Mi, Fa)");
        }
      }
    }
    lastModeDebounce = currentMillis;
  }

  // 2. Read Key Buttons
  bool b1 = digitalRead(BTN_1) == HIGH;
  bool b2 = digitalRead(BTN_2) == HIGH;
  bool b3 = digitalRead(BTN_3) == HIGH;
  bool b4 = digitalRead(BTN_4) == HIGH;

  int pressedCount = (b1 ? 1 : 0) + (b2 ? 1 : 0) + (b3 ? 1 : 0) + (b4 ? 1 : 0);

  // 3. Play sound based on button state
  if (pressedCount >= 2) {
    // If two or more buttons are pressed together: play Sol as a chord substitute
    tone(BUZZER_PIN, FREQ_SOL);
  } else if (pressedCount == 1) {
    if (b1) {
      tone(BUZZER_PIN, FREQ_DO);
    } else if (b2) {
      tone(BUZZER_PIN, FREQ_RE);
    } else if (b3) {
      // Third degree changes depending on Major/Minor scale
      int thirdFreq = (currentScale == SCALE_MAJOR) ? FREQ_MI_MAJOR : FREQ_MI_MINOR;
      tone(BUZZER_PIN, thirdFreq);
    } else if (b4) {
      tone(BUZZER_PIN, FREQ_FA);
    }
  } else {
    // No buttons pressed: silence the buzzer
    noTone(BUZZER_PIN);
  }
}
