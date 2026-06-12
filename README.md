# Bare-Metal I2C Maze Game on STM32 Black Pill

A simple maze game built from scratch using **bare-metal STM32 programming**. The project uses an **SSD1306 0.96" OLED display** connected via **I2C** and an **MPU6050 IMU sensor** to control movement by tilting the board.

## Features

* Bare-metal STM32 development (no HAL, no STM32Cube libraries)
* Custom I2C driver implementation
* SSD1306 OLED driver
* MPU6050 sensor driver
* Real-time tilt-based player movement
* Maze rendering on OLED display
* Collision detection with maze walls
* Goal/finish point detection
* Lightweight and optimized for embedded systems

## Hardware

| Component | Description                                  |
| --------- | -------------------------------------------- |
| MCU       | STM32 Black Pill (STM32F401CC / STM32F411CE) |
| Display   | 0.96" SSD1306 OLED (I2C)                     |
| Sensor    | MPU6050 Accelerometer + Gyroscope            |
| Power     | USB                                          |

## Connections

### SSD1306 OLED

| OLED | STM32   |
| ---- | ------- |
| VCC  | 3.3V    |
| GND  | GND     |
| SDA  | I2C SDA |
| SCL  | I2C SCL |

### MPU6050

| MPU6050 | STM32   |
| ------- | ------- |
| VCC     | 3.3V    |
| GND     | GND     |
| SDA     | I2C SDA |
| SCL     | I2C SCL |

Both devices share the same I2C bus.

## Project Structure

```text
.
├── Core
│   ├── startup/
│   ├── system/
│   └── main.c
│
├── Drivers
│   ├── i2c.c
│   ├── i2c.h
│   ├── ssd1306.c
│   ├── ssd1306.h
│   ├── mpu6050.c
│   └── mpu6050.h
│
├── Game
│   ├── maze.c
│   ├── maze.h
│   ├── player.c
│   └── player.h
│
└── README.md
```

## How It Works

1. STM32 initializes the I2C peripheral.
2. SSD1306 OLED is configured and cleared.
3. MPU6050 is initialized and calibrated.
4. Accelerometer data is read periodically.
5. Board tilt determines player movement direction.
6. Collision detection prevents movement through walls.
7. Reaching the exit completes the maze.

## Learning Objectives

This project demonstrates:

* Register-level STM32 programming
* I2C protocol implementation
* Sensor interfacing
* OLED graphics rendering
* Embedded game development
* Real-time input processing
* State-machine based design

## Future Improvements

* Multiple maze levels
* Random maze generation
* High score tracking
* Buzzer for sound effects
* Menu system
* Gyroscope-assisted controls
* EEPROM save support

## Build & Flash

Compile using:

```bash
arm-none-eabi-gcc
```

Flash using:

```bash
st-flash write firmware.bin 0x8000000
```

or

```bash
openocd
```

## License

MIT License

## Author

Sadman Sakib

Embedded Systems | Bare-Metal Programming | STM32 Development
