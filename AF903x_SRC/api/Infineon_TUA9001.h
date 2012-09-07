/**
 * @(#)Infineon_TUA9001.h
 *
 * ==========================================================
 * Version: 2.1
 * Date:    2008.10.01
 * ==========================================================
 *
 * ==========================================================
 * History:
 *
 * Date         Author      Description
 * ----------------------------------------------------------
 *
 * 2008.07.02   Tom Lin     added tuner version
 * 2008.10.01   Benny Chen  fix a bug of C compile issue
 * ==========================================================
 *
 * Copyright 2005 Afatech, Inc. All rights reserved.
 *
 */


#ifndef __Infineon_TUA9001_H__
#define __Infineon_TUA9001_H__


#define TUA9001_VER_MAJOR    2
#define TUA9001_VER_MINOR    1

extern TunerDescription tuner_TUA9001;


/**
 *
 */
Dword TUA9001_open (
    IN  Demodulator*    demodulator,
    IN  Byte            chip
);


/**
 *
 */
Dword TUA9001_close (
    IN  Demodulator*    demodulator,
    IN  Byte            chip
);


/**
 *
 */
Dword TUA9001_set (
    IN  Demodulator*    demodulator,
    IN  Byte            chip,
    IN  Word            bandwidth,
    IN  Dword           frequency
);
#endif