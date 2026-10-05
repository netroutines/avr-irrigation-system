# AVR Irrigation System

Automatic irrigation system implemented in bare-metal C for the ATmega328P microcontroller, without using the Arduino framework.

## Overview

AVR Irrigation System monitors soil moisture and automatically controls a water pump through an active-low relay.

The firmware directly configures and uses the ATmega328P peripherals, including GPIO, ADC, and UART, without relying on the Arduino API.

## Features

- Soil moisture measurement using ADC2 / A2
- 16-sample averaging for more stable sensor readings
- Active-low relay control on PD5 / D5
- Automatic pump activation when dry conditions are detected
- Automatic pump shutdown when the wet threshold is reached
- Maximum pump runtime safety timeout
- Cooldown between watering cycles
- Hysteresis between dry and wet thresholds
- UART diagnostics
- Modular bare-metal AVR C codebase

## Hardware

Target hardware:

- ATmega328P
- 16 MHz clock
- Arduino Uno-compatible development board
- CH340 USB-to-serial interface
- Soil moisture sensor
- 5 V active-low relay module
- Submersible water pump

The complete sensor, relay, and pump control chain has been tested on the target hardware.

## Project Structure

```text
avr-irrigation-system/
├── include/
│   ├── adc.h
│   ├── config.h
│   ├── relay.h
│   ├── soil_sensor.h
│   └── uart.h
├── src/
│   ├── adc.c
│   ├── main.c
│   ├── relay.c
│   ├── soil_sensor.c
│   └── uart.c
├── .gitignore
├── platformio.ini
└── README.md
```

## Development Environment

The project is built using PlatformIO with the AVR GCC toolchain.

No Arduino framework is used.

## Build and Upload

Build the firmware from the project directory:

```shell
pio run
```

Upload the firmware to the ATmega328P:

```shell
pio run --target upload
```

PlatformIO usually detects the serial port used by the development board automatically.

## Serial Monitor

UART diagnostics are available at `9600` baud.

Start the PlatformIO serial monitor from the project directory:

```shell
pio device monitor
```

Press `Ctrl+C` to close the serial monitor.
