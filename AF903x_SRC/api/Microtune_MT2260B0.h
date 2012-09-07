/**
 * @(#)Microtune_MT2260B0.h
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


#ifndef __Microtune_MT2260B0_H__
#define __Microtune_MT2260B0_H__


#define MT2260B0_VER_MAJOR        2
#define MT2260B0_VER_MINOR        0

extern TunerDescription tuner_MT2260B0;


extern int RF_IF_MT2060_X100[];


ValueSet Microtune_MT2260B0_EXT_script[];


/**
 *
 */
Dword MT2260B0_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword MT2260B0_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword MT2260B0_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
    IN  Word			bandwidth,
    IN  Dword			frequency
);
#endif