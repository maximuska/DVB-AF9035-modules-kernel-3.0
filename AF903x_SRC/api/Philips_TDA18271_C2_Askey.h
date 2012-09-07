/**
 * @(#)Philips_TDA18271_C2_Askey.h
 *
 * Copyright 2007 Afatech, Inc. All rights reserved.
 */
#ifndef __Philips_TDA18271_C2_Askey_H__
#define __Philips_TDA18271_C2_Askey_H__

#define TDA18271_C2_Askey_VER_MAJOR        2
#define TDA18271_C2_Askey_VER_MINOR        0

extern TunerDescription tuner_TDA18271_C2_Askey;


/**
 *
 */
Dword TDA18271_C2_Askey_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword TDA18271_C2_Askey_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword TDA18271_C2_Askey_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
    IN  Word			bandwidth,
    IN  Dword			frequency
);
#endif