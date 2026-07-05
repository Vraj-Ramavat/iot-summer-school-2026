# Q21: Environmental Monitoring Station (DHT11)

This project reads ambient temperature and relative humidity from a DHT11 sensor and prints the values to the Serial Monitor.

## External Libraries Used
* **Library Name:** DHT sensor library by Adafruit
* **Version:** 1.4.6
* **Dependency:** Adafruit Unified Sensor library (Version 1.1.14)

---

## Pin Configurations
* **DHT11 Data Pin:** Pin 2
* **Red LED:** Pin 11 (High Temp > 35°C or High Humidity > 80% Alarm)
* **Green LED:** Pin 10 (Normal climate range)

---

## Log Output Format
Data is logged to the Serial Monitor every 2 seconds in CSV format:
```text
timestamp_ms,temperature_C,temperature_F,humidity_percent
2000,28.4,83.1,65.2
```

## Wokwi Simulation Link
Paste your Wokwi simulation link here once you create it:
- **Simulation Link:** [Insert Wokwi Link Here](https://wokwi.com/...)
