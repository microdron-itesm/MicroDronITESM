#include "imu_msg_handler.h"

unsigned char IMU_MESSAGE[50] = {'\0'};
const unsigned short int  IMU_MESSAGE_MAX_SIZE = 50;
unsigned short int IMU_MESSAGE_INDEX = 0;
IMU_POSE IMU_LAST_POSE;
IMU_MSG_HANDLER_STATE HANDLER_STATE;
bool NEW_POSE_AVAILABLE = false;
/**
 * Initializes everything that is needed to receive messages from IMU
 */
void IMU_MSG_HANDLER_INITIALIZE(){  
    HANDLER_STATE = IMU_MSG_HANDLER_STATE_INIT;
    IMU_LAST_POSE.height = 0;
    IMU_LAST_POSE.pitch = 0;
    IMU_LAST_POSE.roll = 0;
    IMU_LAST_POSE.yaw = 0;
}

/**
 * Updates IMU MESSAGE HANDLER's state machine
 */
void IMU_MSG_HANDLER_UPDATE(){
    switch(HANDLER_STATE){
        case IMU_MSG_HANDLER_STATE_INIT:
        {
            HANDLER_STATE = IMU_MSG_HANDLER_STATE_MESSAGE_START;
            break;
        }
        
	case IMU_MSG_HANDLER_STATE_MESSAGE_START:
        {
            NEW_POSE_AVAILABLE = false;
            if(!DRV_USART1_ReceiverBufferIsEmpty()){
                bool NEW_IMU_MESSAGE = DRV_USART1_ReadByte() == ',';           

                if(NEW_IMU_MESSAGE){
                    HANDLER_STATE = IMU_MSG_HANDLER_STATE_MESSAGE_RECEIVE;
                }
            }
            break;
        }
        
	case IMU_MSG_HANDLER_STATE_MESSAGE_RECEIVE:
        {
            if(!DRV_USART1_ReceiverBufferIsEmpty()){
                unsigned char newByte = DRV_USART1_ReadByte();
                if(newByte != '\n' && IMU_MESSAGE_INDEX + 1 < IMU_MESSAGE_MAX_SIZE){
                    IMU_MESSAGE[IMU_MESSAGE_INDEX++] = newByte;
                }else{
                    int ret = sscanf(IMU_MESSAGE, "%f %f %f %f",
                            &IMU_LAST_POSE.yaw, &IMU_LAST_POSE.pitch, &IMU_LAST_POSE.roll, &IMU_LAST_POSE.height);
                    
                    NEW_POSE_AVAILABLE = ret == 4;
                    
                    memset(IMU_MESSAGE, 0, sizeof IMU_MESSAGE);
                    IMU_MESSAGE_INDEX = 0;
                    HANDLER_STATE = IMU_MSG_HANDLER_STATE_MESSAGE_START;
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
IMU_POSE IMU_MSG_HANDLER_GET_LAST_POSE(){
    return IMU_LAST_POSE;
}

/**
 * Get whether there is a new IMU pose available
 * @return  bool
 */
bool IMU_MSG_HANDLER_NEW_POSE_AVAILABLE(){
    return NEW_POSE_AVAILABLE;
}
