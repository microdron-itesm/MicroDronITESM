#include "app.h"
#include <stdint.h> 
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include <stdio.h>

unsigned char readcode;
unsigned char readyIMU = '\0';
unsigned char arreglo[20] = {'\0'};
unsigned char buffer[10] = {'\0'};
int dutycycle0 = 2000;
int dutycycle1 = 2000;
int dutycycle2 = 2000;
int dutycycle3 = 2000;
float yaw, roll, pitch; //en verdad es float
int result = 0;
int x = 0;
int i;

APP_DATA appData;

void APP_Initialize(void) {
    DRV_TMR0_Start();
    DRV_TMR1_Start();
    DRV_USART0_Initialize();
    DRV_USART1_Initialize();
    DRV_OC0_Start();
    DRV_OC1_Start();
    DRV_OC2_Start();
    DRV_OC3_Start();
    //DRV_OC0_PulseWidthSet (1250);
    //DRV_OC1_PulseWidthSet (2500);
    //DRV_OC2_PulseWidthSet (3750);
    //DRV_OC3_PulseWidthSet (5000);
    appData.state = APP_STATE_INIT;
    LATAbits.LATA2 = 0b0;
    TRISAbits.TRISA2 = 0b0;
}

void APP_Tasks(void) {
    /* Check the application's current state. */
    switch (appData.state) {
            /* Application's initial state. */
        case APP_STATE_INIT:
        {
            bool appInitialized = true;
            if (appInitialized) {
                appData.state = APP_STATE_SERVICE_TASKS;
            }
        }
            break;
        case APP_STATE_SERVICE_TASKS:
        {
            DRV_TMR1_CounterClear();
            while (1) {
                //if (!DRV_USART0_ReceiverBufferIsEmpty()) {
                //    readcode = DRV_USART0_ReadByte();
                //}
                if(abs((int) yaw) < 20){
                    readcode = 'U';
                }else{
                    readcode = 'D';
                }
                
                switch (readcode) {
                    case 'U':
                    {
                        dutycycle0 = 5000;
                        DRV_OC0_PulseWidthSet(dutycycle0);
                        DRV_OC1_PulseWidthSet(dutycycle0);
                        DRV_OC2_PulseWidthSet(dutycycle0);
                        DRV_OC3_PulseWidthSet(dutycycle0);
                        readcode = '\0';
                    }
                        break;
                    case 'D':
                    {
                        dutycycle0 = 0;
                        DRV_OC0_PulseWidthSet(dutycycle0);
                        DRV_OC1_PulseWidthSet(dutycycle0);
                        DRV_OC2_PulseWidthSet(dutycycle0);
                        DRV_OC3_PulseWidthSet(dutycycle0);
                        readcode = '\0';
                    }
                        break;
                    case 'L':
                    {
                        dutycycle0 = 5000;
                        dutycycle1 = 0;
                        DRV_OC0_PulseWidthSet(dutycycle0);
                        DRV_OC1_PulseWidthSet(dutycycle0);
                        DRV_OC2_PulseWidthSet(dutycycle1);
                        DRV_OC3_PulseWidthSet(dutycycle1);
                        readcode = '\0';
                    }
                        break;
                    case 'R':
                    {
                        dutycycle0 = 5000;
                        dutycycle1 = 0;
                        DRV_OC0_PulseWidthSet(dutycycle1);
                        DRV_OC1_PulseWidthSet(dutycycle1);
                        DRV_OC2_PulseWidthSet(dutycycle0);
                        DRV_OC3_PulseWidthSet(dutycycle0);
                        readcode = '\0';
                    }
                        break;
                    case 'A':
                    {
                        dutycycle0 -= 500;
                        if (dutycycle0 < 0) {
                            dutycycle0 = 0;
                        }
                        dutycycle1 = 0;
                        DRV_OC0_PulseWidthSet(dutycycle1);
                        DRV_OC1_PulseWidthSet(dutycycle1);
                        DRV_OC2_PulseWidthSet(dutycycle0);
                        DRV_OC3_PulseWidthSet(dutycycle0);
                        readcode = '\0';
                    }
                        break;
                    case 'S':
                    {
                        dutycycle0 -= 500;
                        if (dutycycle0 < 0) {
                            dutycycle0 = 0;
                        }
                        dutycycle1 = 0;
                        DRV_OC0_PulseWidthSet(dutycycle0);
                        DRV_OC1_PulseWidthSet(dutycycle0);
                        DRV_OC2_PulseWidthSet(dutycycle1);
                        DRV_OC3_PulseWidthSet(dutycycle1);
                        readcode = '\0';
                    }
                        break;
                    case 'B':
                    {
                        dutycycle0 += 500;
                        if (dutycycle0 > 5000) {
                            dutycycle0 = 5000;
                        }
                        dutycycle1 = 0;
                        DRV_OC0_PulseWidthSet(dutycycle1);
                        DRV_OC1_PulseWidthSet(dutycycle1);
                        DRV_OC2_PulseWidthSet(dutycycle0);
                        DRV_OC3_PulseWidthSet(dutycycle0);
                        readcode = '\0';
                    }
                        break;
                    case 'C':
                    {
                        dutycycle0 += 500;
                        if (dutycycle0 > 5000) {
                            dutycycle0 = 5000;
                        }
                        dutycycle1 = 0;
                        DRV_OC0_PulseWidthSet(dutycycle0);
                        DRV_OC1_PulseWidthSet(dutycycle0);
                        DRV_OC2_PulseWidthSet(dutycycle1);
                        DRV_OC3_PulseWidthSet(dutycycle1);
                        readcode = '\0';
                    }
                        break;

                    default:
                    {
                    }
                        break;
                }

                if (!DRV_USART1_ReceiverBufferIsEmpty()) {
                    readyIMU = DRV_USART1_ReadByte();
                    arreglo[x] = readyIMU;
                    x++;

                    if (readyIMU == '\n') {
                        result = sscanf(arreglo + 1, "%f %f %f", &yaw, &pitch, &roll);
                        
                        x = 0;
                        unsigned char buffer1[10] = {'\0'};
                        unsigned char buffer2[10] = {'\0'};
                        unsigned char buffer3[10] = {'\0'};
                        int ret = snprintf(buffer1, sizeof buffer1, "%f", yaw);
                        ret = snprintf(buffer2, sizeof buffer2, "%f", pitch);
                        ret = snprintf(buffer3, sizeof buffer3, "%f", roll);

                        for (i = 0; i < 10; i++) {
                            DRV_USART0_WriteByte(buffer1[i]);
                        }
                        DRV_USART0_WriteByte(' ');

                        for (i = 0; i < 10; i++) {
                            DRV_USART0_WriteByte(buffer2[i]);
                        }

                        DRV_USART0_WriteByte(' ');

                        for (i = 0; i < 10; i++) {
                            DRV_USART0_WriteByte(buffer3[i]);
                        }

                        DRV_USART0_WriteByte('\n');
                        memset(arreglo, 0, sizeof arreglo);
                        memset(buffer, 0, sizeof buffer);
                    }

                    //DRV_USART0_WriteByte(yaw);

                }
                switch (readyIMU) {
                    case 'k':
                    {

                    }
                        break;
                    default:
                    {

                    }
                        break;
                }
                /*while (DRV_TMR0_CounterValueGet() < 10000){
                }
                DRV_TMR1_CounterClear ();
                PORTAbits.RA2 = 0b1;
                while (DRV_TMR0_CounterValueGet() < 10000){
                }
                DRV_TMR1_CounterClear ();
                PORTAbits.RA2 = 0b0;*/
            }
        }
            break;

            /* TODO: implement your application state machine.*/


            /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
        }
            break;
    }
}