#ifndef _IMU_MSG_HANDLER_H 
#define _IMU_MSG_HANDLER_H
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "system_config.h"
#include "system_definitions.h"
#include "drone_control/drone_pose.h"

/**
 *Simple serial comms handler to obtain IMU data.
 *
 *The IMU message starts with a ',', the state machine waits to read the start character.
 *Then it starts filling a char array buffer, once a '\n' is received the message is parsed  
 *and the IMU state is updated.
 */


typedef enum {
	IMU_MSG_HANDLER_STATE_INIT,
	IMU_MSG_HANDLER_STATE_MSG_START,
	IMU_MSG_HANDLER_STATE_MSG_RECEIVE
} IMU_MSG_HANDLER_STATE;

void IMU_MSG_HANDLER_INITIALIZE();

void IMU_MSG_HANDLER_UPDATE();

DRONE_POSE IMU_MSG_HANDLER_LAST_POSE();

bool IMU_MSG_HANDLER_NEW_POSE_AVAILABLE();

float IMU_MSG_GET_TIME();

#endif