/**
 * @(#)Maxlinear_MXL5005.h
 *
 * ==========================================================
 * Version: 2.1
 * Date:    2009.02.10
 * ==========================================================
 *
 * ==========================================================
 * History:
 *
 * Date         Author      Description
 * ----------------------------------------------------------
 *
 * 2008.07.02   Tom Lin     added tuner version
 * 2009.02.10   Yinding     update tuner code
 * ==========================================================
 *
 * Copyright 2005 Afatech, Inc. All rights reserved.
 *
 */


#ifndef __Maxlinear_MXL5005_H__
#define __Maxlinear_MXL5005_H__


#define MXL5005_VER_MAJOR    2
#define MXL5005_VER_MINOR    1

extern TunerDescription tuner_MXL5005;


ValueSet Maxlinear_MXL5005_EXT_script[];


/**
 *
 */
Dword MXL5005_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword MXL5005_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
);


/**
 *
 */
Dword MXL5005_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
    IN  Word			bandwidth,
    IN  Dword			frequency
);
#endif