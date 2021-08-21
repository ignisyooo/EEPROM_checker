/*
 * EEPROM.c
 *
 *  Created on: Aug 17, 2021
 *      Author: Rzeszutko
 */


#include "EEPROM.h"

static EEPROM_settings_T eeprom_sett;

void EEPROM_Init(I2C_HandleTypeDef *hi2c)
{
	eeprom_sett.i2c = hi2c;
	eeprom_sett.isReady = false;
	eeprom_sett.config.mem_address = 0;
	eeprom_sett.config.mem_size = 0;
	eeprom_sett.config.page_size = 0;
}

void EEPROM_Set_Parameters(uint8_t mem_address, uint16_t mem_size, uint16_t page_size)
{
	eeprom_sett.config.mem_address = mem_address;
	eeprom_sett.config.mem_size = mem_size;
	eeprom_sett.config.page_size = page_size;
	eeprom_sett.isReady = true;
}

bool EEPROM_isConnected(void)
{
	bool retVal = true;
	if(HAL_OK != HAL_I2C_IsDeviceReady(eeprom_sett.i2c, eeprom_sett.config.mem_address, 2, 10))
	{
		retVal = false;
	}

	return retVal;
}

EEPROM_Config_T *EEPROM_Get_ConfigData(void)
{
	return &eeprom_sett.config;
}

STD_Error EEPROM_Write(uint8_t address, const uint8_t * data, int size)
{
	STD_Error retVal = STD_OK;
	HAL_StatusTypeDef halErr;

	if(!EEPROM_isConnected())
		retVal = STD_TIMEOUT_ERROR;

	if(!eeprom_sett.isReady)
		retVal = STD_BUSY_ERROR;

	if(size <= 0)
		retVal = STD_PARAMETER_ERROR;

	if(STD_OK == retVal)
	{
		if(address + size > eeprom_sett.config.mem_size)
			size = eeprom_sett.config.mem_size - address;

		uint8_t offset = 0;
		uint8_t sendSize = eeprom_sett.config.page_size - (address % eeprom_sett.config.page_size);

		if(!sendSize)
			sendSize = eeprom_sett.config.page_size;
		if(sendSize > size)
			sendSize = size;



		halErr = HAL_I2C_Mem_Write(eeprom_sett.i2c, eeprom_sett.config.mem_address, address, 1, data, sendSize, 10);

        retVal = translate_error_hal_to_project(halErr);

        if(retVal != STD_OK)
        	return retVal;

        offset += sendSize;
        size -= sendSize;

        while(size > 0)
        {

			halErr = HAL_I2C_Mem_Write(eeprom_sett.i2c, eeprom_sett.config.mem_address, address + offset, 1,
				data + offset, size > eeprom_sett.config.page_size ? eeprom_sett.config.page_size : size,
				10);

            retVal = translate_error_hal_to_project(halErr);

            if(retVal != STD_OK)
            	return retVal;

            offset += eeprom_sett.config.page_size;
            size -= eeprom_sett.config.page_size;
        }

	}

	return retVal;
}

STD_Error EEPROM_Read(uint8_t address, uint8_t *data, int size)
{
	STD_Error retVal = STD_OK;

	if(!EEPROM_isConnected())
		retVal = STD_TIMEOUT_ERROR;

    if(!eeprom_sett.isReady)
        retVal = STD_BUSY_ERROR;

    if(size <= 0)
        retVal = STD_PARAMETER_ERROR;

    if(STD_OK == retVal)
    {
        if(address + size > eeprom_sett.config.mem_size)
        	size = eeprom_sett.config.mem_size - address;

        HAL_StatusTypeDef halErr;

		halErr = HAL_I2C_Mem_Read(eeprom_sett.i2c, eeprom_sett.config.mem_address, address, 1, data, size,
			10);


        retVal = translate_error_hal_to_project(halErr);
    }

    return retVal;
}
