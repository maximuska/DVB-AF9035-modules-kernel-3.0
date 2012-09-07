/**
 * @(#)Afa_PEACOCK.h
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


#ifndef __Afa_PEACOCK_H__
#define __Afa_PEACOCK_H__


#define PEACOCK_VER_MAJOR    2
#define PEACOCK_VER_MINOR    0

extern TunerDescription tuner_PEACOCK;


/**
 *
 */
Dword PEACOCK_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword PEACOCK_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword PEACOCK_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
    IN  Word			bandwidth,
    IN  Dword			frequency
);
#endif