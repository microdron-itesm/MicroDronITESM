/*******************************************************************************
  Output Compare Driver Interface Declarations for Static Single Instance Driver

  Company:
    Microchip Technology Inc.

  File Name:
    help_drv_oc.h

  Summary:
    Output Compare driver interface declarations for the static single instance driver.

  Description:
    The Output Compare device driver provides a simple interface to manage the Output 
    Compare modules on Microchip microcontrollers. This file defines the interface
    Declarations for the Output Compare driver.
    
  Remarks:
    Static interfaces incorporate the driver instance number within the names
    of the routines, eliminating the need for an object ID or object handle.
    
    Static single-open interfaces also eliminate the need for the open handle.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTOCULAR PURPOSE.
IN NO EVENT SHALL MOCROCHIP OR ITS LOCENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STROCT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVOCES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/
//DOM-IGNORE-END
#ifndef _DRV_OC_H
#define _DRV_OC_H

#include "system_config.h"
#include "driver/driver_common.h"
#include "system/common/sys_module.h"

// *****************************************************************************
/* OC Driver Module Index Numbers

  Summary:
    OC driver index definitions.

  Description:
    These constants provide OC Driver index definitions.

  Remarks:
    These constants should be used in place of hard-coded numeric literals.

    These values should be passed into the DRV_OC_Initialize and
    DRV_OC_Start routines to identify the driver instance in use.
*/

#define DRV_OC_INDEX_0         0
#define DRV_OC_INDEX_1         1
#define DRV_OC_INDEX_2         2
#define DRV_OC_INDEX_3         3
#define DRV_OC_INDEX_4         4
#define DRV_OC_INDEX_5         5
#define DRV_OC_INDEX_6         6
#define DRV_OC_INDEX_7         7
#define DRV_OC_INDEX_8         8
#define DRV_OC_INDEX_9         9
#define DRV_OC_INDEX_10        10
#define DRV_OC_INDEX_11        11
#define DRV_OC_INDEX_12        12
#define DRV_OC_INDEX_13        13
#define DRV_OC_INDEX_14        14
#define DRV_OC_INDEX_15        15

// *****************************************************************************
// *****************************************************************************
// Section: Interface Headers for the static driver
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    SYS_MODULE_OBJ DRV_OC_Initialize(const SYS_MODULE_INDEX index,
                                     const SYS_MODULE_INIT * const init);

  Summary:
    Initializes the Comparator instance for the specified driver index.
    <p><b>Implementation:</b> Static</p>	

  Description:
    This routine initializes the Output Compare driver instance for the specified 
	driver instance, making it ready for clients to use it. The initialization
    routine is specified by the MHC parameters. The driver instance index is
    independent of the Output Compare module ID. For example, driver instance 0 
	can be assigned to Output Compare 1.

  Precondition:
    None.

  Parameters:
    drvIndex        - Index for the driver instance to be initialized

    init            - Pointer to a data structure containing any data necessary
                      to initialize the driver. This pointer may be null if no
                      data is required because static overrides have been
                      provided.

  Returns:
    If successful, returns a valid handle to a driver object.  Otherwise, it
    returns SYS_MODULE_OBJ_INVALID. 

  Remarks:
    This function must be called before any other OC function is called.
    This function should only be called once during system initialization.
    Build configuration options may be used to statically override options in the
    "init" structure and will take precedence over initialization data passed
    using this function.
*/
SYS_MODULE_OBJ DRV_OC_Initialize(const SYS_MODULE_INDEX index,const SYS_MODULE_INIT * const init);


// *****************************************************************************
/* Function:
DRV_HANDLE DRV_OC_Open(const SYS_MODULE_INDEX drvIndex, const DRV_IO_INTENT intent)

    Summary:
    Starts the Comparator instance for the specified driver index.
    <p><b>Implementation:</b> Static</p>	

  Description:
    This routine starts the Output Compare for the specified driver
    instance.

  Precondition:
    DRV_OC_Initialize has been called.

  Parameters:
    drvIndex    - Identifier for the object instance to be opened
    intent      - Zero or more of the values from the enumeration
                  DRV_IO_INTENT "ORed" together to indicate the intended use
                  of the driver

  Returns:
    If successful, the function returns a valid open-instance handle (a number
    identifying both the caller and the module instance).

    If an error occurs, the return value is DRV_HANDLE_INVALID.

  Remarks:
    The handle returned is valid until the DRV_OC_Close function is called.

    This function will NEVER block waiting for hardware.

    If the DRV_IO_INTENT_BLOCKING is requested and the driver was built
    appropriately to support blocking behavior, then other client-level
    operations may block waiting on hardware until they are complete.

*/
DRV_HANDLE DRV_OC_Open(const SYS_MODULE_INDEX drvIndex, const DRV_IO_INTENT intent);

// *****************************************************************************
/* Function:
     void DRV_OC_Close( DRV_HANDLE handle )

  Summary:
    Stops the Output Compare instance for the specified driver index.
	<p><b>Implementation:</b> Static</p>

  Description:
    This routine stops the Output Compare for the specified driver
    instance.

  Precondition:
    The DRV_OC_Initialize function must have been called for the specified
    Sample Driver instance.

    DRV_OC_Open must have been called to obtain a valid opened device handle.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open function

  Returns:
    None.

  Remarks:
    After calling this function, the handle passed in "handle" must not be used
    with any of the remaining driver routines.  A new handle must be obtained by
    calling DRV_OC_Open before the caller may use the driver again.

    Usually there is no need for the driver client to verify that the Close
    operation has completed.
*/
void DRV_OC_Close(DRV_HANDLE handle);

// *****************************************************************************
/* Function:
DRV_HANDLE DRV_OC_Start(const SYS_MODULE_INDEX drvIndex, const DRV_IO_INTENT intent)

    Summary:
    Starts the Comparator instance for the specified driver index.
    <p><b>Implementation:</b> Static</p>	

  Description:
    This routine starts the Output Compare for the specified driver
    instance.

  Precondition:
    DRV_OC_Initialize has been called.

  Parameters:
    drvIndex    - Identifier for the object instance to be opened
    intent      - Zero or more of the values from the enumeration
                  DRV_IO_INTENT "ORed" together to indicate the intended use
                  of the driver

  Returns:
    If successful, the function returns a valid open-instance handle (a number
    identifying both the caller and the module instance).

    If an error occurs, the return value is DRV_HANDLE_INVALID.

  Remarks:
    The handle returned is valid until the DRV_OC_Close function is called.

    This function will NEVER block waiting for hardware.

    If the DRV_IO_INTENT_BLOCKING is requested and the driver was built
    appropriately to support blocking behavior, then other client-level
    operations may block waiting on hardware until they are complete.

*/
DRV_HANDLE DRV_OC_Start(const SYS_MODULE_INDEX drvIndex, const DRV_IO_INTENT intent);

// *****************************************************************************
/* Function:
     void DRV_OC_Stop( DRV_HANDLE handle )

  Summary:
    Stops the Output Compare instance for the specified driver index.
	<p><b>Implementation:</b> Static</p>

  Description:
    This routine stops the Output Compare for the specified driver
    instance.

  Precondition:
    The DRV_OC_Initialize function must have been called for the specified
    Sample Driver instance.

    DRV_OC_Open must have been called to obtain a valid opened device handle.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open function

  Returns:
    None.

  Remarks:
    After calling this function, the handle passed in "handle" must not be used
    with any of the remaining driver routines.  A new handle must be obtained by
    calling DRV_OC_Open before the caller may use the driver again.

    Usually there is no need for the driver client to verify that the Stop
    operation has completed.
*/
void DRV_OC_Stop(DRV_HANDLE handle);

// *****************************************************************************
/* Function:
     bool DRV_OC_FaultHasOccurred( DRV_HANDLE handle )

  Summary:
    Checks if a Fault has occurred for the specified driver index.
    <p><b>Implementation:</b> Static</p>	

  Description:
    This routine checks whether or not a Fault has occurred for the specified 
	driver index. The initialization routine is specified by the MHC parameters.

  Precondition:
    DRV_OC_Initialize has been called.

  Parameters:
    None.

  Returns:
    Boolean
	- 1 - A Fault has occurred
	- 0 - A Fault has not occurred

  Remarks:
    None. 
*/
bool DRV_OC_FaultHasOccurred(DRV_HANDLE handle);

// *****************************************************************************
/* Function:
    void DRV_OC_CompareValuesSingleSet(DRV_HANDLE handle, uint32_t compareValue)

  Summary:
    Sets the compare value for Single Compare match modes.
    <p><b>Implementation:</b> Static</p>

  Description:
    This routine sets the compare value for the Single Compare match modes.
    Single compare match modes of OC are:
        - OC_SET_HIGH_SINGLE_PULSE_MODE
        - OC_SET_LOW_SINGLE_PULSE_MODE
        - OC_TOGGLE_CONTINUOUS_PULSE_MODE
        
    Use DRV_TMR_AlarmPeriodSet API to update the period of time base.

  Precondition:
    The DRV_OC_Initialize function must have been called for the specified
    driver instance.

    DRV_OC_Open must have been called to obtain a valid opened device handle.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open function
    compareValue - Preferred compare value needed by the application

  Returns:
    None.

  Remarks:
    This API is supported only when selected instance of the OC driver is 
    configured for one of the Single Compare match modes.
*/
void DRV_OC_CompareValuesSingleSet(DRV_HANDLE handle, uint32_t compareValue);

// *****************************************************************************
/* Function:
    void DRV_OC_CompareValuesDualSet
    (
        DRV_HANDLE handle, 
        uint32_t priVal, 
        uint32_t secVal
    )

  Summary:
    Sets the primary and secodary compare values for Dual Compare match modes.
    <p><b>Implementation:</b> Static</p>

  Description:
    This routine sets the primary and secodary compare values for Dual Compare 
    match modes. Dual compare match modes of OC are:
        - OC_DUAL_COMPARE_SINGLE_PULSE_MODE
        - OC_DUAL_COMPARE_CONTINUOUS_PULSE_MODE
        
    Use DRV_TMR_AlarmPeriodSet API to update the period of time base.

  Precondition:
    The DRV_OC_Initialize function must have been called for the specified
    driver instance.

    DRV_OC_Open must have been called to obtain a valid opened device handle.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open function
    priValue     - Preferred primary compare value needed by the application
    secValue     - Preferred secondary compare value needed by the application

  Returns:
    None.

  Remarks:
    This API is supported only when selected instance of the OC driver is 
    configured for one of the Dual Compare match modes.
*/
void DRV_OC_CompareValuesDualSet
(
    DRV_HANDLE handle, 
    uint32_t priVal, 
    uint32_t secVal
);

// *****************************************************************************
/* Function:
     void DRV_OC_PulseWidthSet(DRV_HANDLE handle, uint32_t pulseWidth)

  Summary:
    Sets the pulse width for PWM modes.
    <p><b>Implementation:</b> Static</p>

  Description:
    This routine sets the pulse width for PWM modes, setting pulse width updates 
    the PWM duty cycle accordingly. Available PWM modes of OC are:
        - OC_COMPARE_PWM_MODE_WITHOUT_FAULT_PROTECTION
        - OC_COMPARE_PWM_MODE_WITH_FAULT_PROTECTION
        
    Use DRV_TMR_AlarmPeriodSet API to update the period of time base.

  Precondition:
    The DRV_OC_Initialize function must have been called for the specified
    driver instance.

    DRV_OC_Open must have been called to obtain a valid opened device handle.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open function
    pulseWidth   - Preferred pulse width demanded by the application

  Returns:
    None.

  Remarks:
    This API is supported only when selected instance of the OC driver is 
    configured for one of the PWM modes.
*/
void DRV_OC_PulseWidthSet(DRV_HANDLE handle, uint32_t pulseWidth);

	
#ifdef DRV_OC_DRIVER_MODE_STATIC
#include "framework/driver/oc/drv_oc_static.h"
#endif
	
#endif // #ifndef _DRV_OC_H
/*******************************************************************************
 End of File
*/
