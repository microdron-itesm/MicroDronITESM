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

/**
*This is the main code for the PIC32 MicroDron project, the code runs 3 separate 
*state machines, one manages the communication from the IMU, another reads incoming data
*from the Wifi Module and the last one sends telemetry data through the Wifi Module.
*
*The drone control loop is only updated once a new valid pose is read from the IMU, roughly
*every 10 ms.
*
*By: Rodrigo Vazquez Villarreal rodv.95@gmail.com 
*    Alberto Jahuey Moncada     A01039835@itesm.mx
*/

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
float LAST_TIME_UPDATE;
long ITERATION_COUNTER;
long LAST_HEARTBEAT;
long MAX_HEARTBEAT_INTERVAL = 2000;

void APP_UpdateState(void);
long timer1CounterToMs(int ms);

void APP_Initialize(void) {
    ITERATION_COUNTER = 0;
    LAST_HEARTBEAT = 0;
    
    LAST_TIME_UPDATE = 0.0f;
    dronePose.zAccel = 0.0;
    dronePose.pitch = 0.0;
    dronePose.roll = 0.0;
    dronePose.yaw = 0.0;
    LAST_UPDATE_SETPOINT.height = 0;
    LAST_UPDATE_SETPOINT.pitch = 0;
    LAST_UPDATE_SETPOINT.roll = 0;
    LAST_UPDATE_SETPOINT.yaw = 0;
    
    CURRENT_MOTOR_OUTPUT.bottomLeft = 0;
    CURRENT_MOTOR_OUTPUT.bottomRight = 0;
    CURRENT_MOTOR_OUTPUT.topLeft = 0;
    CURRENT_MOTOR_OUTPUT.topRight = 0;
    
    LAST_DRONE_MSG = DRONE_MSG_TYPE_KILL_MOTORS;
    
    DRV_OC0_Start();
    DRV_OC1_Start();
    DRV_OC2_Start();
    DRV_OC3_Start();
    
    DRV_TMR0_Start();
    DRV_TMR1_Start();
    
    appData.state = APP_STATE_INIT;
    DRONE_CTRL_INITIALIZE();
    DRV_OC0_PulseWidthSet(0);
    DRV_OC1_PulseWidthSet(0);
    DRV_OC2_PulseWidthSet(0);
    DRV_OC3_PulseWidthSet(0); 
    DRONE_CTRL_USE_MANUAL_THRUST(true);
    DRONE_CTRL_SET_MANUAL_THRUST(0.0);
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
                    DRV_OC0_PulseWidthSet((uint32_t) CURRENT_MOTOR_OUTPUT.topLeft);
                    DRV_OC1_PulseWidthSet((uint32_t) CURRENT_MOTOR_OUTPUT.topRight);
                    DRV_OC2_PulseWidthSet((uint32_t) CURRENT_MOTOR_OUTPUT.bottomLeft);
                    DRV_OC3_PulseWidthSet((uint32_t) CURRENT_MOTOR_OUTPUT.bottomRight);
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
        LAST_TIME_UPDATE = IMU_MSG_GET_TIME();
        DRONE_CTRL_UPDATE(dronePose, IMU_MSG_GET_TIME());
    }

   
    if(DRONE_MSG_HANDLER_NEW_MSG_AVAILABLE()){
        switch(DRONE_MSG_HANDLER_LAST_MSG_TYPE()){
            case DRONE_MSG_TYPE_HEARTBEAT:
            {
   
                LAST_HEARTBEAT = ITERATION_COUNTER;
                
                break;
            }
            case DRONE_MSG_TYPE_UPDATE_SETPOINTS:
            {
                LAST_UPDATE_SETPOINT = DRONE_MSG_HANDLER_DATA_UPDATE_SETPOINTS();
                DRONE_CTRL_SET_MANUAL_THRUST(LAST_UPDATE_SETPOINT.height);
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
            case DRONE_MSG_TYPE_KILL_MOTORS:
            {
                CURRENT_MOTOR_OUTPUT.bottomLeft = 0;
                CURRENT_MOTOR_OUTPUT.bottomRight = 0;
                CURRENT_MOTOR_OUTPUT.topLeft = 0;
                CURRENT_MOTOR_OUTPUT.topRight = 0;
                break;
            }
            case DRONE_MSG_TYPE_UPDATE_PID:
            {                   
                switch(DRONE_MSG_HANDLER_GET_PID_UPDATE_TARGET()){
                    case 'P':
                    {
                        DRONE_CTRL_SET_PITCH_PID(DRONE_MSG_HANDLER_GET_PID_CONFIG_UPDATE());
                        break;
                    }
                    case 'R':
                    {
                        DRONE_CTRL_SET_ROLL_PID(DRONE_MSG_HANDLER_GET_PID_CONFIG_UPDATE());
                        break;
                    }
                    case 'Y':
                    {
                        DRONE_CTRL_SET_YAW_PID(DRONE_MSG_HANDLER_GET_PID_CONFIG_UPDATE());
                        break;
                    }
                    case 'H':
                    {
                        DRONE_CTRL_SET_HEIGHT_PID(DRONE_MSG_HANDLER_GET_PID_CONFIG_UPDATE());
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
                break;
            }
            case DRONE_MSG_TYPE_UPDATE_K:
            {
                DRONE_CTRL_SET_K(DRONE_MSG_HANDLER_GET_LAST_K());
                break;
            }
            default:
            {
                break;
            }
        }
        
        if(LAST_DRONE_MSG == DRONE_MSG_TYPE_UPDATE_SETPOINTS && 
                    (DRONE_MSG_HANDLER_LAST_MSG_TYPE() == DRONE_MSG_TYPE_UPDATE_PID || 
                    DRONE_MSG_HANDLER_LAST_MSG_TYPE() == DRONE_MSG_TYPE_UPDATE_K)){
            LAST_DRONE_MSG = DRONE_MSG_TYPE_UPDATE_SETPOINTS;
        }else if(DRONE_MSG_HANDLER_LAST_MSG_TYPE() != DRONE_MSG_TYPE_HEARTBEAT){
            LAST_DRONE_MSG = DRONE_MSG_HANDLER_LAST_MSG_TYPE();
        }
    }   

    /*if(ITERATION_COUNTER - LAST_HEARTBEAT > MAX_HEARTBEAT_INTERVAL){
                CURRENT_MOTOR_OUTPUT.bottomLeft = 0;
                CURRENT_MOTOR_OUTPUT.bottomRight = 0;
                CURRENT_MOTOR_OUTPUT.topLeft = 0;
                CURRENT_MOTOR_OUTPUT.topRight = 0;
                LAST_DRONE_MSG = DRONE_MSG_TYPE_KILL_MOTORS;
    }*/
    
    if(abs(dronePose.pitch) > 50 || abs(dronePose.roll) > 50){
                CURRENT_MOTOR_OUTPUT.bottomLeft = 0;
                CURRENT_MOTOR_OUTPUT.bottomRight = 0;
                CURRENT_MOTOR_OUTPUT.topLeft = 0;
                CURRENT_MOTOR_OUTPUT.topRight = 0;
                LAST_DRONE_MSG = DRONE_MSG_TYPE_KILL_MOTORS;    
    }
    
    if(WIFI_MSG_SENDER_LAST_MSG_SENT()){
        unsigned char msgBuffer[200] = {'\0'};
        PID_CONFIG pitchPid = DRONE_CTRL_GET_PITCH_PID();
        PID_CONFIG yawPid = DRONE_CTRL_GET_YAW_PID();
        PID_CONFIG rollPid = DRONE_CTRL_GET_ROLL_PID();
        PID_CONFIG heightPid = DRONE_CTRL_GET_HEIGHT_PID();

        int ret = snprintf(msgBuffer, sizeof msgBuffer, 
               "Y:%.2f M:%d P:%.2f R:%.2f H:%.2f  M:%.1f %.1f %.1f %.1f PID: %.0f Y:%f %f %f P:%f %f %f R:%f %f %f H:%f %f %f %i K"
                , dronePose.yaw, LAST_DRONE_MSG ,dronePose.pitch,
                    dronePose.roll, dronePose.zAccel,
                CURRENT_MOTOR_OUTPUT.topLeft, CURRENT_MOTOR_OUTPUT.topRight,
                     CURRENT_MOTOR_OUTPUT.bottomLeft, CURRENT_MOTOR_OUTPUT.bottomRight,
                    DRONE_CTRL_GET_K(), yawPid.p, yawPid.i, yawPid.d, pitchPid.p, 
                    pitchPid.i, pitchPid.d, rollPid.p, rollPid.i, rollPid.d, 
                    heightPid.p, heightPid.i, heightPid.d, ITERATION_COUNTER - LAST_HEARTBEAT);
        
        WIFI_MSG_SENDER_SEND_MSG(msgBuffer, strlen(msgBuffer));
    }
}
