/* Created by plibgen $Revision: 1.31 $ */

#ifndef _ADCP_P32MZ2048ECM100_H
#define _ADCP_P32MZ2048ECM100_H

/* Section 1 - Enumerate instances, define constants, VREGs */

#include <xc.h>
#include <stdbool.h>

#include "peripheral/peripheral_common_32bit.h"

/* Default definition used for all API dispatch functions */
#ifndef PLIB_INLINE_API
    #define PLIB_INLINE_API extern inline
#endif

/* Default definition used for all other functions */
#ifndef PLIB_INLINE
    #define PLIB_INLINE extern inline
#endif

typedef enum {

    ADCP_ID_1 = _ADC12_BASE_ADDRESS,
    ADCP_NUMBER_OF_MODULES = 1

} ADCP_MODULE_ID;

typedef enum {

    ADCP_VREF_AVDD_AVSS = 0,
    ADCP_VREF_VREFP_AVSS = 1,
    ADCP_VREF_AVDD_VREFN = 2,
    ADCP_VREF_VREFP_VREFN = 3

} ADCP_VREF_SOURCE;

typedef enum {

    ADCP_CLK_SRC_NONE = 0,
    ADCP_CLK_SRC_SYSCLK = 1,
    ADCP_CLK_SRC_RFCLK3 = 2,
    ADCP_CLK_SRC_FRC = 3

} ADCP_CLOCK_SOURCE;

typedef enum {

    ADCP_CLASS12_AN0 = 0,
    ADCP_CLASS12_AN1 = 1,
    ADCP_CLASS12_AN2 = 2,
    ADCP_CLASS12_AN3 = 3,
    ADCP_CLASS12_AN4 = 4,
    ADCP_CLASS12_AN5 = 5,
    ADCP_CLASS12_AN6 = 6,
    ADCP_CLASS12_AN7 = 7,
    ADCP_CLASS12_AN8 = 8,
    ADCP_CLASS12_AN9 = 9,
    ADCP_CLASS12_AN10 = 10,
    ADCP_CLASS12_AN11 = 11

} ADCP_CLASS12_INPUT_ID;

typedef enum {

    ADCP_SH0 = 0,
    ADCP_SH1 = 1,
    ADCP_SH2 = 2,
    ADCP_SH3 = 3,
    ADCP_SH4 = 4,
    ADCP_SH5 = 5,
    ADCP_NUMBER_OF_SH = 6

} ADCP_SH_ID;

typedef enum {

    ADCP_DSH0 = 0,
    ADCP_DSH1 = 1,
    ADCP_DSH2 = 2,
    ADCP_DSH3 = 3,
    ADCP_DSH4 = 4,
    ADCP_NUMBER_OF_DSH = 5

} ADCP_DSH_ID;

typedef enum {

    ADCP_SH_MODE_SINGLE_ENDED_UNIPOLAR = 0,
    ADCP_SH_MODE_SINGLE_ENDED_TWOS_COMP = 1,
    ADCP_SH_MODE_DIFFERENTIAL_UNIPOLAR = 2,
    ADCP_SH_MODE_DIFFERENTIAL_TWOS_COMP = 3

} ADCP_SH_MODE;

typedef enum {

    ADCP_SCAN_TRG_SRC_NONE = 0,
    ADCP_SCAN_TRG_SRC_SOFTWARE = 1,
    ADCP_SCAN_TRG_SRC_INT0 = 4,
    ADCP_SCAN_TRG_SRC_TMR1_MATCH = 5,
    ADCP_SCAN_TRG_SRC_TMR3_MATCH = 6,
    ADCP_SCAN_TRG_SRC_TMR5_MATCH = 7,
    ADCP_SCAN_TRG_SRC_OCMP1 = 8,
    ADCP_SCAN_TRG_SRC_OCMP3 = 9,
    ADCP_SCAN_TRG_SRC_OCMP5 = 10,
    ADCP_SCAN_TRG_SRC_COMP1_COUT = 11,
    ADCP_SCAN_TRG_SRC_COMP2_COUT = 12

} ADCP_SCAN_TRG_SRC;

typedef enum {

    ADCP_TRG_SRC_NONE = 0,
    ADCP_TRG_SRC_SOFTWARE = 1,
    ADCP_TRG_SRC_SCAN_TRG = 3,
    ADCP_TRG_SRC_INT0 = 4,
    ADCP_TRG_SRC_TMR1_MATCH = 5,
    ADCP_TRG_SRC_TMR3_MATCH = 6,
    ADCP_TRG_SRC_TMR5_MATCH = 7,
    ADCP_TRG_SRC_OCMP1 = 8,
    ADCP_TRG_SRC_OCMP3 = 9,
    ADCP_TRG_SRC_OCMP5 = 10,
    ADCP_TRG_SRC_COMP1_COUT = 11,
    ADCP_TRG_SRC_COMP2_COUT = 12

} ADCP_TRG_SRC;

typedef enum {

    ADCP_AN0 = 0,
    ADCP_AN1 = 1,
    ADCP_AN2 = 2,
    ADCP_AN3 = 3,
    ADCP_AN4 = 4,
    ADCP_AN5 = 5,
    ADCP_AN6 = 6,
    ADCP_AN7 = 7,
    ADCP_AN8 = 8,
    ADCP_AN9 = 9,
    ADCP_AN10 = 10,
    ADCP_AN11 = 11,
    ADCP_AN12 = 12,
    ADCP_AN13 = 13,
    ADCP_AN14 = 14,
    ADCP_AN15 = 15,
    ADCP_AN16 = 16,
    ADCP_AN17 = 17,
    ADCP_AN18 = 18,
    ADCP_AN19 = 19,
    ADCP_AN20 = 20,
    ADCP_AN21 = 21,
    ADCP_AN22 = 22,
    ADCP_AN23 = 23,
    ADCP_AN24 = 24,
    ADCP_AN25 = 25,
    ADCP_AN26 = 26,
    ADCP_AN27 = 27,
    ADCP_AN28 = 28,
    ADCP_AN29 = 29,
    ADCP_AN30 = 30,
    ADCP_AN31 = 31,
    ADCP_AN32 = 32,
    ADCP_AN33 = 33,
    ADCP_AN34 = 34,
    ADCP_IVREF = 43,
    ADCP_ITEMP = 44

} ADCP_INPUT_ID;

typedef enum {

    ADCP_DCMP1 = 0,
    ADCP_DCMP2 = 1,
    ADCP_DCMP3 = 2,
    ADCP_DCMP4 = 3,
    ADCP_DCMP5 = 4,
    ADCP_DCMP6 = 5,
    ADCP_NUMBER_OF_DCMP = 6

} ADCP_DCMP_ID;

typedef enum {

    ADCP_ODFLTR1 = 0,
    ADCP_ODFLTR2 = 1,
    ADCP_ODFLTR3 = 2,
    ADCP_ODFLTR4 = 3,
    ADCP_ODFLTR5 = 4,
    ADCP_ODFLTR6 = 5,
    ADCP_NUMBER_OF_ODFLTR = 6

} ADCP_ODFLTR_ID;

typedef enum {

    ADCP_ODFLTR_4X = 0,
    ADCP_ODFLTR_16X = 1,
    ADCP_ODFLTR_64X = 2,
    ADCP_ODFLTR_256X = 3,
    ADCP_ODFLTR_2X = 4,
    ADCP_ODFLTR_8X = 5,
    ADCP_ODFLTR_32X = 6,
    ADCP_ODFLTR_128X = 7

} ADCP_ODFLTR_SAMPLE_RATIO;

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE PLIB_INLINE
#include "../templates/adcp_EnableControl_Default.h"
#include "../templates/adcp_Calibration_Default.h"
#include "../templates/adcp_Configuration_Default.h"
#include "../templates/adcp_LowPowerControl_Default.h"
#include "../templates/adcp_ReadyStatus_Default.h"
#include "../templates/adcp_InputSelect_Default.h"
#include "../templates/adcp_ModeSelect_Default.h"
#include "../templates/adcp_ChannelScan_Default.h"
#include "../templates/adcp_Triggering_Default.h"
#include "../templates/adcp_ConversionResults_Default.h"
#include "../templates/adcp_DigitalComparator_Default.h"
#include "../templates/adcp_OsampDigitalFilter_Default.h"

/* Section 3 - PLIB dispatch function definitions */

PLIB_INLINE_API void PLIB_ADCP_Enable(ADCP_MODULE_ID index)
{
     ADCP_Enable_Default(index);
}

PLIB_INLINE_API void PLIB_ADCP_Disable(ADCP_MODULE_ID index)
{
     ADCP_Disable_Default(index);
}

PLIB_INLINE_API bool PLIB_ADCP_ExistsEnableControl(ADCP_MODULE_ID index)
{
     return ADCP_ExistsEnableControl_Default(index);
}

PLIB_INLINE_API void PLIB_ADCP_CalibrationStart(ADCP_MODULE_ID index)
{
     ADCP_CalibrationStart_Default(index);
}

PLIB_INLINE_API bool PLIB_ADCP_ExistsCalibration(ADCP_MODULE_ID index)
{
     return ADCP_ExistsCalibration_Default(index);
}

PLIB_INLINE_API void PLIB_ADCP_Configure(ADCP_MODULE_ID index, ADCP_VREF_SOURCE voltageRefSelect, bool boostVref, bool fractionalOutputOn, bool stopInIdle, ADCP_CLOCK_SOURCE adcClockSource, int8_t adcClockDivider, int8_t oversampleDigFilterSamTime, int8_t earlyIntEnable, int8_t class2and3SampleTime)
{
     ADCP_Configure_Default(index, voltageRefSelect, boostVref, fractionalOutputOn, stopInIdle, adcClockSource, adcClockDivider, oversampleDigFilterSamTime, earlyIntEnable, class2and3SampleTime);
}

PLIB_INLINE_API bool PLIB_ADCP_ExistsConfiguration(ADCP_MODULE_ID index)
{
     return ADCP_ExistsConfiguration_Default(index);
}

PLIB_INLINE_API void PLIB_ADCP_LowPowerStateEnter(ADCP_MODULE_ID index)
{
     ADCP_LowPowerStateEnter_Default(index);
}

PLIB_INLINE_API void PLIB_ADCP_LowPowerStateExit(ADCP_MODULE_ID index)
{
     ADCP_LowPowerStateExit_Default(index);
}

PLIB_INLINE_API bool PLIB_ADCP_LowPowerStateGet(ADCP_MODULE_ID index)
{
     return ADCP_LowPowerStateGet_Default(index);
}

PLIB_INLINE_API bool PLIB_ADCP_ExistsLowPowerControl(ADCP_MODULE_ID index)
{
     return ADCP_ExistsLowPowerControl_Default(index);
}

PLIB_INLINE_API bool PLIB_ADCP_ModuleIsReady(ADCP_MODULE_ID index)
{
     return ADCP_ModuleIsReady_Default(index);
}

PLIB_INLINE_API bool PLIB_ADCP_ExistsReadyStatus(ADCP_MODULE_ID index)
{
     return ADCP_ExistsReadyStatus_Default(index);
}

PLIB_INLINE_API void PLIB_ADCP_AlternateInputSelect(ADCP_MODULE_ID index, ADCP_DSH_ID id)
{
     ADCP_AlternateInputSelect_Default(index, id);
}

PLIB_INLINE_API void PLIB_ADCP_DefaultInputSelect(ADCP_MODULE_ID index, ADCP_DSH_ID id)
{
     ADCP_DefaultInputSelect_Default(index, id);
}

PLIB_INLINE_API bool PLIB_ADCP_ExistsInputSelect(ADCP_MODULE_ID index)
{
     return ADCP_ExistsInputSelect_Default(index);
}

PLIB_INLINE_API void PLIB_ADCP_SHModeSelect(ADCP_MODULE_ID index, ADCP_DSH_ID id, ADCP_SH_MODE mode)
{
     ADCP_SHModeSelect_Default(index, id, mode);
}

PLIB_INLINE_API bool PLIB_ADCP_ExistsModeSelect(ADCP_MODULE_ID index)
{
     return ADCP_ExistsModeSelect_Default(index);
}

PLIB_INLINE_API void PLIB_ADCP_ChannelScanConfigure(ADCP_MODULE_ID index, uint32_t lowEnable, uint32_t highEnable, ADCP_SCAN_TRG_SRC triggerSource)
{
     ADCP_ChannelScanConfigure_Default(index, lowEnable, highEnable, triggerSource);
}

PLIB_INLINE_API bool PLIB_ADCP_ExistsChannelScan(ADCP_MODULE_ID index)
{
     return ADCP_ExistsChannelScan_Default(index);
}

PLIB_INLINE_API void PLIB_ADCP_Class12TriggerConfigure(ADCP_MODULE_ID index, ADCP_CLASS12_INPUT_ID inputId, ADCP_TRG_SRC triggerSource)
{
     ADCP_Class12TriggerConfigure_Default(index, inputId, triggerSource);
}

PLIB_INLINE_API void PLIB_ADCP_GlobalSoftwareTrigger(ADCP_MODULE_ID index)
{
     ADCP_GlobalSoftwareTrigger_Default(index);
}

PLIB_INLINE_API void PLIB_ADCP_IndividualTrigger(ADCP_MODULE_ID index, ADCP_INPUT_ID inputId)
{
     ADCP_IndividualTrigger_Default(index, inputId);
}

PLIB_INLINE_API bool PLIB_ADCP_ExistsTriggering(ADCP_MODULE_ID index)
{
     return ADCP_ExistsTriggering_Default(index);
}

PLIB_INLINE_API AN_READY PLIB_ADCP_ResultReady(ADCP_MODULE_ID index)
{
     return ADCP_ResultReady_Default(index);
}

PLIB_INLINE_API int32_t PLIB_ADCP_ResultGet(ADCP_MODULE_ID index, ADCP_INPUT_ID inputId)
{
     return ADCP_ResultGet_Default(index, inputId);
}

PLIB_INLINE_API void PLIB_ADCP_ResultReadyGrpIntConfigure(ADCP_MODULE_ID index, uint32_t lowEnable, uint32_t highEnable)
{
     ADCP_ResultReadyGrpIntConfigure_Default(index, lowEnable, highEnable);
}

PLIB_INLINE_API bool PLIB_ADCP_ExistsConversionResults(ADCP_MODULE_ID index)
{
     return ADCP_ExistsConversionResults_Default(index);
}

PLIB_INLINE_API void PLIB_ADCP_DigCmpConfig(ADCP_MODULE_ID index, ADCP_DCMP_ID id, bool globalIntEnable, bool inBetweenOrEqual, bool greaterEqualHi, bool lessThanHi, bool greaterEqualLo, bool lessThanLo, uint32_t inputEnable, int32_t hiLimit, int32_t loLimit)
{
     ADCP_DigCmpConfig_Default(index, id, globalIntEnable, inBetweenOrEqual, greaterEqualHi, lessThanHi, greaterEqualLo, lessThanLo, inputEnable, hiLimit, loLimit);
}

PLIB_INLINE_API void PLIB_ADCP_DigCmpEnable(ADCP_MODULE_ID index, ADCP_DCMP_ID id)
{
     ADCP_DigCmpEnable_Default(index, id);
}

PLIB_INLINE_API void PLIB_ADCP_DigCmpDisable(ADCP_MODULE_ID index, ADCP_DCMP_ID id)
{
     ADCP_DigCmpDisable_Default(index, id);
}

PLIB_INLINE_API int16_t PLIB_ADCP_DigCmpAIdGet(ADCP_MODULE_ID index, ADCP_DCMP_ID id)
{
     return ADCP_DigCmpAIdGet_Default(index, id);
}

PLIB_INLINE_API bool PLIB_ADCP_ExistsDigCmp(ADCP_MODULE_ID index)
{
     return ADCP_ExistsDigCmp_Default(index);
}

PLIB_INLINE_API void PLIB_ADCP_OsampDigFilterConfig(ADCP_MODULE_ID index, ADCP_ODFLTR_ID id, ADCP_INPUT_ID inputId, ADCP_ODFLTR_SAMPLE_RATIO oversampleRatio, bool globalIntEnable)
{
     ADCP_OsampDigFilterConfig_Default(index, id, inputId, oversampleRatio, globalIntEnable);
}

PLIB_INLINE_API void PLIB_ADCP_OsampDigFilterEnable(ADCP_MODULE_ID index, ADCP_ODFLTR_ID id)
{
     ADCP_OsampDigFilterEnable_Default(index, id);
}

PLIB_INLINE_API void PLIB_ADCP_OsampDigFilterDisable(ADCP_MODULE_ID index, ADCP_ODFLTR_ID id)
{
     ADCP_OsampDigFilterDisable_Default(index, id);
}

PLIB_INLINE_API bool PLIB_ADCP_OsampDigFilterDataRdy(ADCP_MODULE_ID index, ADCP_ODFLTR_ID id)
{
     return ADCP_OsampDigFilterDataRdy_Default(index, id);
}

PLIB_INLINE_API int16_t PLIB_ADCP_OsampDigFilterDataGet(ADCP_MODULE_ID index, ADCP_ODFLTR_ID id)
{
     return ADCP_OsampDigFilterDataGet_Default(index, id);
}

PLIB_INLINE_API bool PLIB_ADCP_ExistsOsampDigFilter(ADCP_MODULE_ID index)
{
     return ADCP_ExistsOsampDigFilter_Default(index);
}

#endif
