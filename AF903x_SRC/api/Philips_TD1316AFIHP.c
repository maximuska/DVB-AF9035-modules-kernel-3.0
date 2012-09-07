/**
 * @(#)Philips_TD1316AFIHP.cpp
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

//#include <stdio.h> for Linux
#include "type.h"
#include "error.h"
#include "user.h"
#include "register.h"
#include "standard.h"
#include "Philips_TD1316AFIHP_Script.h"


Dword TD1316AFIHP_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
    return (Error_NO_ERROR);
}


Dword TD1316AFIHP_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
    return (Error_NO_ERROR);
}


Dword TD1316AFIHP_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
	IN  Word			bandwidth,
	IN  Dword			frequency
) {
    Dword error = Error_NO_ERROR;
	Byte buffer[10];
    Word N;
    Byte N1;
    Byte N2;
    Byte R10;
    Byte T210;
    Byte SP3;
    Byte SP210;
    Byte CP;
	Byte AGC;
    Byte AL210;
	Byte CB;
	Byte SB;
	Byte AB;

	N = (Word)(((frequency + 36167) * 6) / 1000);
	N1 = (Byte)(N >> 8) & 0x00FF;
	N2 = (Byte)(N & 0x00FF);

	if (bandwidth == 8000)
        SP3 = 0x01;
    else
        SP3 = 0x00;
    
    if(frequency > 790000)      {CP = 0x01; T210 = 0x07;}
	else if(frequency > 646000) {CP = 0x01; T210 = 0x06;}
	else if(frequency > 484000) {CP = 0x00; T210 = 0x07;}
	else if(frequency > 366000) {CP = 0x01; T210 = 0x06;}
	else if(frequency > 197000) {CP = 0x00; T210 = 0x07;}
	else if(frequency > 180000) {CP = 0x01; T210 = 0x06;}
	else if(frequency > 84000)  {CP = 0x00; T210 = 0x07;}
	    else
    {
        error = Error_FREQ_OUT_OF_RANGE;
        goto exit;
    }

	if(frequency > 473900)		{SP210 = 0x04;}
	else if(frequency > 173900){SP210 = 0x02;}
	else					{SP210 = 0x01;}

	R10 = 0x02;
    AGC = 0x00;   /** 0x01 */
	AL210 = 0x03; /** 0x04 */


	CB = 0x80 + (CP<<6) + (T210<<3) + (R10<<1);
	SB = (SP3<<3) + SP210;
	AB = (AGC<<7) + (AL210<<4);

	buffer[0]  = N1;
	buffer[1]  = N2;
	buffer[2]  = CB;
	buffer[3]  = SB;

	T210 = 0x03;
	CB = 0x80 + (CP<<6) + (T210<<3) + (R10<<1);

	buffer[4]  = CB;
	buffer[5]  = AB;

	error = Standard_writeTunerRegisters (demodulator, chip, 0x0000, 6, buffer);
    if (error) goto exit;

    User_delay (demodulator, 60);

exit :
	return (error);
}


TunerDescription tuner_TD1316AFIHP = {
    TD1316AFIHP_open,
    TD1316AFIHP_close,
    TD1316AFIHP_set,
    TD1316AFIHP_scripts,
    TD1316AFIHP_scriptSets,
    TD1316AFIHP_ADDRESS,            /** tuner i2c address */
    0,                              /** length of tuner register address */
    36167000,                       /** tuner if */
    True,                           /** spectrum inverse */
    0x04,                           /** tuner id */
};
