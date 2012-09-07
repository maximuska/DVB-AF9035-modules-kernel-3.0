/**
 * @(#)Integrant_ITD3020_EXT.cpp
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
#include "ITD30x0.h"
#include "Integrant_ITD3020_Script.h"


Demodulator* Integrant_ITD3020_EXT_demodulator;
Byte Integrant_ITD3020_EXT_chip;


Dword ITD3020_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
	Dword error = Error_NO_ERROR;
	Ganymede* ganymede;

	ganymede = (Ganymede*) demodulator;
	Integrant_ITD3020_EXT_demodulator = demodulator;
	Integrant_ITD3020_EXT_chip = chip;

	AGCMODE = 1;	/** If this value = 0, Internal AGC mode.  */
					/** If this value = 1, External AGC mode   */

	TUNER_IF = ganymede->tunerDescription->ifFrequency / 1000;
	TUNER_RF = 88000;
	TUNER_REFCLK = REF_CLK16_384M; 

	ITD30x0MP_Tuner_Init();

	return (error);
}


Dword ITD3020_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
    return (Error_NO_ERROR);
}


Dword ITD3020_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
	IN  Word			bandwidth,
	IN  Dword			frequency
) {
	Dword error = Error_NO_ERROR;
	Ganymede* ganymede;

	ganymede = (Ganymede*) demodulator;
	Integrant_ITD3020_EXT_demodulator = demodulator;
	Integrant_ITD3020_EXT_chip = chip;

	AGCMODE = 1;	/** If this value = 0, Internal AGC mode.  */
					/** If this value = 1, External AGC mode   */

	TUNER_IF = ganymede->tunerDescription->ifFrequency / 1000;
	TUNER_RF = frequency;
	TUNER_REFCLK = REF_CLK16_384M; 

	SetFreq(TUNER_RF);

	return (error);
}


TunerDescription tuner_ITD3020 = {
    ITD3020_open,
    ITD3020_close,
    ITD3020_set,
    ITD3020_scripts,
    ITD3020_scriptSets,
    ITD3020_ADDRESS,                /** tuner i2c address */
    1,                              /** length of tuner register address */
    850000,                         /** tuner if */
    True,                           /** spectrum inverse */
    0x24,                           /** tuner id */
};
