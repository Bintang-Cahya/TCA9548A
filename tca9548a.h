/*
 * File:   TCA9548A.h
 * Author: Bintang Cahya
 *
 * Description:
 * Header file for controlling TCA9548A I2C Multiplexer.
 */

#ifndef TCA9548A_H
#define TCA9548A_H

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TCA9548A_TIMEOUT 100

typedef enum
{
    TCA_CHANNEL_0 = 0,
    TCA_CHANNEL_1,
    TCA_CHANNEL_2,
    TCA_CHANNEL_3,
    TCA_CHANNEL_4,
    TCA_CHANNEL_5,
    TCA_CHANNEL_6,
    TCA_CHANNEL_7
} TCA_Channel_t;

typedef struct
{
    I2C_HandleTypeDef *hi2c;	// I2C HandleTypeDef Pointer

    GPIO_TypeDef *reset_port;	// Reset pin port
    uint16_t reset_pin;			// Reset pin number

    uint8_t address;			// TCA9548A Address
    uint8_t channels;			// Channel Configuration Data

} TCA9548A_HandleTypeDef;


/****************************************************************************************************************
 * Initialize the TCA9548A device and verify its status
 ****************************************************************************************************************/
HAL_StatusTypeDef TCA_Init(TCA9548A_HandleTypeDef *dev, I2C_HandleTypeDef *hi2c, GPIO_TypeDef *reset_port, uint16_t reset_pin, uint8_t address);


/****************************************************************************************************************
 * Resets TCA9548A
 ****************************************************************************************************************/
HAL_StatusTypeDef TCA_Reset(TCA9548A_HandleTypeDef *dev);


/****************************************************************************************************************
 * Open the specified I2C bus channel
 ****************************************************************************************************************/
HAL_StatusTypeDef TCA_OpenChannel(TCA9548A_HandleTypeDef *dev, TCA_Channel_t channel);


/****************************************************************************************************************
 * Close the specified I2C bus channel
 ****************************************************************************************************************/
HAL_StatusTypeDef TCA_CloseChannel(TCA9548A_HandleTypeDef *dev, TCA_Channel_t channel);


/****************************************************************************************************************
 * Open the selected channel and close others
 ****************************************************************************************************************/
HAL_StatusTypeDef TCA_SelectChannel(TCA9548A_HandleTypeDef *dev, TCA_Channel_t channel);


/****************************************************************************************************************
 * Set the state of multiple channels simultaneously
 ****************************************************************************************************************/
HAL_StatusTypeDef TCA_SetMultipleChannels(TCA9548A_HandleTypeDef *dev, uint8_t state_data);


/****************************************************************************************************************
 * Open all channels
 ****************************************************************************************************************/
HAL_StatusTypeDef TCA_OpenAllChannels(TCA9548A_HandleTypeDef *dev);


/****************************************************************************************************************
 * Close all channels
 ****************************************************************************************************************/
HAL_StatusTypeDef TCA_CloseAllChannels(TCA9548A_HandleTypeDef *dev);


/****************************************************************************************************************
 * Get the specified channel status
 ****************************************************************************************************************/
uint8_t TCA_GetChannelStatus(TCA9548A_HandleTypeDef *dev, TCA_Channel_t channel);


/****************************************************************************************************************
 *  * Get status of all channels
 ****************************************************************************************************************/
uint8_t TCA_GetAllChannelStatus(TCA9548A_HandleTypeDef *dev);


#ifdef __cplusplus
}
#endif

#endif /* TCA9548A_H */
