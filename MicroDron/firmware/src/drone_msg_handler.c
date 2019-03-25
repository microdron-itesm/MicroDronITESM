
#include "drone_msg_handler.h"


DRONE_MSG_TYPE LAST_MSG_TYPE;
DRONE_MSG_HANDLER_STATE DRONE_MSG_CURRENT_STATE;
unsigned char DRONE_MSG[50] = {'\0'};
unsigned short int DRONE_MSG_INDEX = 0;
unsigned short int DRONE_MSG_MAX_SIZE = 50;

DRONE_MSG_DATA_UPDATE_SETPOINTS LAST_DATA_UPDATE_SETPOINTS;
DRONE_CTRL_MOTOR_OUTPUT LAST_DATA_MANUAL_CONTROL;

bool NEW_DRONE_MESSAGE = false;

void DRONE_MSG_HANDLER_INITIALIZE(){
    LAST_MSG_TYPE = DRONE_MSG_TYPE_NONE;
    DRONE_MSG_CURRENT_STATE = DRONE_MSG_HANDLER_STATE_MSG_START;
}


void DRONE_MSG_HANDLER_UPDATE(){

    switch(DRONE_MSG_CURRENT_STATE){
        case DRONE_MSG_HANDLER_STATE_MSG_START:
        {   
            NEW_DRONE_MESSAGE = false;
            LAST_MSG_TYPE = DRONE_MSG_TYPE_NONE;
                    
            if(!DRV_USART0_ReceiverBufferIsEmpty()){
                bool NEW_MSG = DRV_USART0_ReadByte() == ',';
                if(NEW_MSG){
                    DRONE_MSG_CURRENT_STATE = DRONE_MSG_HANDLER_STATE_MSG_RECEIVE;
                }
            }
            break;
        }
        case DRONE_MSG_HANDLER_STATE_MSG_RECEIVE:
        {
            if(!DRV_USART0_ReceiverBufferIsEmpty()){
                unsigned char newByte = DRV_USART0_ReadByte();
                
                if(newByte != '\n' && DRONE_MSG_INDEX + 1 < DRONE_MSG_MAX_SIZE ){
                    DRONE_MSG[DRONE_MSG_INDEX++] = newByte;
                }else{
                    char MSG_ID = {'\0'};
                    float firstValue = 0;
                    float secondValue = 0;
                    float thirdValue = 0;
                    float fourthValue = 0;

                    int ret = sscanf(DRONE_MSG, "%c %f %f %f %f",
                            &MSG_ID, &firstValue, &secondValue, &thirdValue, &fourthValue);
                    NEW_DRONE_MESSAGE = ret == 5;
                    
                    if(NEW_DRONE_MESSAGE){
                        switch(MSG_ID){
                            case 'S':
                            {

                                LAST_MSG_TYPE = DRONE_MSG_TYPE_UPDATE_SETPOINTS;
                                
                                LAST_DATA_UPDATE_SETPOINTS.yaw = firstValue;
                                LAST_DATA_UPDATE_SETPOINTS.pitch = secondValue;
                                LAST_DATA_UPDATE_SETPOINTS.roll = thirdValue;
                                LAST_DATA_UPDATE_SETPOINTS.height = fourthValue;
                                break;
                            }
                          
                            case 'M':
                            {
                                LAST_MSG_TYPE = DRONE_MSG_TYPE_MANUAL_CONTROL;

                                LAST_DATA_MANUAL_CONTROL.bottomLeft = firstValue;
                                LAST_DATA_MANUAL_CONTROL.bottomRight = secondValue;
                                LAST_DATA_MANUAL_CONTROL.topRight = thirdValue;
                                LAST_DATA_MANUAL_CONTROL.topLeft = fourthValue;
                          

                            }
                            case 'K':
                            {
                                LAST_MSG_TYPE = DRONE_MSG_TYPE_KILL_MOTORS;
                                break;
                            }
                            
                            default:
                            {
                                LAST_MSG_TYPE = DRONE_MSG_TYPE_NONE;
                                break;
                            }
                        }
                    }

                    memset(DRONE_MSG, 0, sizeof DRONE_MSG);
                    DRONE_MSG_INDEX = 0;
                    DRONE_MSG_CURRENT_STATE = DRONE_MSG_HANDLER_STATE_MSG_START;
                }
            
            }
            break;
        }
        
    }
}

DRONE_MSG_TYPE DRONE_MSG_HANDLER_LAST_MSG_TYPE(){
    return LAST_MSG_TYPE;
}

DRONE_MSG_DATA_UPDATE_SETPOINTS DRONE_MSG_HANDLER_DATA_UPDATE_SETPOINTS(){
    return LAST_DATA_UPDATE_SETPOINTS;
}

DRONE_CTRL_MOTOR_OUTPUT DRONE_MSG_HANDLER_DATA_MANUAL_CONTROL(){
    return LAST_DATA_MANUAL_CONTROL;
}

bool DRONE_MSG_HANDLER_NEW_MSG_AVAILABLE(){
    return NEW_DRONE_MESSAGE;
}
