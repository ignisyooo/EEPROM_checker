/*
 * Comunication.c
 *
 *  Created on: 18 sie 2021
 *      Author: Rzeszutko
 */

#include "usart.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "Comunication.h"


volatile char ReceivedFrame[MAX_MSG_LENGTH];

volatile bool is_updated = false;

void UART_init(void)
{
	HAL_UART_Receive_IT(&huart2, (uint8_t*)ReceivedFrame, MAX_MSG_LENGTH);
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART2)
	{
		is_updated = true;
		HAL_UART_Receive_IT(&huart2, (uint8_t*)ReceivedFrame, MAX_MSG_LENGTH);
	}
}


uint8_t GetMemoryAddress(void)
{
	uint8_t retVal = 0;
	char memory_adress[MA_SIZE];
	memcpy(memory_adress, ReceivedFrame + MA_INDEX, MA_SIZE);
	retVal = strtoul(memory_adress, NULL, 16);
	return retVal;
}

uint16_t GetMemorySize(void)
{
	uint16_t retVal = 0;
	char memory_size[MS_SIZE];
	memcpy(memory_size, ReceivedFrame + MS_INDEX, MS_SIZE);
	retVal = strtoul(memory_size, NULL, 10) /10;
	return retVal;
}

uint16_t GetPageSize(void)
{
	uint16_t retVal = 0;
	char page_size[PS_SIZE];
	memcpy(page_size, ReceivedFrame + PS_INDEX, PS_SIZE);
	retVal = strtoul(page_size, NULL, 10);
	return retVal;
}

uint8_t GetTestValue(void)
{
	uint16_t retVal = 0;
	char page_size[VAL_SIZE];
	memcpy(page_size, ReceivedFrame + VAL_INDEX, VAL_SIZE);
	retVal = strtoul(page_size, NULL, 16);
	return retVal;
}


FrameType GetFrameType(void)
{
	FrameType retVal;
	if(strstr(ReceivedFrame, "CONFIG"))
	{
		retVal = CONFIG;
	}
	else if(strstr(ReceivedFrame, "SINGLE"))
	{
		retVal = SINGLE;
	}
	else if(strstr(ReceivedFrame, "MATS"))
	{
		retVal = MATS;
	}
	else if(strstr(ReceivedFrame, "SHORT"))
	{
		retVal = SHORT_BIT;
	}
	else
	{
		retVal = UNKNOWN;
	}

	return retVal;
}


void LogData(const uint8_t *msg)
{
	if(HAL_OK != HAL_UART_Transmit(&huart2, msg, strlen(msg), HAL_MAX_DELAY))
	{
		Error_Handler();
	}
}

