# Thermostat Relay Control Simulation (Q27)

## Hardware Required
- 1x Arduino Uno
- 1x DHT11 Temperature Sensor
- 1x 5V Relay Module
- 1x LED (representing simulated AC appliance)
- 1x 220Ω Resistor
- 1x Push Button
- 1x 10kΩ Resistor (pull-down)

## Circuit Connections
1. DHT11 Signal to pin 2.
2. Override Button to pin 3 with a 10kΩ pull-down resistor.
3. Relay signal IN to pin 8.
4. LED connected across Relay COM and NO terminals with a 220Ω resistor and 5V supply.

## Expected Output
Operates as a thermostat with hysteresis: Relay turns ON (AC ON) if temperature exceeds 32.0°C and turns OFF (AC OFF) when temperature falls below 28.0°C. Pressing the button immediately overrides the system state.

## Wokwi Simulation Link
Paste your Wokwi simulation link here once you create it:
- **Simulation Link:** [Insert Wokwi Link Here](https://wokwi.com/...)
