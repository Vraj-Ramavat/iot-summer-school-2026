const int POT_PIN = A0;
unsigned long blinkCount = 0;
void setup() {
  pinMode(13, OUTPUT);
  pinMode(POT_PIN, INPUT);
  Serial.begin(9600);
}
void loop() {
  int potValue = analogRead(POT_PIN);
  int delayMs = map(potValue, 0, 1023, 100, 2000);
  digitalWrite(13, HIGH);
  delay(delayMs);
  digitalWrite(13, LOW);
  delay(delayMs);
  blinkCount++;
  Serial.print("Blink count: ");
  Serial.print(blinkCount);
  Serial.print(" | Delay: ");
  Serial.println(delayMs);
}
