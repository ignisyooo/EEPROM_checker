/*
 * ErrorCode.h
 *
 *  Created on: Aug 17, 2021
 *      Author: Rzeszutko
 */

#ifndef INC_ERRORCODE_H_
#define INC_ERRORCODE_H_

#include "main.h"

#define ERROR_CODE(INPUT_MACRO) \
	INPUT_MACRO(STD_OK) \
	INPUT_MACRO(STD_ERROR) \
	INPUT_MACRO(STD_PARAMETER_ERROR) \
	INPUT_MACRO(STD_BUSY_ERROR) \
	INPUT_MACRO(STD_TIMEOUT_ERROR) \
	INPUT_MACRO(STD_COMMAND_ERROR) \


#define ENUM_ErrorCode(CODE) CODE,
#define STRING_ErrorCode(CODE) #CODE,


typedef enum
{
	ERROR_CODE(ENUM_ErrorCode)
	STD_UKNOWN_ERROR = 255
}STD_Error;

char * getErrorCode(STD_Error type);
STD_Error translate_error_hal_to_project(HAL_StatusTypeDef halStatus);

#endif /* INC_ERRORCODE_H_ */
