/**
 * @(#)Fitipower_FC0012.h
 *
 * ==========================================================
 * Version: 2.0
 * Date:    2008.09.17
 * ==========================================================
 *
 * ==========================================================
 * History:
 *
 * Date         Author      Description
 * ----------------------------------------------------------
 *
 * 2008.09.17   Benny Chen  added tuner version
 * ==========================================================
 *
 * Copyright 2008 Afatech, Inc. All rights reserved.
 *
 */


#ifndef __Fitipower_FC0012_H__
#define __Fitipower_FC0012_H__


#define FC0012_VER_MAJOR    2
#define FC0012_VER_MINOR    0

extern TunerDescription tuner_FC0012;


/**
 *
 */
Dword FC0012_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword FC0012_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword FC0012_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
    IN  Word			bandwidth,
    IN  Dword			frequency
);
#endif