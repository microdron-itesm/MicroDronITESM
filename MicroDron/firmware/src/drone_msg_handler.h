
#ifndef _DRONE_MSG_HANDLER_H   
#define _DRONE_MSG_HANDLER_H
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "drone_control/drone_motor_output.h"
#include "drone_control/PID/pid_config.h"

/**
 *Simple serial comms handler to manage received commands from Wifi Module.
 *
 *
 *A drone Command message starts with a ',', the state machine waits to read the start character.
 *Then it starts filling a char array buffer, once a '\n' is received the message is parsed  
 *and the last drone command is updated. This manages the heartbeat update, PID setpoint control
 *PID Configuration Updates, manual motor control, etc.
 */

typedef enum {
	DRONE_MSG_HANDLER_STATE_MSG_START,
	DRONE_MSG_HANDLER_STATE_MSG_RECEIVE
}DRONE_MSG_HANDLER_STATE;

typedef enum {
	DRONE_MSG_TYPE_NONE,
	DRONE_MSG_TYPE_UPDATE_SETPOINTS,
	DRONE_MSG_TYPE_MANUAL_CONTROL,
	DRONE_MSG_TYPE_KILL_MOTORS,
	DRONE_MSG_TYPE_UPDATE_PID,
	DRONE_MSG_TYPE_UPDATE_K,
	DRONE_MSG_TYPE_HEARTBEAT
} DRONE_MSG_TYPE;

typedef struct {
	float yaw;
	float pitch;
	float roll;
	float thrust;	
} DRONE_MSG_DATA_UPDATE_SETPOINTS;


void DRONE_MSG_HANDLER_INITIALIZE();

void DRONE_MSG_HANDLER_UPDATE();

DRONE_MSG_TYPE DRONE_MSG_HANDLER_LAST_MSG_TYPE();

DRONE_MSG_DATA_UPDATE_SETPOINTS DRONE_MSG_HANDLER_DATA_UPDATE_SETPOINTS();

DRONE_CTRL_MOTOR_OUTPUT DRONE_MSG_HANDLER_DATA_MANUAL_CONTROL();

PID_CONFIG DRONE_MSG_HANDLER_GET_PID_CONFIG_UPDATE();

char DRONE_MSG_HANDLER_GET_PID_UPDATE_TARGET();

bool DRONE_MSG_HANDLER_NEW_MSG_AVAILABLE();

float DRONE_MSG_HANDLER_GET_LAST_K();

#endif 
