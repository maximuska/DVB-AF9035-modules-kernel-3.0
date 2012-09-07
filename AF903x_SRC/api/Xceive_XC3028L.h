/**
 * @(#)Xceive_XC3028L.h
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
 * Copyright 2006 Afatech, Inc. All rights reserved.
 *
 */


#ifndef __XCEIVE_XC3028L_H__
#define __XCEIVE_XC3028L_H__


#define XC3028L_VER_MAJOR        2
#define XC3028L_VER_MINOR        0

extern TunerDescription tuner_XC3028L;


/**
 *
 */
Dword XC3028L_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword XC3028L_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword XC3028L_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
    IN  Word			bandwidth,
    IN  Dword			frequency
);
#endif