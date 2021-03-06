#include "wifi_msg_sender.h"

bool LAST_MSG_SENT = true;
WIFI_MSG_SENDER_STATE SENDER_STATE;

unsigned char CURRENT_MESSAGE[200] = {'\0'};
unsigned int CURRENT_MSG_INDEX = 0;
unsigned int CURRENT_MSG_SIZE = 0;

const unsigned int MAX_MSG_LENGHT = 200;

void WIFI_MSG_SENDER_INITIALIZE(){
    SENDER_STATE = WIFI_MSG_SENDER_STATE_WAIT;
}

void WIFI_MSG_SENDER_UPDATE(){
    switch(SENDER_STATE){
        case WIFI_MSG_SENDER_STATE_WAIT:
        {           
            if(!LAST_MSG_SENT){
                SENDER_STATE = WIFI_MSG_SENDER_STATE_SEND;
            }
  
            
            break;
        }
        case WIFI_MSG_SENDER_STATE_SEND:
        {   
            if(CURRENT_MSG_INDEX < CURRENT_MSG_SIZE){
                DRV_USART0_WriteByte(CURRENT_MESSAGE[CURRENT_MSG_INDEX++]);
            }else{
                LAST_MSG_SENT = true;
                memset(CURRENT_MESSAGE, '\0', sizeof CURRENT_MESSAGE);
                CURRENT_MSG_INDEX = 0;
                CURRENT_MSG_SIZE = 0;
                SENDER_STATE = WIFI_MSG_SENDER_STATE_WAIT;
            }
            break;
        }
        default:
        {
            break;
        }
    }
}

bool WIFI_MSG_SENDER_LAST_MSG_SENT(){
    return LAST_MSG_SENT;
}

bool WIFI_MSG_SENDER_SEND_MSG(unsigned char* msg, size_t size){
    if(!WIFI_MSG_SENDER_LAST_MSG_SENT()){
        return false;
    }
    LAST_MSG_SENT = false;
    CURRENT_MSG_SIZE = size;
    snprintf(CURRENT_MESSAGE, sizeof CURRENT_MESSAGE, "%s", msg);
    CURRENT_MSG_INDEX = 0;
    return true;
}