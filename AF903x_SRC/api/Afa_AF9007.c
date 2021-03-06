/**
 * @(#)Afa_AF9007.cpp
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


//#include <stdio.h> // for Linux
#include "type.h"
#include "error.h"
#include "user.h"
#include "register.h"
#include "standard.h"
#include "Afa_AF9007_Script.h"


Dword AF9007_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
	return (Error_NO_ERROR);
}


Dword AF9007_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
	return (Error_NO_ERROR);
}


Dword AF9007_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
	IN  Word			bandwidth,
	IN  Dword			frequency
) {
	return (Error_NO_ERROR);
}


TunerDescription tuner_AF9007 = {
    AF9007_open,
    AF9007_close,
    AF9007_set,
    AF9007_scripts,
    AF9007_scriptSets,
    0,                              /** tuner i2c address */
    0,                              /** length of tuner register address */
    36167000,                       /** tuner if */
    True,                           /** spectrum inverse */
    0xFF,                           /** tuner id */
};
