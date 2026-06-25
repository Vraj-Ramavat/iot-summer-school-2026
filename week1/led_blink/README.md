# Week 1: Potentiometer-Controlled LED Blink

## Project Title
Potentiometer-Controlled LED Blink Rate with Serial Logging

## Hardware Required
- 1 x Arduino UNO R3 (or Nano/Mega)
- 1 x LED (Red/Green/Blue)
- 1 x 220Ω Resistor (for LED current limiting)
- 1 x 10kΩ Potentiometer (for analog input speed control)
- 1 x Breadboard
- Jumper Wires (M-M)
- USB Type-B programming cable

## Circuit Diagram Description
1. **LED Connection:**
   - Connect the anode (longer leg) of the LED to Arduino **Digital Pin 13**.
   - Connect the cathode (shorter leg) of the LED to one end of the **220Ω resistor**.
   - Connect the other end of the 220Ω resistor to one of the **GND** pins on the Arduino.
2. **Potentiometer Connection:**
   - Connect the left terminal (Pin 1) of the potentiometer to Arduino **5V**.
   - Connect the middle terminal (wiper / Pin 2) of the potentiometer to Arduino **Analog Pin A0**.
   - Connect the right terminal (Pin 3) of the potentiometer to Arduino **GND**.

## How to Upload Code
1. Open the [led_blink.ino](file:///H:/IOT-SUMMER-SCHOOL-2026/week1/led_blink/led_blink.ino) sketch in the **Arduino IDE**.
2. Connect your Arduino board to your computer using the USB cable.
3. Select the correct board type: go to **Tools > Board > Arduino AVR Boards > Arduino Uno**.
4. Select the correct port: go to **Tools > Port** and select the port associated with your Arduino (e.g., COM3, COM4, or `/dev/ttyACM0`).
5. Click the **Verify** button (checkmark icon) to compile the code and ensure there are no errors.
6. Click the **Upload** button (right-pointing arrow icon) to flash the firmware onto the Arduino.
7. Open the **Serial Monitor** (**Tools > Serial Monitor**) and set the baud rate to **9600** to observe the logs.

## Expected Output
- The LED on pin 13 will blink continuously.
- Rotating the potentiometer wiper will change the blink frequency (speeding it up when turned towards 5V, slowing it down when turned towards GND).
- The Serial Monitor will print logs in the following format:
  ```text
  Blink count: 1 | Pot Raw: 512 | Delay: 1050 ms
  Blink count: 2 | Pot Raw: 256 | Delay: 575 ms
  ```

## Troubleshooting Tips
1. **LED does not light up:** Double-check the polarity of the LED. The longer leg (anode) must connect to pin 13, and the shorter leg (cathode) to GND. Also, ensure the resistor is connected properly.
2. **Blink rate does not change:** Verify that the potentiometer middle pin is connected to **A0** (not digital pin 0) and the outer pins are securely connected to 5V and GND.
3. **No output in Serial Monitor:** Ensure the Serial Monitor baud rate is set to **9600 baud** in the bottom-right dropdown of the window.
4. **Upload fails:** Check if the correct board model and COM Port are selected in the Arduino IDE. Try unplugging and re-plugging the USB cable.
