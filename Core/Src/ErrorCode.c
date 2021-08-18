/*
 * ErrorCode.c
 *
 *  Created on: Aug 17, 2021
 *      Author: Rzeszutko
 */


#include "ErrorCode.h"
#include "main.h"

static char * str_error_code[] = {
		ERROR_CODE(STRING_ErrorCode)
};

char * getErrorCode(STD_Error type)
{
	return str_error_code[type];
}

STD_Error translate_error_hal_to_project(HAL_StatusTypeDef halStatus)
{
	STD_Error retVal;

    switch(halStatus)
    {
        case HAL_OK: retVal = STD_OK; break;
        case HAL_ERROR: retVal = STD_ERROR; break;
        case HAL_BUSY: retVal = STD_BUSY_ERROR; break;
        case HAL_TIMEOUT: retVal = STD_TIMEOUT_ERROR; break;
        default: retVal = STD_UKNOWN_ERROR; break;
    }
    return retVal;
}
