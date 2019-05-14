
#ifndef _WIFI_MSG_SENDER_H    
#define _WIFI_MSG_SENDER_H
#include <stdio.h>
#include "system_config.h"
#include "system_definitions.h"

/**
 *Simple serial comms handler to manage sending telemetry messages from Wifi Module.
 *
 *
 *A drone telemetry message starts with a ',', the state machine waits until a new message
 *is queued, once a message is queued a new one cant be added until the first one is completly sent.
 *The state machines starts sending character by character until it reaches the end of the message or 
 *the max message size is reached.
 */

typedef enum {
	WIFI_MSG_SENDER_STATE_WAIT,
	WIFI_MSG_SENDER_STATE_SEND
} WIFI_MSG_SENDER_STATE;

void WIFI_MSG_SENDER_INITIALIZE();

void WIFI_MSG_SENDER_UPDATE();

bool WIFI_MSG_SENDER_LAST_MSG_SENT();

bool WIFI_MSG_SENDER_SEND_MSG(unsigned char* msg, size_t size);

#endif 

