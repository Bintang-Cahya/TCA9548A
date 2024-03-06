
#include "tca9548a.h"

/*
 * @brief	Initialize the device and verify its status
 *
 * @param   _dev_typedef		Pointer to the device handle structure
 * @param   _dev_hi2c	        Pointer to a I2C_HandleTypeDef structure
 * @param   _dev_addr	        TCA9548A address, automatically shifted by the function
 * @return  HAL_StatusTypeDef   Status of the initialization
 *                              - HAL_OK: Success
 *                              - HAL_ERROR: Error occurred during initialization
 */
HAL_StatusTypeDef TCA_Init(TCA9548A_HandleTypeDef *_dev_typedef, I2C_HandleTypeDef *_dev_hi2c, uint8_t _dev_addr)
{
	// Assign the I2C handle and device address to the device handle structure
	_dev_typedef->hi2c = _dev_hi2c;
	_dev_typedef->address = _dev_addr;
	_dev_typedef->channels = 0; // Initialize channels (if needed)

	// Check if the device is ready for communication
	return HAL_I2C_IsDeviceReady(_dev_typedef->hi2c, (_dev_typedef->address << 1) | 1, 2, 100);
}

/*
 * @brief	Open the specified I2C bus channel
 *
 * @param   _dev_typedef     	Pointer to the device handle structure
 * @param   _channel	     	Channel number, ranging from 0 to 7
 * @return  HAL_StatusTypeDef   Status of the channel opening:
 *                              - HAL_OK: Success
 *                              - HAL_ERROR: Error occurred during channel opening
 */
HAL_StatusTypeDef TCA_OpenChannel(TCA9548A_HandleTypeDef *_dev_typedef, uint8_t _channel)
{
	// Set the specified channel bit in the channels configuration
	_dev_typedef->channels |= 1 << _channel;

	// Transmit the updated channels configuration to the TCA9548A device
	return HAL_I2C_Master_Transmit(_dev_typedef->hi2c, _dev_typedef->address << 1, &_dev_typedef->channels, 1, 100);
}

/*
 * @brief	Close the specified I2C bus channel
 *
 * @param   _dev_typedef     	Pointer to the device handle structure
 * @param   _channel	     	Channel number, ranging from 0 to 7
 * @return  HAL_StatusTypeDef   Status of the channel closing:
 *                              - HAL_OK: Success
 *                              - HAL_ERROR: Error occurred during channel closing
 */
HAL_StatusTypeDef TCA_CloseChannel(TCA9548A_HandleTypeDef *_dev_typedef, uint8_t _channel)
{
	// Clear the specified channel bit in the channels configuration
	_dev_typedef->channels &= ~(1 << _channel);

	// Transmit the updated channels configuration to the TCA9548A device
	return HAL_I2C_Master_Transmit(_dev_typedef->hi2c, _dev_typedef->address << 1, &_dev_typedef->channels, 1, 100);
}

/*
 * @brief	Open the selected channel and close others
 *
 * @param   _dev_typedef     	Pointer to the device handle structure
 * @param   _channel	     	Channel number, ranging from 0 to 7
 * @return  HAL_StatusTypeDef   Status of the channel opening:
 *                              - HAL_OK: Success
 *                              - HAL_ERROR: Error occurred during channel closing
 */
HAL_StatusTypeDef TCA_SelectChannel(TCA9548A_HandleTypeDef *_dev_typedef, uint8_t _channel)
{
	// Set the specified channel bit in the channels configuration
	_dev_typedef->channels = 1 << _channel;

	// Transmit the updated channels configuration to the TCA9548A device
	return HAL_I2C_Master_Transmit(_dev_typedef->hi2c, _dev_typedef->address << 1, &_dev_typedef->channels, 1, 100);
}

/*
 * @brief	Set the state of multiple channels simultaneously
 *
 * @param   _dev_typedef     	Pointer to the device handle structure
 * @param   _state_data	     	Channels state data byte, 0 = close; 1 = open
 * @return  HAL_StatusTypeDef   Status of the channel setting:
 *                              - HAL_OK: Success
 *                              - HAL_ERROR: Error occurred during channel closing
 */
HAL_StatusTypeDef TCA_SetMultipleChannels(TCA9548A_HandleTypeDef *_dev_typedef, uint8_t _state_data)
{
	// Move data to channels configuration
	_dev_typedef->channels = _state_data;

	// Transmit the updated channels configuration to the TCA9548A device
	return HAL_I2C_Master_Transmit(_dev_typedef->hi2c, _dev_typedef->address << 1, &_dev_typedef->channels, 1, 100);
}

/*
 * @brief	Open all channels
 *
 * @param   _dev_typedef     	Pointer to the device handle structure
 * @return  HAL_StatusTypeDef   Status of the channel opening:
 *                              - HAL_OK: Success
 *                              - HAL_ERROR: Error occurred during channel closing
 */
HAL_StatusTypeDef TCA_OpenAllChannels(TCA9548A_HandleTypeDef *_dev_typedef)
{
	// Set all bits to 1
	_dev_typedef->channels = 0xff;

	// Transmit the updated channels configuration to the TCA9548A device
	return HAL_I2C_Master_Transmit(_dev_typedef->hi2c, _dev_typedef->address << 1, &_dev_typedef->channels, 1, 100);
}

/*
 * @brief	Close all channels
 *
 * @param   _dev_typedef     	Pointer to the device handle structure
 * @return  HAL_StatusTypeDef   Status of the channel closing:
 *                              - HAL_OK: Success
 *                              - HAL_ERROR: Error occurred during channel closing
 */
HAL_StatusTypeDef TCA_CloseAllChannels(TCA9548A_HandleTypeDef *_dev_typedef)
{
	// Set all bits to 0
	_dev_typedef->channels = 0x00;

	// Transmit the updated channels configuration to the TCA9548A device
	return HAL_I2C_Master_Transmit(_dev_typedef->hi2c, _dev_typedef->address << 1, &_dev_typedef->channels, 1, 100);
}

/*
 * @brief	Get the specified channel status
 *
 * @param   _dev_typedef     	Pointer to the device handle structure
 * @param   _channel	     	Channel number, ranging from 0 to 7
 * @return  uint8_t   			Channel status:
 *                              - 1: Open
 *                              - 0: Close
 */
uint8_t TCA_GetChannelStatus(TCA9548A_HandleTypeDef *_dev_typedef, uint8_t _channel)
{
	if (HAL_I2C_Master_Receive(_dev_typedef->hi2c, (_dev_typedef->address << 1) | 1, &_dev_typedef->channels, 1, 100) == HAL_OK)
	{
		return (_dev_typedef->channels & (1 << _channel)) > 0;
	}
	else return 0;
}

/*
 * @brief	Get all channels status
 *
 * @param   _dev_typedef     	Pointer to the device handle structure
 * @param   _channel	     	Channel number, ranging from 0 to 7
 * @return  uint8_t   			Channel status data byte:
 *                              - 1: Open
 *                              - 0: Close
 */
uint8_t TCA_GetAllChannelStatus(TCA9548A_HandleTypeDef *_dev_typedef)
{
	if (HAL_I2C_Master_Receive(_dev_typedef->hi2c, (_dev_typedef->address << 1) | 1, &_dev_typedef->channels, 1, 100) == HAL_OK)
	{
		return _dev_typedef->channels;
	}
	else return 0;
}
