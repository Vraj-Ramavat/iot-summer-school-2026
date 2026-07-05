# Module 3: Theory Questions (Q29 & Q30)

## Q29. Sensor Calibration & Two-Point Calibration Method

### What is Sensor Calibration?
Sensor calibration is the process of mapping a sensor's raw physical response (like analog voltage or ADC counts) to a standardized, meaningful engineering unit (such as temperature in °C, humidity in %, or distance in cm). 
- **Importance in IoT:** Raw sensor outputs vary due to manufacturing tolerances, component aging, wiring resistance, and environmental changes. Uncalibrated sensors lead to drift, offset errors, and incorrect automated decisions (e.g., watering dry soil or failing to cool an overheating server room). Calibration ensures accuracy, repeatability, and system-wide reliability.

### Calibrating an Analog Soil Moisture Sensor (0% to 100%)
An analog soil moisture sensor outputs a raw voltage (read using `analogRead()` yielding 0 to 1023 on Arduino) which is inversely proportional to moisture:
- **Air (0% moisture):** Sensor probe is dry, giving the highest resistance and maximum voltage output (e.g., raw value `850`).
- **Water (100% moisture):** Sensor probe is submerged, giving minimum resistance and lowest voltage output (e.g., raw value `290`).

To convert this raw value to a percentage:
1. Determine dry boundary ($V_{dry}$) and wet boundary ($V_{wet}$) by testing.
2. In the code, map and constrain the raw readings:
   ```cpp
   int rawVal = analogRead(A1);
   // Clamp raw reading within calibrated range to prevent outputs below 0% or above 100%
   rawVal = constrain(rawVal, wetLimit, dryLimit); 
   // Invert mapping since higher raw values correspond to dryer soil
   int moisturePercent = map(rawVal, dryLimit, wetLimit, 0, 100);
   ```

### The Two-Point Calibration Method
The two-point calibration is a mathematical method used to correct linear sensor responses. It establishes a slope ($m$) and intercept ($c$) using two known reference standards (points).

#### Calibration Procedure:
1. **Take Measurement 1 ($X_1$):** Place the sensor in a known environment standard (e.g., ice water for $0^\circ\text{C}$). Record the raw reading $Y_1$.
2. **Take Measurement 2 ($X_2$):** Place the sensor in a second known standard (e.g., boiling water for $100^\circ\text{C}$). Record the raw reading $Y_2$.
3. **Calculate Calibration Equation ($Y = mX + c$):**
   - Solve for slope $m$:
     $$m = \frac{Y_2 - Y_1}{X_2 - X_1}$$
   - Solve for offset $c$:
     $$c = Y_1 - m \cdot X_1$$
4. Apply the formula in the microcontroller code to dynamically scale any subsequent raw inputs $Y_{raw}$ back to the true physical parameter $X_{calibrated}$:
   $$X_{calibrated} = \frac{Y_{raw} - c}{m}$$

---

## Q30. The I2C Protocol in IoT Communication

### What is the I2C Protocol?
**I2C (Inter-Integrated Circuit)** is a synchronous, multi-master, multi-slave, half-duplex serial communication protocol developed by Philips (now NXP). It is widely used in IoT to connect multiple low-speed integrated circuits (sensors, EEPROMs, LCD displays) to a single host microcontroller over short distances.

```mermaid
cellulator
graph TD
    MCU[Arduino / Microcontroller (Master)]
    SDA((SDA Line))
    SCL((SCL Line))
    
    Sensor1[BMP280 Barometer (Slave 0x76)]
    Sensor2[MPU6050 Gyro (Slave 0x68)]
    LCD[LCD Display (Slave 0x27)]
    
    MCU <-->|Data| SDA
    MCU -->|Clock| SCL
    
    SDA <--> Sensor1
    SDA <--> Sensor2
    SDA <--> LCD
    
    SCL --> Sensor1
    SCL --> Sensor2
    SCL --> LCD
```

### The SDA and SCL Lines
I2C uses only **two bi-directional bus lines** pulled up to VCC with resistors (usually 4.7kΩ):
1. **SDA (Serial Data Line):** The line used to carry the address, command, and data payload bits between devices.
2. **SCL (Serial Clock Line):** The line carrying the clock synchronization pulse generated exclusively by the Master device. Data on the SDA line is sampled on the transitions of the SCL clock.

### How I2C Addressing Works
Unlike SPI which uses dedicated Chip Select (CS) wires for each device, I2C uses **software addressing**.
1. Every slave device on the bus is hardwired with a unique 7-bit (or 10-bit) address (e.g., `0x27` for LCDs, `0x68` for MPU6050).
2. To initiate communication, the Master sends a **Start Condition** followed by the 7-bit address of the target slave plus an 8th bit indicating a Read (1) or Write (0) operation.
3. All slaves monitor the bus. The slave whose address matches pulls the SDA line LOW (sends an **Acknowledge (ACK)** bit) during the 9th clock cycle.
4. Once acknowledged, data transfer proceeds byte-by-byte. Non-matching slaves ignore subsequent bus activity.

### 3 Common IoT Sensors that use I2C:
1. **MPU6050:** 6-axis Accelerometer & Gyroscope sensor (Default Address: `0x68`).
2. **BMP280 / BME280:** Barometric Pressure, Temperature, and Humidity sensor (Default Addresses: `0x76` or `0x77`).
3. **BH1750:** Digital ambient Light intensity (Lux) sensor (Default Address: `0x23`).
