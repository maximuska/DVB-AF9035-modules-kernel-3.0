/**
 * @(#)Infineon_TUA6039.h
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


#ifndef __Infineon_TUA6039_H__
#define __Infineon_TUA6039_H__


#define TUA6039_VER_MAJOR    2
#define TUA6039_VER_MINOR    0

extern TunerDescription tuner_TUA6039;


/**
 *
 */
Dword TUA6039_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword TUA6039_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword TUA6039_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
    IN  Word			bandwidth,
    IN  Dword			frequency
);
#endif