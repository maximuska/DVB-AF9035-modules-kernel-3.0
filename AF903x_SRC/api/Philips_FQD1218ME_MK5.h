/**
 * @(#)Philips_FQD1218ME_MK5.h
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


#ifndef __Philips_FQD1218ME_MK5_H__
#define __Philips_FQD1218ME_MK5_H__


#define FQD1218ME_MK5_VER_MAJOR        2
#define FQD1218ME_MK5_VER_MINOR        0

extern TunerDescription tuner_FQD1218ME_MK5;


/**
 *
 */
Dword FQD1218ME_MK5_open (
    IN  Demodulator*	demodulator,	
    IN  Byte			chip
);


/**
 *
 */
Dword FQD1218ME_MK5_close (
    IN  Demodulator*	demodulator,
    IN  Byte			chip
);


/**
 *
 */
Dword FQD1218ME_MK5_set (
    IN  Demodulator*	demodulator,
    IN  Byte			chip,
    IN  Word			bandwidth,
    IN  Dword			frequency
);
#endif