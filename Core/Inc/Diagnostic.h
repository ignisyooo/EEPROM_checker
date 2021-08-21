/*
 * Diagnostic.h
 *
 *  Created on: 21 sie 2021
 *      Author: Rzeszutko
 */

#ifndef INC_DIAGNOSTIC_H_
#define INC_DIAGNOSTIC_H_

#include "ErrorCode.h"
#include "EEPROM.h"

typedef struct
{
	uint32_t duration_of_the_test; 	/* in mili second */
	uint16_t number_of_mem_cells;
	uint8_t testValue;
	uint8_t address;
}TestParameters_T;

STD_Error ExecuteSingleTest(uint8_t test_value);
STD_Error ExecuteMatsTest(void);
STD_Error ExecuteShortBitTest(void);

void SendRaport_by_UART(STD_Error error_code);


#endif /* INC_DIAGNOSTIC_H_ */
