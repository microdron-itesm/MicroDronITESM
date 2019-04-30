#include "imu_msg_handler.h"

unsigned char IMU_MESSAGE[50] = {'\0'};
const unsigned short int  IMU_MESSAGE_MAX_SIZE = 50;
unsigned short int IMU_MESSAGE_INDEX = 0;
DRONE_POSE IMU_LAST_POSE;
IMU_MSG_HANDLER_STATE IMU_MSG_CURRENT_STATE;
bool NEW_POSE_AVAILABLE = false;
float LAST_TIME = 0;

/**
 * Initializes everything that is needed to receive messages from IMU
 */
void IMU_MSG_HANDLER_INITIALIZE(){  
    IMU_MSG_CURRENT_STATE = IMU_MSG_HANDLER_STATE_INIT;
    IMU_LAST_POSE.zAccel = 0;
    IMU_LAST_POSE.pitch = 0;
    IMU_LAST_POSE.roll = 0;
    IMU_LAST_POSE.yaw = 0;
}

/**
 * Updates IMU MESSAGE HANDLER's state machine
 */
void IMU_MSG_HANDLER_UPDATE(){
    switch(IMU_MSG_CURRENT_STATE){
        case IMU_MSG_HANDLER_STATE_INIT:
        {
            IMU_MSG_CURRENT_STATE = IMU_MSG_HANDLER_STATE_MSG_START;
            break;
        }
        
	case IMU_MSG_HANDLER_STATE_MSG_START:
        {
            NEW_POSE_AVAILABLE = false;
            if(!DRV_USART1_ReceiverBufferIsEmpty()){
                bool NEW_IMU_MESSAGE = DRV_USART1_ReadByte() == ',';           

                if(NEW_IMU_MESSAGE){
                    IMU_MSG_CURRENT_STATE = IMU_MSG_HANDLER_STATE_MSG_RECEIVE;
                }
            }
            break;
        }
        
	case IMU_MSG_HANDLER_STATE_MSG_RECEIVE:
        {
            if(!DRV_USART1_ReceiverBufferIsEmpty()){
                unsigned char newByte = DRV_USART1_ReadByte();
                if(newByte != '\n' && IMU_MESSAGE_INDEX + 1 < IMU_MESSAGE_MAX_SIZE){
                    IMU_MESSAGE[IMU_MESSAGE_INDEX++] = newByte;
                }else{
                    int ret = sscanf(IMU_MESSAGE, "%f %f %f %f %f",
                            &IMU_LAST_POSE.yaw, &IMU_LAST_POSE.roll, &IMU_LAST_POSE.pitch, &IMU_LAST_POSE.zAccel, &LAST_TIME );
                    
                    NEW_POSE_AVAILABLE = ret == 5;
                    
                    memset(IMU_MESSAGE, 0, sizeof IMU_MESSAGE);
                    IMU_MESSAGE_INDEX = 0;
                    IMU_MSG_CURRENT_STATE = IMU_MSG_HANDLER_STATE_MSG_START;
                }
            }
            break;
        }
        
        default:{
            break;
        }
    }
}

/**
 * Get last valid IMU_POSE from HANDLER
 * @return IMU_POSE
 */
DRONE_POSE IMU_MSG_HANDLER_LAST_POSE(){
    return IMU_LAST_POSE;
}

/**
 * Get whether there is a new IMU pose available
 * @return  bool
 */
bool IMU_MSG_HANDLER_NEW_POSE_AVAILABLE(){
    return NEW_POSE_AVAILABLE;
}

float IMU_MSG_GET_TIME(){
    return LAST_TIME;
}


