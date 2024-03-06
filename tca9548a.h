/*
 * File:   TCA9548A.h
 * Author: Bintang Cahya
 *
 * Description:
 * Header file for controlling TCA9548A I2C Multiplexer.
 */

#ifndef INC_TCA9548A_H_
#define INC_TCA9548A_H_

#include "main.h"

typedef struct {
    I2C_HandleTypeDef *hi2c;	// I2C HandleTypeDef Pointer
    uint8_t address;			// TCA9548A Address
    uint8_t channels;			// Channel Configuration Data
} TCA9548A_HandleTypeDef;

/****************************************************************************************************************
 * Initialize the TCA9548A device and verify its status
 ****************************************************************************************************************/
HAL_StatusTypeDef TCA_Init(TCA9548A_HandleTypeDef *_dev_typedef, I2C_HandleTypeDef *_dev_hi2c, uint8_t _dev_addr);


/****************************************************************************************************************
 * Open the specified I2C bus channel
 ****************************************************************************************************************/
HAL_StatusTypeDef TCA_OpenChannel(TCA9548A_HandleTypeDef *_dev_typedef, uint8_t _channel);


/****************************************************************************************************************
 * Close the specified I2C bus channel
 ****************************************************************************************************************/
HAL_StatusTypeDef TCA_CloseChannel(TCA9548A_HandleTypeDef *_dev_typedef, uint8_t _channel);


/****************************************************************************************************************
 * Open the selected channel and close others
 ****************************************************************************************************************/
HAL_StatusTypeDef TCA_SelectChannel(TCA9548A_HandleTypeDef *_dev_typedef, uint8_t _channel);


/****************************************************************************************************************
 * Set the state of multiple channels simultaneously
 ****************************************************************************************************************/
HAL_StatusTypeDef TCA_SetMultipleChannels(TCA9548A_HandleTypeDef *_dev_typedef, uint8_t _state_data);


/****************************************************************************************************************
 * Open all channels
 ****************************************************************************************************************/
HAL_StatusTypeDef TCA_OpenAllChannels(TCA9548A_HandleTypeDef *_dev_typedef);


/****************************************************************************************************************
 * Close all channels
 ****************************************************************************************************************/
HAL_StatusTypeDef TCA_CloseAllChannels(TCA9548A_HandleTypeDef *_dev_typedef);


/****************************************************************************************************************
 * Get the specified channel status
 ****************************************************************************************************************/
uint8_t TCA_GetChannelStatus(TCA9548A_HandleTypeDef *_dev_typedef, uint8_t _channel);


/****************************************************************************************************************
 * Get the all channel status
 ****************************************************************************************************************/
uint8_t TCA_GetAllChannelStatus(TCA9548A_HandleTypeDef *_dev_typedef);

#endif /* INC_TCA9548A_H_ */
