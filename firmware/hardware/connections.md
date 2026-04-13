# 🔌 Hardware Connections

## ESP32 ↔ INMP441
- VDD → 3.3V
- GND → GND
- WS → GPIO 15
- SCK → GPIO 4
- SD → GPIO 32
- L/R → GND

## ESP32 ↔ L298N
- IN1 → GPIO 26
- IN2 → GPIO 27
- IN3 → GPIO 14
- IN4 → GPIO 12
- ENA → GPIO 25
- ENB → GPIO 33

## Power
- Battery → L298N
- GND must be common
