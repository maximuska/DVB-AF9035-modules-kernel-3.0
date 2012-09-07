/**
 * @(#)Freescale_MC44CD02.cpp
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
#include "Freescale_MC44CD02_Script.h"


Bool powerDownMode = False;
Bool bandLockActivated = False;
Bool analogTestMode = False;
Byte referenceClock = 36;
Dword programmableDivider;
Short dischargingCurrent = 266;
Short chargingCurrent = 836;
Short offsetAdjustment = -109;
Short gainAdjustment = 221;
Bool singleEndBuffer = True;
Bool outputDriverDisabled = False;
Byte sineWaveAmplitude = 1;
Bool squareWaveShape = False;
Bool clockHasPriority = False;
Byte kneeVoltageShift = 0;
Bool antiAliasingDisabled = False;
Bool openDrainOutput = False;
Bool stateOfOutputPort = False;
Byte postAmplifierGain = 14;


Dword MC44CD02_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
    Dword error = Error_NO_ERROR;
	Byte values[7];

	values[0] = 0;
	if (powerDownMode == True)
		values[0] |= 0x04;
	if (bandLockActivated == True)
		values[0] |= 0x02;
	if (analogTestMode == True)
		values[0] |= 0x01;

	values[1] = 0;
	if (referenceClock == 26)
		values[1] |= 0x20;
	programmableDivider = (666 * 6) / 1000;
	values[1] |= (Byte) ((programmableDivider & 0x1F00) >> 8);

	values[2] = (Byte) (programmableDivider & 0x00FF);

	values[3] = 0;
	switch (chargingCurrent) {
		case 266 :
			values[3] |= 0x00;
			break;
		case 106 :
			values[3] |= 0x08;
			break;
		case 159 :
			values[3] |= 0x10;
			break;
		case 213 :
			values[3] |= 0x18;
			break;
		case 319 :
			values[3] |= 0x20;
			break;
		case 379 :
			values[3] |= 0x21;
			break;
		case 425 :
			values[3] |= 0x30;
			break;
		default :
			values[3] |= 0x31;
	}
	switch (chargingCurrent) {
		case 836 :
			values[3] |= 0x00;
			break;
		case 790 :
			values[3] |= 0x01;
			break;
		case 744 :
			values[3] |= 0x02;
			break;
		case 698 :
			values[3] |= 0x03;
			break;
		case 880 :
			values[3] |= 0x04;
			break;
		case 924 :
			values[3] |= 0x05;
			break;
		case 967 :
			values[3] |= 0x06;
			break;
		case 1011 :
			values[3] |= 0x07;
	}

	values[4] = 0;
	switch (offsetAdjustment) {
		case -109 :
			values[4] |= 0x00;
			break;
		case -73 :
			values[4] |= 0x08;
			break;
		case -36 :
			values[4] |= 0x10;
			break;
		case 0 :
			values[4] |= 0x18;
			break;
		case 39 :
			values[4] |= 0x20;
			break;
		case 77 :
			values[4] |= 0x21;
			break;
		case 116 :
			values[4] |= 0x30;
			break;
		case 154 :
			values[4] |= 0x31;
	}
	switch (gainAdjustment) {
		case 221 :
			values[4] |= 0x00;
			break;
		case 227 :
			values[4] |= 0x01;
			break;
		case 233 :
			values[4] |= 0x02;
			break;
		case 240 :
			values[4] |= 0x03;
			break;
		case 247 :
			values[4] |= 0x04;
			break;
		case 255 :
			values[4] |= 0x05;
			break;
		case 264 :
			values[4] |= 0x06;
			break;
		case 274 :
			values[4] |= 0x07;
	}

	values[5] = 0;
	if (singleEndBuffer == True)
		values[5] |= 0x80;
	if (outputDriverDisabled == True)
		values[5] |= 0x40;
	if (sineWaveAmplitude == 1)
		values[5] |= 0x20;
	if (squareWaveShape == True)
		values[5] |= 0x08;
	if (clockHasPriority == True)
		values[5] |= 0x04;
	if (kneeVoltageShift == 0)
		values[5] |= 0x00;

	values[6] = 0;
	if (antiAliasingDisabled == True)
		values[6] |= 0x40;
	if (openDrainOutput == True)
		values[6] |= 0x20;
	if (stateOfOutputPort == True)
		values[6] |= 0x10;
	switch (postAmplifierGain) {
		case 14 :
			values[6] |= 0x00;
			break;
		case 10 :
			values[6] |= 0x04;
			break;
		case 12 :
			values[6] |= 0x08;
			break;
	}
	switch (8) {
		case 8 :
			values[6] |= 0x00;
			break;
		case 7 :
			values[6] |= 0x02;
			break;
		case 6 :
			values[6] |= 0x03;
			break;
	}

	error = Standard_writeTunerRegisters (demodulator, chip, 0x00, 7, values); 

	return (error);
}


Dword MC44CD02_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
    Dword error = Error_NO_ERROR;
	return (error);
}


Dword MC44CD02_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
    IN  Word			bandwidth,
    IN  Dword			frequency
) {
    Dword error = Error_NO_ERROR;
	Byte values[2];

	values[0] = 0;
	if (referenceClock == 26)
		values[0] |= 0x20;
	programmableDivider = (frequency * 6) / 1000;
	values[0] |= (Byte) ((programmableDivider & 0x1F00) >> 8);

	values[1] = (Byte) (programmableDivider & 0x00FF);

	error = Standard_writeTunerRegisters (demodulator, chip, 0x01, 2, values); 
	if (error) goto exit;

	values[0] = 0;
	if (antiAliasingDisabled == True)
		values[0] |= 0x40;
	if (openDrainOutput == True)
		values[0] |= 0x20;
	if (stateOfOutputPort == True)
		values[0] |= 0x10;
	switch (postAmplifierGain) {
		case 14 :
			values[0] |= 0x00;
			break;
		case 10 :
			values[0] |= 0x04;
			break;
		case 12 :
			values[0] |= 0x08;
			break;
	}
	switch (bandwidth) {
		case 8000 :
			values[0] |= 0x00;
			break;
		case 7000 :
			values[0] |= 0x02;
			break;
		case 6000 :
			values[0] |= 0x03;
			break;
	}

	error = Standard_writeTunerRegisters (demodulator, chip, 0x06, 1, values); 

exit :
	return (error);
}


TunerDescription tuner_MC44CD02 = {
    MC44CD02_open,
    MC44CD02_close,
    MC44CD02_set,
    MC44CD02_scripts,
    MC44CD02_scriptSets,
    MC44CD02_ADDRESS,               /** tuner i2c address */
    1,                              /** length of tuner register address */
    0,                              /** tuner if */
    True,                           /** spectrum inverse */
    0x20,                           /** tuner id */
};
