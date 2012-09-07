/**
 * @(#)Philips_TD1316AFIHP.h
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


#ifndef __Philips_TD1316AFIHP_H__
#define __Philips_TD1316AFIHP_H__


#define TD1316AFIHP_VER_MAJOR        2
#define TD1316AFIHP_VER_MINOR        0

extern TunerDescription tuner_TD1316AFIHP;


/**
 *
 */
Dword TD1316AFIHP_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword TD1316AFIHP_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword TD1316AFIHP_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
    IN  Word			bandwidth,
    IN  Dword			frequency
);
#endif