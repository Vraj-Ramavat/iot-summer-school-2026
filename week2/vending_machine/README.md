# Vending Machine Finite State Machine (Q18)

## Hardware Required
- 1x Arduino Uno
- 3x LEDs (Red - IDLE, Yellow - READY, Green - DISPENSE)
- 3x 220Ω Resistors
- 3x Push Buttons (Coin, Select, Cancel)
- 3x 10kΩ Resistors (pull-downs)

## Circuit Connections
1. Red, Yellow, Green LEDs to pins 10, 9, 8 respectively (with 220Ω resistors to GND).
2. Coin, Select, Cancel buttons connected to Pins 2, 3, 4 (with 10kΩ pull-downs).

## Expected Output
Simulates a vending system. RED LED is active in IDLE state. Inserting a coin transitions to COIN_INSERTED (YELLOW LED active). Selecting an item transitions to ITEM_SELECTED (both Red and Yellow active) for 1.5 seconds, then enters DISPENSING (Green LED flashes for 3 seconds) before returning to IDLE. Cancel refunds and returns to IDLE.

## Wokwi Simulation Link
Paste your Wokwi simulation link here once you create it:
- **Simulation Link:** [Insert Wokwi Link Here](https://wokwi.com/...)
