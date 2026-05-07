
#include "tca9548a.h"

static HAL_StatusTypeDef TCA_WriteChannels(TCA9548A_HandleTypeDef *dev)
{
    return HAL_I2C_Master_Transmit(
        dev->hi2c,
        dev->address << 1,
        &dev->channels,
        1,
        TCA9548A_TIMEOUT
    );
}

static HAL_StatusTypeDef TCA_ReadChannels(TCA9548A_HandleTypeDef *dev)
{
    return HAL_I2C_Master_Receive(
        dev->hi2c,
        dev->address << 1,
        &dev->channels,
        1,
        TCA9548A_TIMEOUT
    );
}

/*
 * @brief	Initialize the device and verify its status
 *
 * @param   dev					Pointer to the device handle structure
 * @param   hi2c	        	Pointer to a I2C_HandleTypeDef structure
 * @param   address	        	TCA9548A address, automatically shifted by the function
 * @return  HAL_StatusTypeDef   Status of the initialization
 *                              - HAL_OK: Success
 *                              - HAL_ERROR: Error occurred during initialization
 */
HAL_StatusTypeDef TCA_Init(TCA9548A_HandleTypeDef *dev, I2C_HandleTypeDef *hi2c, GPIO_TypeDef *reset_port, uint16_t reset_pin, uint8_t address)
{
	// Assign the I2C handle and device address to the device handle structure
	dev->hi2c = hi2c;
	dev->address = address;
	dev->channels = 0x00;

	// Assign the reset port and pin number to the device handle structure
	dev->reset_port = reset_port;
	dev->reset_pin = reset_pin;

	// Check if the device is ready for communication
	return HAL_I2C_IsDeviceReady(dev->hi2c, dev->address << 1, 3, TCA9548A_TIMEOUT);
}

/*
 * @brief	Resets TCA9548A
 *
 * @param   dev					Pointer to the device handle structure
 * @return  HAL_StatusTypeDef   Status of the initialization
 *                              - HAL_OK: Success
 *                              - HAL_ERROR: Error occurred during initialization
 */
HAL_StatusTypeDef TCA_Reset(TCA9548A_HandleTypeDef *dev)
{
	// Check for pin port
    if (dev->reset_port == NULL)
    {
        return HAL_ERROR;
    }

    // TCA9548A reset signal length minimum is 6 nS
    HAL_GPIO_WritePin(dev->reset_port, dev->reset_pin, GPIO_PIN_RESET);
    HAL_Delay(1);

    HAL_GPIO_WritePin(dev->reset_port, dev->reset_pin, GPIO_PIN_SET);
    HAL_Delay(1);

    dev->channels = 0x00;

    return HAL_I2C_IsDeviceReady(dev->hi2c, dev->address << 1, 3, TCA9548A_TIMEOUT);
}

/*
 * @brief	Open the specified I2C bus channel
 *
 * @param   dev     			Pointer to the device handle structure
 * @param   channel	     		Channel number, ranging from 0 to 7
 * @return  HAL_StatusTypeDef   Status of the channel opening:
 *                              - HAL_OK: Success
 *                              - HAL_ERROR: Error occurred during channel opening
 */
HAL_StatusTypeDef TCA_OpenChannel(TCA9548A_HandleTypeDef *dev, TCA_Channel_t channel)
{
	if (channel > 7) return HAL_ERROR;

	// Set the specified channel bit in the channels configuration
	dev->channels |= (1U << channel);

	// Transmit the updated channels configuration to the TCA9548A device
	return TCA_WriteChannels(dev);
}

/*
 * @brief	Close the specified I2C bus channel
 *
 * @param   dev     			Pointer to the device handle structure
 * @param   channel	     		Channel number, ranging from 0 to 7
 * @return  HAL_StatusTypeDef   Status of the channel closing:
 *                              - HAL_OK: Success
 *                              - HAL_ERROR: Error occurred during channel closing
 */
HAL_StatusTypeDef TCA_CloseChannel(TCA9548A_HandleTypeDef *dev, TCA_Channel_t channel)
{
	if (channel > 7) return HAL_ERROR;

	// Clear the specified channel bit in the channels configuration
	dev->channels &= ~(1U << channel);

	// Transmit the updated channels configuration to the TCA9548A device
	return TCA_WriteChannels(dev);
}

/*
 * @brief	Open the selected channel and close others
 *
 * @param   dev     			Pointer to the device handle structure
 * @param   channel	     		Channel number, ranging from 0 to 7
 * @return  HAL_StatusTypeDef   Status of the channel opening:
 *                              - HAL_OK: Success
 *                              - HAL_ERROR: Error occurred during channel select
 */
HAL_StatusTypeDef TCA_SelectChannel(TCA9548A_HandleTypeDef *dev, TCA_Channel_t channel)
{
	if (channel > 7) return HAL_ERROR;

	// Set the specified channel bit in the channels configuration
	dev->channels = (1U << channel);

	// Transmit the updated channels configuration to the TCA9548A device
	return TCA_WriteChannels(dev);
}

/*
 * @brief	Set the state of multiple channels simultaneously
 *
 * @param   dev     			Pointer to the device handle structure
 * @param   state_data	     	Channels state data byte, 0 = close; 1 = open
 * @return  HAL_StatusTypeDef   Status of the channel setting:
 *                              - HAL_OK: Success
 *                              - HAL_ERROR: Error occurred during channel set
 */
HAL_StatusTypeDef TCA_SetMultipleChannels(TCA9548A_HandleTypeDef *dev, const uint8_t state_data)
{
	// Move data to channels configuration
	dev->channels = state_data;

	// Transmit the updated channels configuration to the TCA9548A device
	return TCA_WriteChannels(dev);
}

/*
 * @brief	Open all channels
 *
 * @param   dev     			Pointer to the device handle structure
 * @return  HAL_StatusTypeDef   Status of the channel opening:
 *                              - HAL_OK: Success
 *                              - HAL_ERROR: Error occurred during channel opening
 */
HAL_StatusTypeDef TCA_OpenAllChannels(TCA9548A_HandleTypeDef *dev)
{
	// Set all bits to 1
	dev->channels = 0xff;

	// Transmit the updated channels configuration to the TCA9548A device
	return TCA_WriteChannels(dev);
}

/*
 * @brief	Close all channels
 *
 * @param   dev     			Pointer to the device handle structure
 * @return  HAL_StatusTypeDef   Status of the channel closing:
 *                              - HAL_OK: Success
 *                              - HAL_ERROR: Error occurred during channel closing
 */
HAL_StatusTypeDef TCA_CloseAllChannels(TCA9548A_HandleTypeDef *dev)
{
	// Set all bits to 0
	dev->channels = 0x00;

	// Transmit the updated channels configuration to the TCA9548A device
	return TCA_WriteChannels(dev);
}

/*
 * @brief	Get the specified channel status
 *
 * @param   dev     			Pointer to the device handle structure
 * @param   channel	     		Channel number, ranging from 0 to 7
 * @return  uint8_t   			Channel status:
 *                              - 1: Open
 *                              - 0: Close
 */
uint8_t TCA_GetChannelStatus(TCA9548A_HandleTypeDef *dev, TCA_Channel_t channel)
{
	if (channel > 7) return 0;

	if (TCA_ReadChannels(dev) == HAL_OK)
	{
		return ((dev->channels & (1U << channel)) != 0U);
	}

	return 0;
}

/*
 * @brief	Get all channels status
 *
 * @param   dev     			Pointer to the device handle structure
 * @param   channel	     		Channel number, ranging from 0 to 7
 * @return  uint8_t   			Channel status data byte:
 *                              - 1: Open
 *                              - 0: Close
 */
uint8_t TCA_GetAllChannelStatus(TCA9548A_HandleTypeDef *dev)
{
	if (TCA_ReadChannels(dev) == HAL_OK)
	{
		return dev->channels;
	}

	return 0;
}
