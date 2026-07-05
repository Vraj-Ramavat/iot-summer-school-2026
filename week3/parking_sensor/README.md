# Ultrasonic Parking Distance Sensor (Q22)

## Hardware Required
- 1x Arduino Uno
- 1x HC-SR04 Ultrasonic Distance Sensor
- 3x LEDs (Red, Yellow, Green)
- 3x 220Ω Resistors
- 1x Buzzer

## Circuit Connections
1. HC-SR04 VCC to 5V, GND to GND, Trig to pin 9, Echo to pin 8.
2. Green, Yellow, Red LEDs to pins 10, 11, 12 (with 220Ω resistors to GND).
3. Buzzer positive to Pin 7, negative to GND.

## Expected Output
Calculates distance continuously. Outputs logs and controls alarms:
- Distance > 50cm: Safe (Green LED ON)
- Distance 20-50cm: Warning (Yellow LED ON, Buzzer beeps slow 500ms)
- Distance 10-20cm: Danger (Red LED ON, Buzzer beeps fast 200ms)
- Distance < 10cm: Critical (All LEDs flash, Buzzer alarms continuously)

## Wokwi Simulation Link
Paste your Wokwi simulation link here once you create it:
- **Simulation Link:** [Insert Wokwi Link Here](https://wokwi.com/...)
