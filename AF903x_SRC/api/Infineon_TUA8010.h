/**
 * @(#)Infineon_TUA8010.h
 *
 * ==========================================================
 * Version: 2.2
 * Date:    2008.10.22
 * ==========================================================
 *
 * ==========================================================
 * History:
 *
 * Date         Author      Description
 * ----------------------------------------------------------
 *
 * 2008.08.19   Tom Lin     added tuner version
 * ==========================================================
 *
 * Copyright 2008 Afatech, Inc. All rights reserved.
 *
 */


#ifndef __Infineon_TUA8010_H__
#define __Infineon_TUA8010_H__


#define TUA8010_VER_MAJOR    2
#define TUA8010_VER_MINOR    2

extern TunerDescription tuner_TUA8010;


/**
 *
 */
Dword TUA8010_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword TUA8010_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword TUA8010_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
    IN  Word			bandwidth,
    IN  Dword			frequency
);
#endif