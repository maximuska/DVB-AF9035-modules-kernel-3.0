/**
 * @(#)FCI_FC2580.h
 *
 * ==========================================================
 * Version: 2.4
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
 * 2008.10.27	Tom Lin     1. update tuner code
 *                          2. modify AGC control to internal
 * 2008.12.02   Tom Lin     update tuner code to 1.4
 * 2009.01.06   Tom Lin     modify tuner registers 0x6b & 0x6c
 *                          to be 0x0f & 0x11 for better per-
 *                          formance
 * 2009.03.23   Yinding     turn on gpiot2 before tuner is opened
 * ==========================================================
 *
 * Copyright 2008 Afatech, Inc. All rights reserved.
 *
 */


//#include <stdio.h> //for Linux
#include "type.h"
#include "error.h"
#include "user.h"
#include "register.h"
#include "standard.h"
#include "fc2580.h"
#include "FCI_FC2580_Script.h"


Demodulator* FCI_FC2580_demodulator;
Byte FCI_FC2580_chip;


Dword FC2580_open (
    IN  Demodulator*    demodulator,
    IN  Byte            chip
) {
    Dword error = Error_NO_ERROR;

    FCI_FC2580_demodulator = demodulator;
    FCI_FC2580_chip = chip;

	error = Standard_writeRegister (demodulator, chip, Processor_LINK, p_reg_top_gpiot2_on, 1);
	if (error) goto exit;
	error = Standard_writeRegister (demodulator, chip, Processor_LINK, p_reg_top_gpiot2_en, 1);
	if (error) goto exit;
	error = Standard_writeRegister (demodulator, chip, Processor_LINK, p_reg_top_gpiot2_o, 1);
	if (error) goto exit;

    fc2580_set_init (1);

exit :
    return (error);
}


Dword FC2580_close (
	IN  Demodulator*    demodulator,
	IN  Byte    chip
) {
    return (Error_NO_ERROR);
}


Dword FC2580_set (
    IN  Demodulator*    demodulator,
    IN  Byte            chip,
    IN  Word            bandwidth,
    IN  Dword           frequency
) {
    Dword error = Error_NO_ERROR;
    Byte bw;

    FCI_FC2580_demodulator = demodulator;
    FCI_FC2580_chip = chip;

    if (bandwidth < 5000) {
        bw = 1;
    } else if (bandwidth < 6000) {
        bw = 5;
    } else if (bandwidth < 7000) {
        bw = 6;
    } else if (bandwidth < 8000) {
        bw = 7;
    } else if (bandwidth < 9000) {
        bw = 8;
    } else {
        bw = 9;
    }

    fc2580_set_filter (bw);
    fc2580_set_freq (frequency);

    return (error);
}


TunerDescription tuner_FC2580 = {
    FC2580_open,                /** Function to open tuner.            */
    FC2580_close,               /** Function to close tuner.           */
    FC2580_set,                 /** Function set frequency.            */
    FC2580_scripts,             /** Scripts.                           */
    FC2580_scriptSets,          /** Length of scripts.                 */
    FC2580_ADDRESS,             /** The I2C address of tuner.          */
    1,                          /** Valid length of tuner register.    */
    0,                          /** IF frequency of tuner.             */
    True,                       /** Spectrum inversion.                */
    0x32,                       /** tuner id                           */
};
