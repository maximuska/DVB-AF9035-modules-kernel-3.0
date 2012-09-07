/**
 * @(#)Microtune_MT2266.h
 *
 * ==========================================================
 * Version: 2.1
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
 * 2008.10.16   Tom Lin     support TA4029CTC
 * ==========================================================
 *
 * Copyright 2005 Afatech, Inc. All rights reserved.
 *
 */


#ifndef __Microtune_MT2266_H__
#define __Microtune_MT2266_H__


#define MT2266_VER_MAJOR        2
#define MT2266_VER_MINOR        1

extern TunerDescription tuner_MT2266;


/**
 *
 */
Dword MT2266_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword MT2266_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword MT2266_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
    IN  Word			bandwidth,
    IN  Dword			frequency
);


/**
 *
 */

void MT2266_supportTA4029CTC (
    IN  Demodulator*	demodulator,
    IN  INT            support // for Linux
);
#endif