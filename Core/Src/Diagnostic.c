/*
 * Diagnostic.c
 *
 *  Created on: 21 sie 2021
 *      Author: Rzeszutko
 */


#include "Diagnostic.h"

#include <string.h>

#define DIAGNOSTIC_MESSAGE_LENGTH (200U)

#define BITS_IN_BYTE (8)

#define GET_BIT(byte, bit_number) ((byte >> bit_number) & 0x01)

static TestParameters_T TestParameters;
static char DiagonosticMsg[DIAGNOSTIC_MESSAGE_LENGTH];

static void SetTestParameters(const EEPROM_Config_T *config, uint8_t test_value)
{
	TestParameters.duration_of_the_test = 0;
	TestParameters.address = 0;
	TestParameters.testValue = test_value;
	TestParameters.number_of_mem_cells = config->mem_size;
}

static const char * Check_for_short_circuit_between_bits(uint8_t pattern, uint8_t read_value)
{
	static char circut_test_msg[50];
	for(uint8_t idx = BITS_IN_BYTE - 1; idx >= 0; idx--)
	{
		if(GET_BIT(pattern, idx) != GET_BIT(read_value, idx))
		{
			(void)sprintf(circut_test_msg, "A short circuit between %u and %u bit was detected", idx, idx - 1);
			break;
		}
	}

	return circut_test_msg;
}

STD_Error ExecuteSingleTest(uint8_t test_value)
{
	STD_Error error_code = STD_OK;
	uint8_t read_value = 0;
	SetTestParameters(EEPROM_Get_ConfigData(), test_value);
	LogData("Single test procedure was started\n");

	uint32_t start = HAL_GetTick();
	uint32_t end = 0;

	error_code = EEPROM_Write(TestParameters.address, &TestParameters.testValue, 1);
	if(STD_OK != error_code)
	{
		end = HAL_GetTick();
		TestParameters.duration_of_the_test = end - start;
		(void)sprintf(DiagonosticMsg, "Test fail\nError while writing value: 0x%.2X to the memory at the address: 0x%.2X\nTest duration: %u ms\n",
				TestParameters.testValue, TestParameters.address, TestParameters.duration_of_the_test);
		return error_code;
	}
	HAL_Delay(MINIMUM_TIME);
	error_code = EEPROM_Read(TestParameters.address, &read_value, 1);
	end = HAL_GetTick();
	TestParameters.duration_of_the_test = end - start;
	if(STD_OK != error_code)
	{
		(void)sprintf(DiagonosticMsg, "Test fail\nError while reading value from the memory at the address: 0x%.2X\nTest duration: %u ms\n\r",
				TestParameters.address, TestParameters.duration_of_the_test);
		return error_code;
	}

	if(TestParameters.testValue == read_value)
	{
		(void)sprintf(DiagonosticMsg, "Test passed\nSuccessful reading the value 0x%.2X, from the address: 0x%.2X\nTest duration: %u ms\n\r",
				TestParameters.testValue, TestParameters.address, TestParameters.duration_of_the_test);
	}
	else
	{
		(void)sprintf(DiagonosticMsg, "Test fail\nValue read: 0x%.2X, not equal to the test value: 0x%.2X, Test performed for the address: 0x%.2X\nTest duration: %u ms\n",
				read_value, TestParameters.testValue, TestParameters.address, TestParameters.duration_of_the_test);
	}
	return error_code;
}


STD_Error ExecuteMatsTest(void)
{
	STD_Error error_code = STD_OK;
	uint8_t read_value = 0;
	uint8_t write_value = 0;
	SetTestParameters(EEPROM_Get_ConfigData(), 0);
	LogData("Mats+ test procedure was started\n");
	uint32_t start = HAL_GetTick();
	uint32_t idx = 0;
	uint32_t end = 0;

	/* M1: for each cell from 0 to n - 1 write 0 */
	for(; idx < TestParameters.number_of_mem_cells; ++idx)
	{
		error_code = EEPROM_Write(idx, &write_value, 1);
		if(STD_OK != error_code) break;
		HAL_Delay(MINIMUM_TIME);
	}

	if(STD_OK != error_code)
	{
		end = HAL_GetTick();
		TestParameters.duration_of_the_test = end - start;
		(void)sprintf(DiagonosticMsg, "Test fail\nError while writing value: 0 to the memory at the address: 0x%.2X\nTest duration: %u ms\n",
				idx, TestParameters.duration_of_the_test);
		return error_code;
	}

	write_value = 0xFF;
	/* M2: for each cell from 0 to n - 1 read cell {expected value 0}, write FF */
	for(idx = 0; idx < TestParameters.number_of_mem_cells; ++idx)
	{
		error_code = EEPROM_Read(idx, &read_value, 1);
		if(STD_OK != error_code)
		{
			(void)sprintf(DiagonosticMsg, "Test fail\nError while reading value from the memory at the address: 0x%.2X\nTest duration: %u ms\n",
					idx, TestParameters.duration_of_the_test);
			break;
		}
		if(0 != read_value)
		{
			(void)sprintf(DiagonosticMsg, "Test fail\nThe value read: 0x%.2X, not equal to the test value: 0, Test performed for the address: 0x%.2X\nTest duration: %u ms\n",
					read_value, TestParameters.address, TestParameters.duration_of_the_test);
		}
		HAL_Delay(MINIMUM_TIME);
		error_code = EEPROM_Write(idx, &write_value, 1);
		if(STD_OK != error_code)
		{
			end = HAL_GetTick();
			TestParameters.duration_of_the_test = end - start;
			(void)sprintf(DiagonosticMsg, "Test fail\nError while writing value: 0xFF to the memory at the address: 0x%.2X\nTest duration: %u ms\n",
					idx, TestParameters.duration_of_the_test);
			break;
		}
		HAL_Delay(MINIMUM_TIME);
	}

	if(STD_OK != error_code) return error_code;

	write_value = 0;
	/* M3:  for each cell from n - 1 to 0 read cell {expected value 1}, write 0*/
	for(idx = TestParameters.number_of_mem_cells - 1; idx > 0; idx--)
	{
		error_code = EEPROM_Read(idx, &read_value, 1);
		if(STD_OK != error_code)
		{
			(void)sprintf(DiagonosticMsg, "Test fail\nError while reading value from the memory at the address: 0x%.2X\nTest duration: %u ms\n",
					idx, TestParameters.duration_of_the_test);
			break;
		}
		if(0xFF != read_value)
		{
			(void)sprintf(DiagonosticMsg, "Test fail\nThe value read: 0x%.2X, not equal to the test value: 0xFF, Test performed for the address: 0x%.2X\nTest duration: %u ms\n",
					read_value, TestParameters.address, TestParameters.duration_of_the_test);
		}
		HAL_Delay(MINIMUM_TIME);
		error_code = EEPROM_Write(idx, &write_value, 1);
		if(STD_OK != error_code)
		{
			end = HAL_GetTick();
			TestParameters.duration_of_the_test = end - start;
			(void)sprintf(DiagonosticMsg, "Test fail\nError while writing value: 0 to the memory at the address: 0x%.2X\nTest duration: %u ms\n",
					idx, TestParameters.duration_of_the_test);
			break;
		}
		HAL_Delay(MINIMUM_TIME);
	}

	if(STD_OK != error_code) return error_code;

	end = HAL_GetTick();
	TestParameters.duration_of_the_test = end - start;
	(void)sprintf(DiagonosticMsg, "Test passed\nSuccessfully completed mats + test sequences\nTest duration: %u ms\n\r",
			TestParameters.duration_of_the_test);

	return error_code;
}

STD_Error ExecuteShortBitTest(void)
{
	STD_Error error_code = STD_OK;
	uint8_t read_value = 0;
	SetTestParameters(EEPROM_Get_ConfigData(), 0);
	LogData("Short Bits test procedure was started\n");
	uint32_t start = HAL_GetTick();
	uint32_t end = 0;
	uint8_t write_value = 0x55;

	for(uint32_t idx = 0; idx < TestParameters.number_of_mem_cells; ++idx)
	{
		error_code = EEPROM_Write(idx, &write_value, 1);
		if(STD_OK != error_code)
		{
			end = HAL_GetTick();
			TestParameters.duration_of_the_test = end - start;
			(void)sprintf(DiagonosticMsg, "Test fail\nError while writing value: 0x55 to the memory at the address: 0x%.2X\n",
					"Test duration: %u ms\n",
					idx, TestParameters.duration_of_the_test);
			break;
		}

		HAL_Delay(MINIMUM_TIME);

		error_code = EEPROM_Read(idx, &read_value, 1);
		if(STD_OK != error_code)
		{
			(void)sprintf(DiagonosticMsg, "Test fail\nError while reading value from the memory at the address: 0x%.2X\n",
					"Test duration: %u ms\n",
					idx, TestParameters.duration_of_the_test);
			break;
		}
		if(0x55 != read_value)
		{
			(void)sprintf(DiagonosticMsg, "Test fail\nThe value read: 0x%.2X, not equal to the test value: 0x55, Test performed for the address: 0x%.2X\n%s\nTest duration: %u ms\n",
					read_value, TestParameters.address, Check_for_short_circuit_between_bits(0x55, read_value), TestParameters.duration_of_the_test);

		}
		HAL_Delay(MINIMUM_TIME);
	}

	if(STD_OK == error_code)
	{
		end = HAL_GetTick();
		TestParameters.duration_of_the_test = end - start;
		(void)sprintf(DiagonosticMsg, "Test passed\nSuccessfully completed Short Bits test sequences\nTest duration: %u ms\n\r",
				TestParameters.duration_of_the_test);
	}

	return error_code;
}

void SendRaport_by_UART(STD_Error error_code)
{
	LogData(DiagonosticMsg);
	if(STD_OK != error_code)
	{
		(void)sprintf(DiagonosticMsg, "Error code: %s\n\r", getErrorCode(error_code));
		LogData(DiagonosticMsg);
	}
}
