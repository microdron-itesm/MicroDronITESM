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
DRONE_CTRL_MOTOR_OUTPUT LAST_MANUAL_CONTROL;

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
    
    LAST_MANUAL_CONTROL.bottomLeft = 0;
    LAST_MANUAL_CONTROL.bottomRight = 0;
    LAST_MANUAL_CONTROL.topLeft = 0;
    LAST_MANUAL_CONTROL.topRight = 0;
    
    LAST_DRONE_MSG = DRONE_MSG_TYPE_NONE;
    
    DRV_OC0_Start();
    DRV_OC1_Start();
    DRV_OC2_Start();
    DRV_OC3_Start();
    
    DRV_TMR0_Start();
    DRV_TMR0_CounterClear();
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
                    DRONE_CTRL_SET_TARGET_HEIGHT(LAST_UPDATE_SETPOINT.height);
                    DRONE_CTRL_SET_TARGET_PITCH(LAST_UPDATE_SETPOINT.pitch);
                    DRONE_CTRL_SET_TARGET_ROLL(LAST_UPDATE_SETPOINT.roll);
                    DRONE_CTRL_SET_TARGET_YAW(LAST_UPDATE_SETPOINT.yaw);
                    
                    DRONE_CTRL_MOTOR_OUTPUT motorOutput = DRONE_CTRL_GET_MOTOR_OUTPUT();
                    DRV_OC0_PulseWidthSet(motorOutput.bottomLeft);
                    DRV_OC1_PulseWidthSet(motorOutput.bottomRight);
                    DRV_OC2_PulseWidthSet(motorOutput.topRight);
                    DRV_OC3_PulseWidthSet(motorOutput.topLeft);
                    
                    break;
                }

                case DRONE_MSG_TYPE_MANUAL_CONTROL:
                {
                    DRV_OC0_PulseWidthSet(LAST_MANUAL_CONTROL.bottomLeft);
                    DRV_OC1_PulseWidthSet(LAST_MANUAL_CONTROL.bottomRight);
                    DRV_OC2_PulseWidthSet(LAST_MANUAL_CONTROL.topRight);
                    DRV_OC3_PulseWidthSet(LAST_MANUAL_CONTROL.topLeft);

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
        DRONE_CTRL_UPDATE(dronePose);
    }

    if(WIFI_MSG_SENDER_LAST_MSG_SENT()){
        unsigned char msgBuffer[50] = {'\0'};

        int ret = snprintf(msgBuffer, sizeof msgBuffer, "T:%d Y:%.2f P:%.2f R:%.2f H:%.2f\n", 
                DRV_TMR0_CounterValueGet(), dronePose.yaw, dronePose.pitch,
                    dronePose.roll, dronePose.height);

        
        WIFI_MSG_SENDER_SEND_MSG(msgBuffer, strlen(msgBuffer) + 1);
    }

    if(DRONE_MSG_HANDLER_NEW_MSG_AVAILABLE()){
        LAST_DRONE_MSG = DRONE_MSG_HANDLER_LAST_MSG_TYPE();

        switch(LAST_DRONE_MSG){
            case DRONE_MSG_TYPE_UPDATE_SETPOINTS:
            {
                LAST_UPDATE_SETPOINT = DRONE_MSG_HANDLER_DATA_UPDATE_SETPOINTS();
                break;
            }

            case DRONE_MSG_TYPE_MANUAL_CONTROL:
            {
                LAST_MANUAL_CONTROL = DRONE_MSG_HANDLER_DATA_MANUAL_CONTROL();
                break;
            }            
            default:
            {
                break;
            }
        }
    }   
}