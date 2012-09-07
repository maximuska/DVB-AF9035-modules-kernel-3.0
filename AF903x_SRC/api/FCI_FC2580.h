/**
 * @(#)FCI_FC2580.h
 *
 * ==========================================================
 * Version: 2.3
 * Date:    2009.01.06
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
 * Copyright 2008 Afatech, Inc. All rights reserved.
 *
 */


#ifndef __FCI_FC2580_H__
#define __FCI_FC2580_H__


#define FC2580_VER_MAJOR    2
#define FC2580_VER_MINOR    4

extern TunerDescription tuner_FC2580;


/**
 *
 */
Dword FC2580_open (
	IN  Demodulator*	demodulator,
	IN  StreamType		streamType,
	IN  Byte			chip
);


/**
 *
 */
Dword FC2580_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);



/**
 *
 */
Dword FC2580_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
    IN  Word			bandwidth,
    IN  Dword			frequency
);
#endif