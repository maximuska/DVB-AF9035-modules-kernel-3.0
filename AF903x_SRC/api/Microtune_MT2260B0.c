/**
 * @(#)Microtune_MT2260B0.cpp
 *
 * ==========================================================
 * Version: 2.0
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
 * ==========================================================
 *
 * Copyright 2005 Afatech, Inc. All rights reserved.
 *
 */


//#include <stdio.h> //for Linux
#include "type.h"
#include "error.h"
#include "user.h"
#include "register.h"
#include "standard.h"
#include "mt2260.h"
#include "Microtune_MT2260B0_Script.h"


#define Microtune_MT2260B0_EXT_ADDRESS 0xC0

Handle_t Microtune_MT2260B0_tunerHandles[2];
UserData Microtune_MT2260B0_userDatas[2];


Dword MT2260B0_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
	Dword error = Error_NO_ERROR;
    UData_t status = MT_OK;

	Microtune_MT2260B0_userDatas[chip].chip = chip;
	Microtune_MT2260B0_userDatas[chip].demodulator = demodulator;
    status = MT2260_Open ((unsigned int)Microtune_MT2260B0_EXT_ADDRESS, &Microtune_MT2260B0_tunerHandles[chip], &Microtune_MT2260B0_userDatas[chip]);
	if (MT_NO_ERROR (status))
		status |= MT2260_SetParam (Microtune_MT2260B0_tunerHandles[chip], MT2260_STEPSIZE, 62500);
	if (MT_NO_ERROR (status))
		status |= MT2260_SetParam (Microtune_MT2260B0_tunerHandles[chip], MT2260_RF_EXT, 1);
	if (MT_NO_ERROR (status))
		status |= MT2260_SetParam (Microtune_MT2260B0_tunerHandles[chip], MT2260_BB_EXT, 1);
    if (MT_IS_ERROR (status)) 
		error = Error_MT_TUNE_FAIL;

    return (error);
}


Dword MT2260B0_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
	Dword error = Error_NO_ERROR;
    UData_t status = MT_OK;

	status |= MT2260_Close (Microtune_MT2260B0_tunerHandles[chip]);
    if (MT_IS_ERROR (status)) 
		error = Error_MT_TUNE_FAIL;

    return (error);
}


Dword MT2260B0_set (
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
    status = MT2260_ChangeFreq (Microtune_MT2260B0_tunerHandles[chip], freq);
	if (MT_NO_ERROR (status))
		status |= MT2260_SetParam (Microtune_MT2260B0_tunerHandles[chip], MT2260_OUTPUT_BW, bw);
	if (MT_IS_ERROR (status))
		error = Error_MT_TUNE_FAIL;

	User_delay (demodulator, 100);

	return (error);
}


TunerDescription tuner_MT2260B0 = {
    MT2260B0_open,
    MT2260B0_close,
    MT2260B0_set,
    MT2260B0_scripts,
    MT2260B0_scriptSets,
    MT2260B0_ADDRESS,               /** tuner i2c address */
    1,                              /** length of tuner register address */
    0,                              /** tuner if */
    True,                           /** spectrum inverse */
    0x21,                           /** tuner id */
};
