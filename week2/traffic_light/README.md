# Traffic Light Controller with Pedestrian Override (Q14)

## Hardware Required
- 1x Arduino Uno
- 3x LEDs (Red, Yellow, Green)
- 3x 220Ω Resistors
- 1x Push Button
- 1x 10kΩ Resistor (button pull-down)

## Circuit Connections
1. Red LED Anode to 220Ω to pin 10, Cathode to GND.
2. Yellow LED Anode to 220Ω to pin 9, Cathode to GND.
3. Green LED Anode to 220Ω to pin 8, Cathode to GND.
4. Push Button connected to 5V and Pin 7, with a 10kΩ pull-down resistor to GND.

## Expected Output
The traffic light will cycle normally: Red (5s) -> Yellow (2s) -> Green (4s). When the button on pin 7 is pressed, the system instantly switches to Red for 8 seconds to allow pedestrians to cross.

## Wokwi Simulation Link
Paste your Wokwi simulation link here once you create it:
- **Simulation Link:** [Insert Wokwi Link Here](https://wokwi.com/...)
