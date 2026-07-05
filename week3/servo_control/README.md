# Potentiometer-Controlled Servo with Sweep (Q25)

## Hardware Required
- 1x Arduino Uno
- 1x SG90 Servo Motor
- 1x 10kΩ Potentiometer
- 1x Push Button
- 1x 10kΩ Resistor (pull-down)

## Circuit Connections
1. Potentiometer wiper to A0 (outer pins to 5V and GND).
2. Servo Signal (orange) to pin 9, VCC to 5V, GND to GND.
3. Push Button to pin 2 with 10kΩ pull-down resistor.

## Expected Output
Rotating the potentiometer controls the servo angle (0 to 180 degrees) in real-time. Pressing the button overrides potentiometer control to perform a smooth automatic sweep (0° -> 180° -> 0°) before returning control to the pot.

## Wokwi Simulation Link
Paste your Wokwi simulation link here once you create it:
- **Simulation Link:** [Insert Wokwi Link Here](https://wokwi.com/...)
