
#include "drone_msg_handler.h"


DRONE_MSG_TYPE LAST_MSG_TYPE;
DRONE_MSG_HANDLER_STATE DRONE_MSG_CURRENT_STATE;
unsigned char DRONE_MSG[150] = {'\0'};
unsigned short int DRONE_MSG_INDEX = 0;
unsigned short int DRONE_MSG_MAX_SIZE = 150;

DRONE_MSG_DATA_UPDATE_SETPOINTS LAST_DATA_UPDATE_SETPOINTS;
DRONE_CTRL_MOTOR_OUTPUT LAST_DATA_MANUAL_CONTROL;
PID_CONFIG LAST_PID_UPDATE;

bool NEW_DRONE_MESSAGE = false;

char MSG_ID = '\0';
char PID_UPDATE_TARGET = {'\0'};
float LAST_K_VALUE = 0.0f;

float firstValue = 0;
float secondValue = 0;
float thirdValue = 0;
float fourthValue = 0;
float fifthValue = 0;
float sixthValue = 0;
float seventhValue = 0;
float eighthValue = 0;
float ninethValue = 0;
                    
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

                    int ret = sscanf(DRONE_MSG, "%c",
                            &MSG_ID);
                    
                    if(MSG_ID == 'S' || MSG_ID == 'M'){
                        ret = sscanf(DRONE_MSG, "%c %f %f %f %f",
                            &MSG_ID, &firstValue, &secondValue, &thirdValue, &fourthValue);
                        NEW_DRONE_MESSAGE = ret == 5;
                        
                    }else if(MSG_ID == 'P'){
                        ret = sscanf(DRONE_MSG, "%c %c %f %f %f %f %f %f %f %f %f",
                            &MSG_ID, &PID_UPDATE_TARGET, &firstValue, &secondValue, &thirdValue,
                                                         &fourthValue, &fifthValue, &sixthValue,
                                                         &seventhValue, &eighthValue, &ninethValue);
                        NEW_DRONE_MESSAGE = ret == 11;
                        
                    }else if(MSG_ID == 'K'){
                        ret = sscanf(DRONE_MSG, "%c %f",
                            &MSG_ID, &firstValue);
                        NEW_DRONE_MESSAGE = ret == 2;                        
                    }else{
                        NEW_DRONE_MESSAGE = true;
                    }
                    
                    
                    if(NEW_DRONE_MESSAGE){
                        switch(MSG_ID){
                            case 'S':
                            {

                                LAST_MSG_TYPE = DRONE_MSG_TYPE_UPDATE_SETPOINTS;
                                
                                LAST_DATA_UPDATE_SETPOINTS.yaw = firstValue;
                                LAST_DATA_UPDATE_SETPOINTS.pitch = secondValue;
                                LAST_DATA_UPDATE_SETPOINTS.roll = thirdValue;
                                LAST_DATA_UPDATE_SETPOINTS.thrust = fourthValue;
                                break;
                            }
                          
                            case 'M':
                            {
                                LAST_MSG_TYPE = DRONE_MSG_TYPE_MANUAL_CONTROL;

                                LAST_DATA_MANUAL_CONTROL.bottomLeft = firstValue;
                                LAST_DATA_MANUAL_CONTROL.bottomRight = secondValue;
                                LAST_DATA_MANUAL_CONTROL.topRight = thirdValue;
                                LAST_DATA_MANUAL_CONTROL.topLeft = fourthValue;
                                break;
                                
                            }
                            case 'E':
                            {
                                LAST_MSG_TYPE = DRONE_MSG_TYPE_KILL_MOTORS;
                                break;
                            }
                            case '1':
                            {
                                LAST_MSG_TYPE = DRONE_MSG_TYPE_MANUAL_CONTROL;

                                LAST_DATA_MANUAL_CONTROL.bottomLeft = LAST_DATA_MANUAL_CONTROL.bottomLeft - 50;
                                LAST_DATA_MANUAL_CONTROL.bottomRight =  LAST_DATA_MANUAL_CONTROL.bottomRight - 50;
                                LAST_DATA_MANUAL_CONTROL.topRight =  LAST_DATA_MANUAL_CONTROL.topRight - 50;
                                LAST_DATA_MANUAL_CONTROL.topLeft =  LAST_DATA_MANUAL_CONTROL.topLeft - 50;

                                break;
                            }
                            case '2':
                            {
                                LAST_MSG_TYPE = DRONE_MSG_TYPE_MANUAL_CONTROL;

                                LAST_DATA_MANUAL_CONTROL.bottomLeft = LAST_DATA_MANUAL_CONTROL.bottomLeft + 50;
                                LAST_DATA_MANUAL_CONTROL.bottomRight =  LAST_DATA_MANUAL_CONTROL.bottomRight + 50;
                                LAST_DATA_MANUAL_CONTROL.topRight =  LAST_DATA_MANUAL_CONTROL.topRight + 50;
                                LAST_DATA_MANUAL_CONTROL.topLeft =  LAST_DATA_MANUAL_CONTROL.topLeft + 50;
                                
                                break;
                            }
                            case 'P':
                            {
                                LAST_MSG_TYPE = DRONE_MSG_TYPE_UPDATE_PID;

                                LAST_PID_UPDATE.p = firstValue;
                                LAST_PID_UPDATE.i = secondValue;
                                LAST_PID_UPDATE.d = thirdValue;
                                LAST_PID_UPDATE.clamped = fourthValue > 0.0;
                                LAST_PID_UPDATE.maxOutput = fifthValue;
                                LAST_PID_UPDATE.minOutput = sixthValue;
                                LAST_PID_UPDATE.continuous = seventhValue > 0.0;
                                LAST_PID_UPDATE.maxInput = eighthValue;
                                LAST_PID_UPDATE.minInput = ninethValue;

                                break;
                            }
                            case 'K':
                            {
                                LAST_MSG_TYPE = DRONE_MSG_TYPE_UPDATE_K;
                                LAST_K_VALUE = firstValue;
                                break;
                            }
                            case 'L':
                            {
                                LAST_MSG_TYPE = DRONE_MSG_TYPE_HEARTBEAT;
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

PID_CONFIG DRONE_MSG_HANDLER_GET_PID_CONFIG_UPDATE(){
    return LAST_PID_UPDATE;
}

char DRONE_MSG_HANDLER_GET_PID_UPDATE_TARGET(){
    return PID_UPDATE_TARGET;
}

float DRONE_MSG_HANDLER_GET_LAST_K(){
    return LAST_K_VALUE;
}
