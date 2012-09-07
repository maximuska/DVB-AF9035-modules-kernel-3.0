/**
 * @(#)Fitipower_FC0011.h
 *
 * ==========================================================
 * Version: 2.1
 * Date:    2009.03.27
 * ==========================================================
 *
 * ==========================================================
 * History:
 *
 * Date         Author      Description
 * ----------------------------------------------------------
 *
 * 2008.07.02   Tom Lin     added tuner version
 * 2009.03.27   Yinding     update tuner register settings
 * ==========================================================
 *
 * Copyright 2008 Afatech, Inc. All rights reserved.
 *
 */


#ifndef __Fitipower_FC0011_H__
#define __Fitipower_FC0011_H__


#define FC0011_VER_MAJOR    2
#define FC0011_VER_MINOR    1

extern TunerDescription tuner_FC0011;


/**
 *
 */
Dword FC0011_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword FC0011_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword FC0011_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
    IN  Word			bandwidth,
    IN  Dword			frequency
);
#endif