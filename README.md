![Static Badge](https://img.shields.io/badge/Board-STM32-yellow?logo=stmicroelectronics)
![Version](https://img.shields.io/badge/version-v1.1.0-yellow?logo=github)

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
2. Use `TCA_Reset()` to reset TCA9548A IC
3. Use `TCA_OpenChannel()` or `TCA_CloseChannel()` to open or close specific I2C bus channels.
4. Use `TCA_SelectChannel()` to select a particular channel while closing others.
5. Use `TCA_SetMultipleChannels()` to set the state of multiple channels simultaneously.
6. Use `TCA_OpenAllChannels()` or `TCA_CloseAllChannels()` to open or close all channels at once.
7. Use `TCA_GetChannelStatus()` or `TCA_GetAllChannelStatus()` to get the status of specific or all channels.

## Library Example

### Include Header File

```c
#include "tca9548a.h"
```

---

### Create TCA9548A Handle

```c
TCA9548A_HandleTypeDef tca9548a;
```

---

### Initialize TCA9548A

#### With RESET Pin

```c
TCA_Init(
    &tca9548a,
    &hi2c1,
    GPIOB,
    GPIO_PIN_5,
    TCA9548A_DEFAULT_ADDRESS
);
```

#### Without RESET Pin

```c
TCA_Init(
    &tca9548a,
    &hi2c1,
    NULL,
    0,
    TCA9548A_DEFAULT_ADDRESS
);
```

---

### Reset TCA9548A

```c
TCA_Reset(&tca9548a);
```

---

### Open Specific Channel

```c
TCA_OpenChannel(&tca9548a, TCA_CHANNEL_0);
```

---

### Close Specific Channel

```c
TCA_CloseChannel(&tca9548a, TCA_CHANNEL_0);
```

---

### Select Single Channel

This function automatically closes all other channels.

```c
TCA_SelectChannel(&tca9548a, TCA_CHANNEL_2);
```

---

### Open Multiple Channels

Open channel 0, 2, and 4 simultaneously.

```c
TCA_SetMultipleChannels(&tca9548a, 0b00010101);
```

---

### Open All Channels

```c
TCA_OpenAllChannels(&tca9548a);
```

---

### Close All Channels

```c
TCA_CloseAllChannels(&tca9548a);
```

---

### Get Specific Channel Status

```c
uint8_t status;

status = TCA_GetChannelStatus(
    &tca9548a,
    TCA_CHANNEL_1
);
```

---

### Get All Channel Status

```c
uint8_t all_status;

all_status = TCA_GetAllChannelStatus(&tca9548a);
```

Example result:

```c
0b00000101
```

Meaning:
- Channel 0 = Open
- Channel 2 = Open
- Other channels = Closed

---

## Contribution
Contributions to this library are welcome. Feel free to fork the repository, make your changes, and submit a pull request or open an issue. Your contributions to this library are highly valued and appreciated.

## License

This library is licensed under MIT Lisence. Check the `LICENSE` file for details.
