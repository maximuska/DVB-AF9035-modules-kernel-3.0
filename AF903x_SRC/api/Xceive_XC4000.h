/**
 * @(#)Xceive_XC4000.h
 *
 * ==========================================================
 * Version: 2.1
 * Date:    2009.01.20
 * ==========================================================
 *
 * ==========================================================
 * History:
 *
 * Date         Author      Description
 * ----------------------------------------------------------
 *
 * 2008.07.02   Tom Lin     created
 * ==========================================================
 *
 * Copyright 2008 Afatech, Inc. All rights reserved.
 *
 */


#ifndef __XCEIVE_XC4000_H__
#define __XCEIVE_XC4000_H__


#define XC4000_VER_MAJOR        2
#define XC4000_VER_MINOR        1

extern TunerDescription tuner_XC4000;


/**
 *
 */
Dword XC4000_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword XC4000_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword XC4000_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
    IN  Word			bandwidth,
    IN  Dword			frequency
);
#endif