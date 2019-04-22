#ifndef _IMU_MSG_HANDLER_H 
#define _IMU_MSG_HANDLER_H
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "system_config.h"
#include "system_definitions.h"
#include "drone_control/drone_pose.h"

/**
 *Simple serial comms handler to obtain IMU data
 * 
 */


typedef enum {
	IMU_MSG_HANDLER_STATE_INIT,
	IMU_MSG_HANDLER_STATE_MSG_START,
	IMU_MSG_HANDLER_STATE_MSG_RECEIVE
} IMU_MSG_HANDLER_STATE;
/**
 * Initializes everything that is needed to receive messages from IMU
 */
void IMU_MSG_HANDLER_INITIALIZE();

/**
 * Updates IMU MESSAGE HANDLER's state machine
 */
void IMU_MSG_HANDLER_UPDATE();

/**
 * Get last valid IMU_POSE from HANDLER
 * @return IMU_POSE
 */
DRONE_POSE IMU_MSG_HANDLER_LAST_POSE();

/**
 * Get whether there is a new IMU pose available
 * @return  bool
 */
bool IMU_MSG_HANDLER_NEW_POSE_AVAILABLE();

float IMU_MSG_GET_TIME();

#endif