# DC Motor Speed & Direction Control (L298N) (Q26)

## Hardware Required
- 1x Arduino Uno
- 1x L298N DC Motor Driver Module (or L293D)
- 1x DC Motor
- 1x 10kΩ Potentiometer
- 2x Push Buttons (Direction, State)
- 2x 10kΩ Resistors (pull-downs)
- External battery supply (e.g. 4x AA / 9V)

## Circuit Connections
1. Potentiometer wiper to A0.
2. Buttons to pin 2 (Direction) and pin 3 (Start/Stop) with 10kΩ pull-downs.
3. ENA to pin 6, IN1 to pin 7, IN2 to pin 8.
4. Motor outputs to DC Motor, driver GND common to Arduino GND, external battery supplying motor voltage.

## Expected Output
Allows full speed adjustments using the potentiometer mapped to PWM duty cycles. Button 3 toggles motor state (RUNNING/STOPPED). Button 2 toggles motor rotation direction (FORWARD/REVERSE) with status updates printed to Serial.

## Wokwi Simulation Link
Paste your Wokwi simulation link here once you create it:
- **Simulation Link:** [Insert Wokwi Link Here](https://wokwi.com/...)
