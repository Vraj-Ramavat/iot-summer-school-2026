# LCD Keypad Password Security System (Q28)

## Hardware Required
- 1x Arduino Uno
- 1x 4x4 Membrane Keypad
- 1x 16x2 LCD Display with I2C Backboard
- 2x LEDs (Red, Green)
- 2x 220Ω Resistors
- 1x Passive Buzzer

## Circuit Connections
1. Keypad rows to pins 9, 8, 7, 6; Columns to pins 5, 4, 3, 2.
2. LCD VCC to 5V, GND to GND, SDA to A4, SCL to A5.
3. LEDs to pins 10, 11 (with 220Ω resistors); Buzzer to pin 12.

## Expected Output
Displays 'ENTER PIN:' on LCD. Inputs are displayed as asterisks. If '1234' is entered, ACCESS GRANTED is printed, Green LED lights up, and a success melody plays. Otherwise, ACCESS DENIED shows with Red LED and a warning tone. After 3 failures, system locks for 10 seconds with a visual countdown.

## Wokwi Simulation Link
Paste your Wokwi simulation link here once you create it:
- **Simulation Link:** https://wokwi.com/projects/new/arduino-uno
