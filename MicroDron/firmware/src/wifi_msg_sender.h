
#ifndef _WIFI_MSG_SENDER_H    
#define _WIFI_MSG_SENDER_H
#include <stdio.h>
#include "system_config.h"
#include "system_definitions.h"

typedef enum {
	WIFI_MSG_SENDER_STATE_WAIT,
	WIFI_MSG_SENDER_STATE_SEND
} WIFI_MSG_SENDER_STATE;

void WIFI_MSG_SENDER_INITIALIZE();

void WIFI_MSG_SENDER_UPDATE();

bool WIFI_MSG_SENDER_LAST_MSG_SENT();

bool WIFI_MSG_SENDER_SEND_MSG(unsigned char* msg, size_t size);

#endif 

