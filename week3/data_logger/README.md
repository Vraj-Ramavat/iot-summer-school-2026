# Multi-Sensor Data Logger (Q24)

## Hardware Required
- 1x Arduino Uno
- 1x DHT11 Temp-Humidity Sensor
- 1x LDR (Photoresistor)
- 1x 10kΩ Resistor
- 1x HC-SR04 Ultrasonic Distance Sensor

## Circuit Connections
1. DHT11 Signal to pin 2.
2. LDR voltage divider to pin A0.
3. HC-SR04 Trig to pin 9, Echo to pin 8.

## Expected Output
Reads all 3 sensors simultaneously. Formats and prints a log output block containing raw time (ms), temperature (°C), humidity (%), light level percentage, and distance (cm) to the Serial Monitor every 5 seconds.

## Wokwi Simulation Link
Paste your Wokwi simulation link here once you create it:
- **Simulation Link:** [Insert Wokwi Link Here](https://wokwi.com/...)
