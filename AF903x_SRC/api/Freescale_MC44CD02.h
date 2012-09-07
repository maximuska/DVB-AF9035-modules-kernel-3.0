/**
 * @(#)Freescale_MC44CD02.h
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


#ifndef __Freescale_MC44CD02_H__
#define __Freescale_MC44CD02_H__


#define MC44CD02_VER_MAJOR    2
#define MC44CD02_VER_MINOR    0

extern TunerDescription tuner_MC44CD02;


/**
 *
 */
Dword MC44CD02_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword MC44CD02_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);



/**
 *
 */
Dword MC44CD02_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
    IN  Word			bandwidth,
    IN  Dword			frequency
);
#endif