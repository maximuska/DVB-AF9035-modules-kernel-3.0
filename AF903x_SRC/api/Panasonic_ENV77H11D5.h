/**
 * @(#)Panasonic_ENV77H11D5.h
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


#ifndef __Panasonic_ENV77H11D5_H__
#define __Panasonic_ENV77H11D5_H__


#define ENV77H11D5_VER_MAJOR        2
#define ENV77H11D5_VER_MINOR        0

extern TunerDescription tuner_ENV77H11D5;


/**
 *
 */
Dword ENV77H11D5_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword ENV77H11D5_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword ENV77H11D5_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
    IN  Word			bandwidth,
    IN  Dword			frequency
);
#endif