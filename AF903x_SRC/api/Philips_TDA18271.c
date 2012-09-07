/**
 * @(#)Philips_TDA18271.cpp
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
 * Copyright 2007 Afatech, Inc. All rights reserved.
 *
 */


//#include <stdio.h> //for Linux
#include "type.h"
#include "error.h"
#include "user.h"
#include "register.h"
#include "standard.h"
#include "TDA18271Local.h"
#include "TDA18271.h"
#include "Philips_TDA18271_Script.h"


extern tmTDA18271Object_t gTDA18271Instance[];

Dword Standard_computeFcw (
    IN  Demodulator*    demodulator,
    IN  Long            adcFrequency,       /** ADC frequency (Hz)    */
    IN  Long            ifFrequency,        /** IF frequency (Hz)     */
    IN  Bool            inversion,          /** RF spectrum inversion */
    OUT Dword*          fcw
);


Dword TDA18271_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
    return (Error_NO_ERROR);
}


Dword TDA18271_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
	return (Error_NO_ERROR);
}


Dword TDA18271_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
	IN  Word			bandwidth,
	IN  Dword			frequency
) {

	Dword           error = Error_NO_ERROR;
    tmbslTuParam_t  param;
    Byte			fc = 1;
    Long            IfFreq;
	Dword           fcw;
    Byte            buffer[3];
	Ganymede* ganymede;		
	ganymede = (Ganymede*) demodulator;

	gTDA18271Instance[0].AFAInfo.demodulator = demodulator;
	gTDA18271Instance[0].AFAInfo.chip = chip;
 
    param.systemFunc.SY_Read  = SY_Read;
    param.systemFunc.SY_Write = SY_Write;
    param.uHwAddress = 0xC0ul;

    
    switch(bandwidth)
	{
	case 6000:
        IfFreq = 3300000;
        fc = tmDigital_TV_ATSC_6MHz;
		break;
	case 7000:
        IfFreq = 3800000;
        fc = tmDigital_TV_DVBT_7MHz;
		break;
	case 8000:
        IfFreq = 4300000;
        fc = tmDigital_TV_DVBT_8MHz;
		break;
	default:
        error = Error_INVALID_BW;
        goto exit;
	}

    error = Standard_computeFcw (demodulator, (Long) ganymede->adcFrequency, IfFreq, ganymede->tunerDescription->inversion, &fcw);
    if (error) goto exit;
    ganymede->fcw = fcw;
   
    buffer[0] = (Byte) (fcw & 0x000000FF);
    buffer[1] = (Byte) ((fcw & 0x0000FF00) >> 8);
    buffer[2] = (Byte) ((fcw & 0x007F0000) >> 16);
    error = Standard_writeRegisters (demodulator, chip, Processor_OFDM, bfs_fcw_7_0, bfs_fcw_22_16 - bfs_fcw_7_0 + 1, buffer);    
    if (error) goto exit;

    
    error = tmbslTDA18271Init(0, param);
    if (error) goto exit;

    error = tmbslTDA18271SetConfig(0, STANDARDMODE, fc);
    if (error) goto exit;
	
	error = tmbslTDA18271SetRf(0, frequency * 1000);

exit:
    return (error);    
}


TunerDescription tuner_TDA18271 = {
    TDA18271_open,
    TDA18271_close,
    TDA18271_set,
    TDA18271_scripts,
    TDA18271_scriptSets,
    TDA18271_ADDRESS,               /** tuner i2c address */
    1,                              /** length of tuner register address */
    0,                              /** tuner if */
    (Bool)True,                     /** spectrum inverse */
    0x1B,                           /** tuner id */
};
