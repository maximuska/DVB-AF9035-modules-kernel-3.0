/**
 * @(#)Philips_TDA18271_C2_Askey_INT.cpp
 *
 * Copyright 2007 Afatech, Inc. All rights reserved.
 */




//#include <stdio.h> //for Linux
#include "type.h"
#include "error.h"
#include "user.h"
#include "register.h"
#include "standard.h"

#include "TDA18271local_C2_Askey.h"
#include "TDA18271_C2_Askey.h"
#include "Philips_TDA18271_C2_Askey_Script.h"


extern tmTDA18271Object_t_C2_Askey gTDA18271Instance_C2_Askey[];

Dword Standard_computeFcw (
    IN  Demodulator*    demodulator,
    IN  Long            adcFrequency,       /** ADC frequency (Hz)    */
    IN  Long            ifFrequency,        /** IF frequency (Hz)     */
    IN  Bool            inversion,          /** RF spectrum inversion */
    OUT Dword*          fcw
);

Dword TDA18271_C2_Askey_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
  	Dword              error = Error_NO_ERROR;
    tmbslTuParam_t_C2_Askey  param;
        
	gTDA18271Instance_C2_Askey[0].AFAInfo_C2_Askey.demodulator = demodulator;
	gTDA18271Instance_C2_Askey[0].AFAInfo_C2_Askey.chip = chip;
 
    param.systemFunc.SY_Read_C2_Askey  = SY_Read_C2_Askey;
    param.systemFunc.SY_Write_C2_Askey = SY_Write_C2_Askey;
    param.uHwAddress = 0xC0ul;
        
    error = tmbslTDA18271Init_C2_Askey(0, param);
    if (error) goto exit;

    error = TDA18271Init_C2_Askey(0);
    if (error) goto exit;

exit:
    return (error);
}

Dword TDA18271_C2_Askey_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
	return (Error_NO_ERROR);
}

Dword TDA18271_C2_Askey_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
	IN  Word			bandwidth,
	IN  Dword			frequency
) {

	Dword           error = Error_NO_ERROR;
    Byte			fc = 1;
    Long            IfFreq;
	Dword           fcw;
    Byte            buffer[3];
	Ganymede* ganymede;		
	ganymede = (Ganymede*) demodulator;
  
    switch(bandwidth)
	{
	case 6000:
        IfFreq = 3300000;
        fc = tmDigital_TV_ATSC_6MHz_C2_Askey;
		break;
	case 7000:
        IfFreq = 3500000;
        fc = tmDigital_TV_DVBT_7MHz_C2_Askey;
		break;
	case 8000:
        IfFreq = 4000000;
        fc = tmDigital_TV_DVBT_8MHz_C2_Askey;
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
   
    error = tmbslTDA18271SetConfig_C2_Askey(0, STANDARDMODE_C2_Askey, fc);
    if (error) goto exit;
	
	error = tmbslTDA18271SetRf_C2_Askey(0, frequency * 1000);

exit:
    return (error);    
}


TunerDescription tuner_TDA18271_C2_Askey = {
    TDA18271_C2_Askey_open,
    TDA18271_C2_Askey_close,
    TDA18271_C2_Askey_set,
    TDA18271_C2_Askey_scripts,
    TDA18271_C2_Askey_scriptSets,
    TDA18271_C2_Askey_ADDRESS,               /** tuner i2c address */
    1,                              /** length of tuner register address */
    0,                              /** tuner if */
    (Bool)True,                     /** spectrum inverse */
    0x2F,                            /** tuner id */
};
