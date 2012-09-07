/**
 * @(#)Philips_TDA18291HN.h
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
 * Copyright 2007 Afatech, Inc. All rights reserved.
 *
 */


#ifndef __Philips_TDA18291HN_H__
#define __Philips_TDA18291HN_H__


#define TDA18291HN_VER_MAJOR        2
#define TDA18291HN_VER_MINOR        0

extern TunerDescription tuner_TDA18291HN;


/**
 *
 */
Dword TDA18291HN_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword TDA18291HN_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword TDA18291HN_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
    IN  Word			bandwidth,
    IN  Dword			frequency
);
#endif