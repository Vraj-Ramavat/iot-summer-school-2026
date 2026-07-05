# Serial Command Interface (Q16)

## Hardware Required
- 1x Arduino Uno
- Built-in LED (Pin 13)

## Circuit Connections
No external components required. Uses the built-in LED on Digital Pin 13.

## Expected Output
Allows command inputs via the Serial Monitor (9600 baud):
- 'LED_ON' -> Turns LED ON
- 'LED_OFF' -> Turns LED OFF
- 'BLINK_X' -> Blinks LED X times (where X is 1-9)
- 'STATUS' -> Returns system and counter information
- 'RESET' -> Resets total blink counters
- Non-matching commands return 'ERROR: Unknown command'.

## Wokwi Simulation Link
Paste your Wokwi simulation link here once you create it:
- **Simulation Link:** [Insert Wokwi Link Here](https://wokwi.com/...)
