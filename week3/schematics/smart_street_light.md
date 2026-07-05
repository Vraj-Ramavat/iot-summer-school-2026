# Q23. Smart Street Light Circuit Diagram (Schematic)

This document describes the circuit connections for the Smart Street Light controller using an Arduino UNO, an LDR (Light Dependent Resistor), a PIR motion sensor, a PWM-controlled LED, and resistors.

---

## 1. Pin Mapping Table

| Component | Component Pin | Arduino Uno Pin | Description |
| :--- | :--- | :--- | :--- |
| **LDR Circuit** | Analog Signal Output | **A0** | Analog input representing ambient light levels |
| **PIR Sensor** | OUT (Signal) | **D2** | Digital input triggering high on motion detection |
| **PIR Sensor** | VCC / GND | **5V / GND** | Power rails |
| **LED** | Anode (+) | **D6 (PWM)** | PWM-controlled output for brightness adjustments |
| **LED** | Cathode (-) | **GND** | Connected via 220Ω current-limiting resistor |

---

## 2. ASCII Schematic Diagram

```text
                  +-----------------------------------+
                  |            ARDUINO UNO            |
                  |                                   |
                  |               5V  GND   A0   D2   D6 (PWM)
                  +---------------+----+----+----+----+
                                  |    |    |    |    |
       +--------------------------+    |    |    |    |
       |                               |    |    |    |
       |     +-------------------------+    |    |    |
       |     |                              |    |    |
       |     |       +----------------------+    |    |
       |     |       |                           |    |
    +--+-----+-------+---+                       |    |
    |  VCC  GND     OUT  |                       |    |
    |                    |                       |    |
    |     PIR Sensor     |                       |    |
    +--------------------+                       |    |
                                                 |    |
                                                 |    |
                         +--------[ 10k Resistor ]----+
                         |                       |
                  5V ----+---[ LDR Sensor ]------+---- GND
                                                 |
                                                 |
                                                 |
                                         +-------+
                                         |
                                  [ 220 Ohm Resistor ]
                                         |
                                         +----[ LED Anode (+) ]
                                                [ LED Cathode (-) ] ---- GND
```

---

## 3. Circuit Hookup Steps

1. **Power Breadboard Rails:**
   - Connect Arduino **5V** to the positive (+) rail of the breadboard.
   - Connect Arduino **GND** to the negative (-) rail of the breadboard.

2. **LDR Sensor Setup (Voltage Divider):**
   - Connect one leg of the **LDR** to the **5V** rail.
   - Connect the other leg of the LDR to Arduino Analog Pin **A0**.
   - Connect a **10kΩ resistor** from Arduino Analog Pin **A0** to the **GND** rail. (This forms a voltage divider where the output voltage drops as the light level decreases).

3. **PIR Sensor Setup:**
   - Connect the **VCC** pin of the PIR to the **5V** rail.
   - Connect the **GND** pin of the PIR to the **GND** rail.
   - Connect the **OUT** pin of the PIR to Arduino Digital Pin **D2**.

4. **LED Setup:**
   - Connect Arduino PWM Pin **D6** to a **220Ω current-limiting resistor**.
   - Connect the other end of the resistor to the **Anode** (longer leg) of the **LED**.
   - Connect the **Cathode** (shorter leg) of the LED to the **GND** rail.
