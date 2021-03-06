/**
 * @(#)Philips_TDA18271_C2.h
 *
 * Copyright 2007 Afatech, Inc. All rights reserved.
 */
#ifndef __Philips_TDA18271_C2_H__
#define __Philips_TDA18271_C2_H__

#define TDA18271_C2_VER_MAJOR        1
#define TDA18271_C2_VER_MINOR        0

extern TunerDescription tuner_TDA18271_C2;


/**
 *
 */
Dword TDA18271_C2_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword TDA18271_C2_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword TDA18271_C2_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
    IN  Word			bandwidth,
    IN  Dword			frequency
);
#endif