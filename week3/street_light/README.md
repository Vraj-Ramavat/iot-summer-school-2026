# Smart Street Light with LDR and PIR (Q23)

## Hardware Required
- 1x Arduino Uno
- 1x LDR (Photoresistor)
- 1x 10kΩ Resistor (for voltage divider)
- 1x PIR Motion Sensor
- 1x LED (PWM Pin 6)
- 1x 220Ω Resistor

## Circuit Connections
1. LDR in series with 10kΩ resistor across 5V and GND, middle node connected to A0.
2. PIR VCC to 5V, GND to GND, OUT to pin 2.
3. LED Anode to 220Ω to pin 6, Cathode to GND.

## Expected Output
In daylight (LDR high), LED remains OFF. At night (LDR low), the system enters Motion Detection. If PIR detects movement, LED lights up to 100% brightness for 30 seconds. If no motion is detected, it dims down to a power-saving 20% level.

## Wokwi Simulation Link
Paste your Wokwi simulation link here once you create it:
- **Simulation Link:** [Insert Wokwi Link Here](https://wokwi.com/...)
