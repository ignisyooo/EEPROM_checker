/*
 * Comunication.h
 *
 *  Created on: 18 sie 2021
 *      Author: Rzeszutko
 */

#ifndef INC_COMUNICATION_H_
#define INC_COMUNICATION_H_

#include "ErrorCode.h"

#define MAX_MSG_LENGTH (31)

#define MA_INDEX (10)
#define MA_SIZE	(4)

#define MS_INDEX (18)
#define MS_SIZE (3)

#define PS_INDEX (25)
#define PS_SIZE (2)

#define VAL_INDEX (12)
#define VAL_SIZE (4)

typedef enum
{
	CONFIG,
	SINGLE,
	MATS,
	SHORT_BIT,
	UNKNOWN
}FrameType;


void UART_init(void);
void LogData(const uint8_t *msg);
FrameType GetFrameType(void);
uint8_t GetMemoryAddress(void);
uint16_t GetMemorySize(void);
uint16_t GetPageSize(void);



#endif /* INC_COMUNICATION_H_ */
