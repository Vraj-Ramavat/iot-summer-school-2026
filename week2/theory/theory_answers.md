# Module 2: Theory Questions (Q11 - Q13, Q19 - Q20)

## Q11. Draw and label a 4-layer IoT architecture diagram

The IoT ecosystem is typically represented in a 4-layer architecture. Each layer serves a specific purpose, transferring physical data from the edge to the end application.

### Architecture Diagram (Mermaid Flowchart)
```mermaid
graph TD
    subgraph Layer4 [4. Application Layer]
        app[Smart Home App / Dashboard / Cloud UI / Industrial SCADA]
    end

    subgraph Layer3 [3. Processing Layer]
        db[(SQL/NoSQL Databases)]
        analytics[Edge Analytics / AI Inference]
        cloud[Cloud Broker / MQTT Server / Node-Red]
    end

    subgraph Layer2 [2. Network Layer]
        gw[Gateways / Routers]
        proto[Wi-Fi / LoRaWAN / 4G-5G / Zigbee]
    end

    subgraph Layer1 [1. Perception Layer]
        sensors[Sensors: DHT11, LDR, HC-SR04]
        actuators[Actuators: Relays, Servos, Buzzer]
        rfid[RFID / Transducers]
    end

    sensors -->|Raw Data| gw
    actuators <--|Control Signals| gw
    gw -->|MQTT / HTTP Protocols| cloud
    cloud -->|Data Logging| db
    db -->|API / WebSockets| app
    analytics -->|Alerts| app
```

### Layer Definitions and Examples
1. **Perception Layer (Physical/Sensor Layer):** Captures physical parameters from the environment and executes physical operations.
   - *Example Devices:* DHT11 (Temperature & Humidity Sensor), PIR Sensor, Servos.
2. **Network Layer (Transmission Layer):** Transmits data gathered by sensors to processing systems.
   - *Example Technologies:* Wi-Fi (ESP8266), LoRaWAN gateways, 5G Cellular.
3. **Processing Layer (Middleware/Analytics Layer):** Accumulates, filters, processes, and stores data. Runs algorithms and manages device states.
   - *Example Technologies:* MQTT broker (e.g., Mosquitto), InfluxDB, AWS IoT Core.
4. **Application Layer (User Interface Layer):** Presents the processed data to the end-user and allows remote command inputs.
   - *Example Technologies:* Blynk Dashboard, Home Assistant, Custom Web/Mobile App.

---

## Q12. Microcontroller vs Microprocessor Comparison Table

| Parameter | Microcontroller (Arduino UNO) | Microprocessor (Raspberry Pi) |
| :--- | :--- | :--- |
| **CPU Speed** | 16 MHz (Slow, single-threaded) | 1.5 GHz - 2.4 GHz (Fast, multi-core) |
| **On-chip RAM** | 2 KB SRAM (Very limited) | 2 GB / 4 GB / 8 GB LPDDR4 (Abundant) |
| **On-chip Flash** | 32 KB Flash memory (Internal storage) | None (Requires external MicroSD Card, e.g., 32GB+) |
| **Operating System** | None (Bare-metal; code runs directly) | Full OS (e.g., Linux / Raspberry Pi OS) |
| **Typical Use Case** | Reading analog sensors, controlling relays, real-time motor control | Edge AI, computer vision, running web servers, database aggregation |
| **Power Consumption** | Extremely Low (~100-200 mW, fits battery operations) | Moderate to High (~3W - 15W, needs active power supply) |

---

## Q13. Arduino Pin Types & Real-World IoT Use Cases

1. **Digital Input:** Reads binary states (HIGH / LOW or 5V / 0V).
   - *IoT Use Case:* A **magnetic door sensor** on an IoT home security system to detect if a window is open (HIGH) or closed (LOW).
2. **Digital Output:** Writes binary states (HIGH / LOW).
   - *IoT Use Case:* An **IoT water irrigation pump** controlled via a relay connected to pin 8. The MCU writes HIGH to turn the pump on.
3. **Analog Input:** Reads continuous voltage (0V to 5V) and maps it to a digital range (0 to 1023) using a 10-bit ADC.
   - *IoT Use Case:* A **soil moisture sensor** reading soil dryness in smart agriculture.
4. **PWM Output (Pulse Width Modulation):** Simulates analog output levels using digital pulses with varying duty cycles (0 to 255).
   - *IoT Use Case:* A **smart room light dimmer** fading a high-power LED dynamically.
5. **I2C (Inter-Integrated Circuit) & SPI (Serial Peripheral Interface) Pins:** Dedicated communication buses (SDA/SCL for I2C, MOSI/MISO/SCK/SS for SPI).
   - *IoT Use Case:* Reading ambient atmospheric pressure and altitude from a **BME280 sensor** via I2C or communicating with an **MFRC522 RFID reader** via SPI for automated access control.

---

## Q19. `analogWrite()` vs `analogRead()`, and Pulse Width Modulation (PWM)

### Difference between `analogWrite()` and `analogRead()`
* **`analogRead()`** is an **input** operation. It uses the Arduino's internal Analog-to-Digital Converter (ADC) to read a voltage between 0V and 5V from an analog pin (A0-A5) and outputs a value from **0 to 1023**.
  - *IoT Example:* Reading raw moisture levels from a resistive probe sensor.
* **`analogWrite()`** is an **output** operation. It does **not** output a true analog voltage; rather, it uses Pulse Width Modulation (PWM) on support pins (3, 5, 6, 9, 10, 11) to control average power using values from **0 to 255**.
  - *IoT Example:* Controlling the speed of an exhaust fan based on temperature.

### What is PWM and why is it used?
**Pulse Width Modulation (PWM)** is a method of generating pseudo-analog outputs using digital pins. By rapidly toggling a pin between 5V (ON) and 0V (OFF), we create a square wave. The percentage of time the signal is HIGH during one cycle is called the **Duty Cycle**. 
- A **25% duty cycle** delivers 25% of the total average power.
- A **100% duty cycle** delivers 100% power (constant 5V).

It is used in IoT because producing true variable analog voltages requires complex and expensive DAC hardware. PWM provides an efficient, digital way to control brightness, motor speeds, and thermal elements without power losses.

---

## Q20. `setup()`, `loop()`, Blocking Delay vs Non-Blocking `millis()`

### Explanation of `setup()` and `loop()`
* **`setup()`** executes exactly once when the Arduino boots up or resets. It initializes pin configurations (using `pinMode()`), starts serial communications (`Serial.begin()`), and instantiates sensors/peripherals.
* **`loop()`** executes sequentially and infinitely as long as the board has power. It contains the main execution logic.

### Effect of a long `delay()` inside `loop()`
A `delay(X)` function is **blocking**. When called, the MCU enters a busy-wait loop, halting all other processing for the duration of `X` milliseconds. 
- **Sensor Responsiveness:** If you have a `delay(5000)` (5 seconds) to wait between sensor logs, the MCU is completely blind for those 5 seconds. If a user presses a panic button, or a water level sensor triggers a flood alarm, the Arduino will **not detect it** until the delay finishes. This creates an unresponsive and unreliable system.

### Non-Blocking Alternative: The `millis()` approach
The non-blocking alternative uses the internal timer `millis()`, which returns the number of milliseconds elapsed since the Arduino board began running.
Instead of pausing the CPU, we store the timestamp of the last executed action and check if the required time interval has elapsed in each loop cycle.

**Example structure:**
```cpp
unsigned long previousMillis = 0;
const long interval = 1000; // 1 second interval

void loop() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // update time
    // Read sensor and log data here (non-blocking)
  }
  
  // Other fast-running tasks, button checks, etc., run instantly here!
}
```
Using this pattern, the Arduino loop runs thousands of times per second, checking inputs constantly and executing timed tasks only when necessary.
