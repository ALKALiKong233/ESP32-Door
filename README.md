# Welcome!
This is a personally used toy using ESP32 as MCU and Arduino as framework.

# PIN connection

## RC522 Pin Connections

| RC522 Pin | ESP32 Pin |
|-----------|-----------|
| SDA (SS)  | GPIO 5    |
| SCK       | GPIO 18   |
| MOSI      | GPIO 23   |
| MISO      | GPIO 19   |
| IRQ       | Not used  |
| GND       | GND       |
| RST       | GPIO 22   |
| 3.3V      | 3.3V      |

## Servo Pin Connections

| Servo Pin | ESP32 Pin |
|-----------|-----------|
| 5V        | VN        |
| GND       | GND       |
| Signal    | GPIO 13   |

## Button Pin Connections

| Button Pin | ESP32 Pin |
|------------|-----------|
| VCC        | VCC       |
| GND        | GND       |
| OUT        | GPIO 2    |
