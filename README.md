![Static Badge](https://img.shields.io/badge/Board-STM32-yellow?logo=stmicroelectronics)
[![GitHub Release](https://img.shields.io/github/release/Bintang-Cahya/TCA9548A.svg?logo=github&label=Version&color=yellow)](https://github.com/Bintang-Cahya/TCA9548A/releases/tag/v1.0.0?target="_blank")

# TCA9548A Library

This library provides functions to control the TCA9548A I2C multiplexer switch on STM32 microcontrollers.

## Introduction

The TCA9548A is an I2C multiplexer switch that allows you to control multiple I2C devices using a single I2C bus. This library simplifies the usage of the TCA9548A switch on STM32 microcontrollers.

## Features

- Initialize the TCA9548A device and verify its status
- Open and close specific I2C bus channels
- Select a particular channel while closing others
- Set the state of multiple channels simultaneously
- Open or close all channels at once
- Get the status of specific or all channels

## Installation

1. Clone or download this repository.
2. Copy the `TCA9548A` folder into your STM32 project's `Libraries` directory.
3. Include the library header file in your project:
   ```c
   #include "TCA9548A.h"
   ```
   
## Library Functions

1. Initialize the TCA9548A device with `TCA_Init()` function.
2. Use `TCA_OpenChannel()` or `TCA_CloseChannel()` to open or close specific I2C bus channels.
3. Use `TCA_SelectChannel()` to select a particular channel while closing others.
4. Use `TCA_SetMultipleChannels()` to set the state of multiple channels simultaneously.
5. Use `TCA_OpenAllChannels()` or `TCA_CloseAllChannels()` to open or close all channels at once.
6. Use `TCA_GetChannelStatus()` or `TCA_GetAllChannelStatus()` to get the status of specific or all channels.

## Contribution
Contributions to this library are welcome. Feel free to fork the repository, make your changes, and submit a pull request or open an issue. Your contributions to this library are highly valued and appreciated.

## License

This library is licensed under MIT Lisence. Check the `LICENSE` file for details.
