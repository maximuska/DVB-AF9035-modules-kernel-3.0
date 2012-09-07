/**
 * @(#)Panasonic_ENV77H11D5.cpp
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
#include "Panasonic_ENV77H11D5_Script.h"


Dword ENV77H11D5_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
    return (Error_NO_ERROR);
}


Dword ENV77H11D5_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
    return (Error_NO_ERROR);
}


Dword ENV77H11D5_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
    IN  Word			bandwidth,
	IN  Dword			frequency
) {
    Dword error = Error_NO_ERROR;
    Word N;
	Byte N1;
	Byte N2;
	Byte ucC1 = 0x8E;
	Byte ucC2;
	Byte buffer[10];

    /** Round ((wFreq * 1000 + 36125) * 6 / 1000) so that "500" exists */
	N   = (Word)(((frequency + 36167) * 6 + 500) / 1000);
    N1 = (Byte)(N / 256);
    N2 = (Byte)(N % 256);

    if ((174000 <= frequency) && (frequency <= 230000)) ucC2 = 0x42;
    else if ((470000 < frequency) && (frequency <= 486000)) ucC2 = 0x64;
    else if ((486000 < frequency) && (frequency <= 526000)) ucC2 = 0x84;
    else if ((526000 < frequency) && (frequency <= 678000)) ucC2 = 0xA4;
    else if ((678000 < frequency) && (frequency <= 862000)) ucC2 = 0xC4;
    else {
        error = Error_FREQ_OUT_OF_RANGE;
        goto exit;
    }

    ucC1 = 0xC2;

    buffer[0] = N1;
    buffer[1] = N2;
    buffer[2] = ucC1;
    buffer[3] = ucC2;

    /** Write freq parameters to tuner */
    error = Standard_writeTunerRegisters (demodulator, chip, 0x0000, 4, buffer);
    if (error) goto exit;

    ucC1 = 0x86;

    buffer[0] = N1;
    buffer[1] = N2;
    buffer[2] = ucC1;
    buffer[3] = ucC2;

    /** Write freq parameters to tuner */
    error = Standard_writeTunerRegisters (demodulator, chip, 0x0000, 4, buffer);
    if (error) goto exit;

exit:
	return(error);
}


TunerDescription tuner_ENV77H11D5 = {
    ENV77H11D5_open,
    ENV77H11D5_close,
    ENV77H11D5_set,
    ENV77H11D5_scripts,
	ENV77H11D5_scriptSets,
    ENV77H11D5_ADDRESS,             /** tuner i2c address */
    0,                              /** length of tuner register address */
    36167000,                       /** tuner if */
    True,                           /** spectrum inverse */
    0x01,                           /** tuner id */
};
