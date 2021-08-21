/*
 * StateMachine.c
 *
 *  Created on: Aug 20, 2021
 *      Author: Rzeszutko
 */

#include "StateMachine.h"
#include "Comunication.h"
#include "EEPROM.h"

static void ConfigHandler(void);
static void InitStateHandler(void);
static void RunTestHandler(void);
static void WaitForActionHandler(void);
static void RaportGenerationHandler(void);
static void ConnectionCheckHandler(void);


static StateMachine_T SM_interface[] = {
		SM_INTERFACE(SM_STRUCT_INIT)
};

extern volatile bool is_updated;
volatile SM_state_T State = Init;
static FrameType frame = UNKNOWN;
STD_Error error_code = STD_OK;

static char error_msg[150];

static void ConfigHandler(void)
{
	uint8_t memory_address = GetMemoryAddress();
	uint16_t memory_size = GetMemorySize();
	uint16_t page_size = GetPageSize();
	EEPROM_Set_Parameters(memory_address, memory_size, page_size);
	LogData("The parameters have been saved\n\r");
	LogData("Waiting for the test method to be selected\n\r");
	State = WaitForAction;
}


static void InitStateHandler(void)
{
	UART_init();
	EEPROM_Init(&hi2c1);
	State = WaitForAction;
}

static void RunTestHandler(void)
{
	switch(frame)
	{
		case SINGLE:
			error_code = ExecuteSingleTest(GetTestValue());
			break;
		case MATS:
			error_code = ExecuteMatsTest();
			break;
		case SHORT_BIT:
			error_code = ExecuteShortBitTest();
			break;
		default:
			error_code = STD_COMMAND_ERROR;
	}

	State = RaportGeneration;
}

static void RaportGenerationHandler(void)
{
	SendRaport_by_UART(error_code);
	State = WaitForAction;
}

static void WaitForActionHandler(void)
{
	if(is_updated)
	{
		frame = GetFrameType();
		switch(frame)
		{
			case CONFIG:
				State = Config;
				break;
			case SINGLE:
			case MATS:
			case SHORT_BIT:
				State = RunTest;
				break;
			case CONNECTION:
				State = ConnectionCheck;
				break;
			default:
				(void)sprintf(error_msg, "Invalid data frame received\n\rError code: %s\n\r", getErrorCode(error_code));
				LogData(error_msg);
				break;
		}
		is_updated = false;
	}
}

static void ConnectionCheckHandler(void)
{
	if(EEPROM_isConnected())
	{
		LogData("Device detected\n\r");
	}
	else
	{
		(void)sprintf(error_msg, "The device with the address: 0x%.2X was not detected. Check if the given address is correct, or check the connection to the microcontroller\n\r", EEPROM_Get_ConfigData()->mem_address);
		LogData(error_msg);
	}
	State = WaitForAction;
}


void StateMachineHandle(void)
{
	SM_interface[State].callback();
}
