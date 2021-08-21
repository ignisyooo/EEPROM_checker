/*
 * StateMachine.h
 *
 *  Created on: Aug 20, 2021
 *      Author: Rzeszutko
 */

#ifndef INC_STATEMACHINE_H_
#define INC_STATEMACHINE_H_



#define SM_INTERFACE(INPUT_MACRO) \
		INPUT_MACRO(Init, InitStateHandler) \
		INPUT_MACRO(WaitForAction, WaitForActionHandler) \
		INPUT_MACRO(Config, ConfigHandler) \
		INPUT_MACRO(RunTest, RunTestHandler) \
		INPUT_MACRO(RaportGeneration, RaportGenerationHandler) \

#define SM_STRUCT_INIT(STATE, CALLBACK) \
		{ \
			.state = STATE, \
			.callback = CALLBACK \
		}, \

#define SM_ENUM_INIT(STATE, CALLBACK) STATE,

typedef void (*State_fun_ptr)(void);

typedef enum
{
	SM_INTERFACE(SM_ENUM_INIT)
	MaxNumberOfState
}SM_state_T;


typedef struct
{
	SM_state_T state;
	State_fun_ptr callback;
}StateMachine_T;

void StateMachineHandle(void);

#endif /* INC_STATEMACHINE_H_ */
