// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


#include "app.h"
#include "imu_msg_handler.h"
#include "wifi_msg_sender.h"
#include "drone_msg_handler.h"
#include "drone_control/drone_control.h"

APP_DATA appData;
DRONE_POSE dronePose;
DRONE_MSG_TYPE LAST_DRONE_MSG;
DRONE_MSG_DATA_UPDATE_SETPOINTS LAST_UPDATE_SETPOINT;
DRONE_CTRL_MOTOR_OUTPUT CURRENT_MOTOR_OUTPUT;

void APP_UpdateState(void);

void APP_Initialize(void) {
    dronePose.height = 0.0;
    dronePose.pitch = 0.0;
    dronePose.roll = 0.0;
    dronePose.yaw = 0.0;
    LAST_UPDATE_SETPOINT.height = 0;
    LAST_UPDATE_SETPOINT.pitch = 0;
    LAST_UPDATE_SETPOINT.roll = 0;
    LAST_UPDATE_SETPOINT.yaw = 0;
    
    CURRENT_MOTOR_OUTPUT.bottom = 0;
    CURRENT_MOTOR_OUTPUT.midRight = 0;
    CURRENT_MOTOR_OUTPUT.midLeft = 0;
    CURRENT_MOTOR_OUTPUT.top = 0;
    
    LAST_DRONE_MSG = DRONE_MSG_TYPE_KILL_MOTORS;
    
    DRV_OC0_Start();
    DRV_OC1_Start();
    DRV_OC2_Start();
    DRV_OC3_Start();
    
    DRV_TMR0_Start();
    DRV_TMR1_Start();

    appData.state = APP_STATE_INIT;
    DRONE_CTRL_INITIALIZE();
    
}

void APP_Tasks(void) {
    APP_UpdateState();
    
    /* Check the application's current state. */
    switch (appData.state) {
        case APP_STATE_INIT:
        {

            appData.state = APP_STATE_SERVICE_TASKS;
            break;
        }

        case APP_STATE_SERVICE_TASKS:
        {
                    
            switch(LAST_DRONE_MSG){
                case DRONE_MSG_TYPE_UPDATE_SETPOINTS:
                {
                    CURRENT_MOTOR_OUTPUT = DRONE_CTRL_GET_MOTOR_OUTPUT();

                }
                case DRONE_MSG_TYPE_MANUAL_CONTROL:
                {
                    DRV_OC0_PulseWidthSet((uint32_t) CURRENT_MOTOR_OUTPUT.bottom);
                    DRV_OC1_PulseWidthSet((uint32_t) CURRENT_MOTOR_OUTPUT.midRight);
                    DRV_OC2_PulseWidthSet((uint32_t) CURRENT_MOTOR_OUTPUT.midLeft);
                    DRV_OC3_PulseWidthSet((uint32_t) CURRENT_MOTOR_OUTPUT.top);
                    break;
                }
                case DRONE_MSG_TYPE_KILL_MOTORS:
                {
                    DRV_OC0_PulseWidthSet(0);
                    DRV_OC1_PulseWidthSet(0);
                    DRV_OC2_PulseWidthSet(0);
                    DRV_OC3_PulseWidthSet(0);
                    break;
                }
                default:
                {
                    break;
                }
            }
            
            break;
        }
          /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
    

}

void APP_UpdateState(){
    if(IMU_MSG_HANDLER_NEW_POSE_AVAILABLE()){
        dronePose = IMU_MSG_HANDLER_LAST_POSE();
        dronePose.height = 0.0;
        DRONE_CTRL_UPDATE(dronePose);
    }

    if(DRONE_MSG_HANDLER_NEW_MSG_AVAILABLE()){
        LAST_DRONE_MSG = DRONE_MSG_HANDLER_LAST_MSG_TYPE();

        switch(LAST_DRONE_MSG){
            case DRONE_MSG_TYPE_UPDATE_SETPOINTS:
            {
                LAST_UPDATE_SETPOINT = DRONE_MSG_HANDLER_DATA_UPDATE_SETPOINTS();
                DRONE_CTRL_SET_TARGET_HEIGHT(LAST_UPDATE_SETPOINT.height);
                DRONE_CTRL_SET_TARGET_PITCH(LAST_UPDATE_SETPOINT.pitch);
                DRONE_CTRL_SET_TARGET_ROLL(LAST_UPDATE_SETPOINT.roll);
                DRONE_CTRL_SET_TARGET_YAW(LAST_UPDATE_SETPOINT.yaw);
                
                break;
            }

            case DRONE_MSG_TYPE_MANUAL_CONTROL:
            {
                CURRENT_MOTOR_OUTPUT = DRONE_MSG_HANDLER_DATA_MANUAL_CONTROL();
                break;
            }            
            default:
            {
                break;
            }
        }
    }   
    
    if(WIFI_MSG_SENDER_LAST_MSG_SENT()){
        unsigned char msgBuffer[100] = {'\0'};
        int ret = snprintf(msgBuffer, sizeof msgBuffer, 
                "Y:%.2f M:%d P:%.2f R:%.2f H:%.2f  M: %.1f %.1f %.1f %.1f\r"
                , dronePose.yaw, LAST_DRONE_MSG ,dronePose.pitch,
                    dronePose.roll, dronePose.height,
                CURRENT_MOTOR_OUTPUT.bottom, CURRENT_MOTOR_OUTPUT.midRight,
                     CURRENT_MOTOR_OUTPUT.midLeft, CURRENT_MOTOR_OUTPUT.top);
        WIFI_MSG_SENDER_SEND_MSG(msgBuffer, strlen(msgBuffer) + 1);
    }
}