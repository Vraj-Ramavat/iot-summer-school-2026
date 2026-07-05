# PWM Fading Night Light and Morse SOS (Q17)

## Hardware Required
- 1x Arduino Uno
- 1x LED (connected to PWM Pin 9)
- 1x 220Ω Resistor
- 1x Push Button
- 1x 10kΩ Resistor (pull-down)

## Circuit Connections
1. LED Anode to 220Ω resistor to PWM pin 9, Cathode to GND.
2. Mode Toggle Button to 5V and Pin 2, with a 10kΩ pull-down to GND.

## Expected Output
Pressing the button cycles between three modes:
1. Slow breathing (3-second sine-wave fade cycle)
2. Fast pulse (0.5-second sine-wave cycle)
3. Morse Code SOS pattern (... --- ...) flashed continuously without blocking processor execution.

## Wokwi Simulation Link
Paste your Wokwi simulation link here once you create it:
- **Simulation Link:** [Insert Wokwi Link Here](https://wokwi.com/...)
