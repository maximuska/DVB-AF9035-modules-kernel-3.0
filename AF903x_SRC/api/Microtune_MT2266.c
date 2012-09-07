/**
 * @(#)Microtune_MT2266.cpp
 *
 * ==========================================================
 * Version: 2.1
 * Date:    2008.07.02
 * ==========================================================
 *
 * ==========================================================
 * History:
 *
 * Date         Author      Description
 * ----------------------------------------------------------
 *
 * 2008.07.02   Tom Lin     added tuner version
 * 2008.10.16   Tom Lin     support TA4029CTC
 * ==========================================================
 *
 * Copyright 2005 Afatech, Inc. All rights reserved.
 *
 */

//#include <stdio.h> // for Linux
#include "type.h"
#include "error.h"
#include "user.h"
#include "register.h"
#include "standard.h"
#include "mt2266.h"
#include "Microtune_MT2266_Script.h"
#include "Microtune_MT2266_TA4029CTC_Script.h"

/** when mount TA4029CTC, set the value to be 1 */
#define MT2266_TA4029CTC_SUPPORT 0


Handle_t Microtune_MT2266_tunerHandles[2];
UserData Microtune_MT2266_userDatas[2];


Dword MT2266_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
	Dword error = Error_NO_ERROR;
    UData_t status = MT_OK;

	Microtune_MT2266_userDatas[chip].chip = chip;
	Microtune_MT2266_userDatas[chip].demodulator = demodulator;
    status = MT2266_Open ((unsigned int)MT2266_ADDRESS, &Microtune_MT2266_tunerHandles[chip], &Microtune_MT2266_userDatas[chip]);
	if (MT_NO_ERROR (status))
		status |= MT2266_SetParam (Microtune_MT2266_tunerHandles[chip], MT2266_STEPSIZE, 62500);
	if (MT_NO_ERROR (status))
		status |= MT2266_SetParam (Microtune_MT2266_tunerHandles[chip], MT2266_RF_EXT, 1);
	if (MT_NO_ERROR (status))
		status |= MT2266_SetParam (Microtune_MT2266_tunerHandles[chip], MT2266_BB_EXT, 1);
    if (MT_IS_ERROR (status)) 
		error = Error_MT_TUNE_FAIL;

    return (error);
}


Dword MT2266_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
	Dword error = Error_NO_ERROR;
    UData_t status = MT_OK;

	status |= MT2266_Close (Microtune_MT2266_tunerHandles[chip]);
    if (MT_IS_ERROR (status)) 
		error = Error_MT_TUNE_FAIL;

    return (error);
}


Dword MT2266_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
    IN  Word			bandwidth,
    IN  Dword			frequency
) {
    Dword error = Error_NO_ERROR;
    UData_t status = MT_OK;
    UData_t freq;
    UData_t bw;

    freq = frequency * 1000UL;
    bw = (UData_t) bandwidth * 1000UL;

    /** Change frequency */
    status = MT2266_ChangeFreq (Microtune_MT2266_tunerHandles[chip], freq);
	if (MT_NO_ERROR (status))
		status |= MT2266_SetParam (Microtune_MT2266_tunerHandles[chip], MT2266_OUTPUT_BW, bw);
	if (MT_IS_ERROR (status))
		error = Error_MT_TUNE_FAIL;

	User_delay (demodulator, 100);

	return (error);
}


Dword Microtune_MT2266_EXT_getparam (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
	IN  MT2266_Param	param,
	IN  Dword*			value
) {
	Dword error = Error_NO_ERROR;
    UData_t status = MT_OK;

	status |= MT2266_GetParam (Microtune_MT2266_tunerHandles[chip], param, value);
    if (MT_IS_ERROR (status)) 
		error = Error_MT_TUNE_FAIL;

    return (error);
}


Dword Microtune_MT2266_EXT_setparam (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
	IN  MT2266_Param	param,
	IN  Dword			value
) {
	Dword error = Error_NO_ERROR;
    UData_t status = MT_OK;

	status |= MT2266_SetParam (Microtune_MT2266_tunerHandles[chip], param, value);
    if (MT_IS_ERROR (status)) 
		error = Error_MT_TUNE_FAIL;

    return (error);
}


TunerDescription tuner_MT2266 = {
    MT2266_open,
    MT2266_close,
    MT2266_set,
#if MT2266_TA4029CTC_SUPPORT
    MT2266_TA4029CTC_scripts,
    MT2266_TA4029CTC_scriptSets,
    MT2266_TA4029CTC_ADDRESS,                 /** tuner i2c address */
#else
    MT2266_scripts,
    MT2266_scriptSets,
    MT2266_ADDRESS,                 /** tuner i2c address */
#endif
    1,                              /** length of tuner register address */
    0,                              /** tuner if */
    True,                           /** spectrum inverse */
#if MT2266_TA4029CTC_SUPPORT
    0x2D,                           /** tuner id */
#else
    0x23,                           /** tuner id */
#endif
};

void MT2266_supportTA4029CTC (
    IN  Demodulator*    demodulator,
    IN  INT            support //for Linux
 ) {
     if (support) {
         tuner_MT2266.tunerScript = MT2266_TA4029CTC_scripts;
         tuner_MT2266.tunerScriptSets = MT2266_TA4029CTC_scriptSets;
         tuner_MT2266.tunerAddress = MT2266_TA4029CTC_ADDRESS;
         tuner_MT2266.tunerId = 0x2D;
     } else {
         tuner_MT2266.tunerScript = MT2266_scripts;
         tuner_MT2266.tunerScriptSets = MT2266_scriptSets;
         tuner_MT2266.tunerAddress = MT2266_ADDRESS;
         tuner_MT2266.tunerId = 0x23;
     }
}