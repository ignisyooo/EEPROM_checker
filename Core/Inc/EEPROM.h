/*
 * EEPROM.h
 *
 *  Created on: Aug 17, 2021
 *      Author: Rzeszutko
 */

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_

#include <stdbool.h>

#include "i2c.h"
#include "ErrorCode.h"

#define MINIMUM_TIME (5)

typedef struct
{
	uint8_t mem_address;
	uint16_t mem_size;
	uint16_t page_size;
}EEPROM_Config_T;

typedef struct
{
	bool isReady;
	I2C_HandleTypeDef *i2c;
	EEPROM_Config_T config;
}EEPROM_settings_T;

void EEPROM_Init(I2C_HandleTypeDef *hi2c);
void EEPROM_Set_Parameters(uint8_t mem_address, uint16_t mem_size, uint16_t page_size);

STD_Error EEPROM_Write(uint8_t address, const uint8_t * data, int size);
STD_Error EEPROM_Read(uint8_t address, uint8_t *data, int size);

EEPROM_Config_T *EEPROM_Get_ConfigData(void);

#endif /* INC_EEPROM_H_ */
