/*
 * @(#)Xceive_XC4000.cpp
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
 * 2008.09.18   Tom Lin     improve performance
 * 2009.01.20   Tom Lin     fix clock stretch issue
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
#include "xc4000_control.h"
#include "i2c_driver.h"
#include "xc4000_firmwares.h"
#include "xc4000_channelmaps.h"
#include "xc4000_standards.h"
#include "xc4000_scodes.h"
#include "Xceive_XC4000_Script.h"


extern Demodulator* XC4000Handle;
extern Byte         XC4000Chip;


Dword XC4000_open (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
    Dword error = Error_NO_ERROR;

    XC4000Handle = demodulator;
    XC4000Chip = chip;

    /** Enable I2C clock dynamic speed */
    error = Standard_writeRegister (demodulator, 0, Processor_LINK, 0x83ED, 1);
    if (error) goto exit;

    /** xc4000 links TV standard to its configuration file */
    XC4000_Loading_TVStandards ();

    /** xc4000 hardware resets */
    error = xc_reset();
    if (error) goto exit;

    User_delay (demodulator, 100);

    /** xc4000 downloads firmware */
    error = xc_load_i2c_sequence (XC4000_firmware_SEQUENCE);
    if (error) goto exit;

    /** xc4000 initiates */
    error = xc_load_i2c_sequence (XC4000_INIT_SEQUENCE);
    if (error) goto exit;

    /** Disable I2C clock dynamic speed */
    error = Standard_writeRegister (demodulator, 0, Processor_LINK, 0x83ED, 0);
    if (error) goto exit;

exit:
	return (error);
}


Dword XC4000_set (
	IN  Demodulator*	demodulator,
	IN  Byte			chip,
    IN  Word			bandwidth,
    IN  Dword			frequency
) {
    Dword error = Error_NO_ERROR;
    Byte amplitude[4];

    amplitude[0] = 0, amplitude[1] = 0x10, amplitude[2] = 0, amplitude[3] = 0x87;

	XC4000Handle = demodulator;
	XC4000Chip = chip;

    /** Enable I2C clock dynamic speed */
    error = Standard_writeRegister (demodulator, 0, Processor_LINK, 0x83ED, 1);
    if (error) goto exit;

    error = Standard_writeRegister (demodulator, 0, Processor_LINK, 0x83E6, 0x28);
    if (error) goto exit;

    error = Standard_writeRegister (demodulator, 0, Processor_LINK, 0x83E7, 0x07);
    if (error) goto exit;

    if (bandwidth == 6000)
    {
        /** Tell f/w the stretched packet */
        error = Standard_writeRegister (demodulator, 0, Processor_LINK, 0x83E3, 23);
        if (error) goto exit;

        /** xc4000 sets TV standard to DVBT-6 */
        error = xc_load_i2c_sequence (XC4000_Standard[23].ConfFile);
        if (error) goto exit;
    }
    else if (bandwidth == 7000)
    {
        /** Tell f/w the stretched packet */
        error = Standard_writeRegister (demodulator, 0, Processor_LINK, 0x83E3, 22);
        if (error) goto exit;

        /** xc4000 sets TV standard to DVBT-7 */
        error = xc_load_i2c_sequence(XC4000_Standard[26].ConfFile);
        if (error) goto exit;
    }
    else if (bandwidth == 8000)
    {
        /** Tell f/w the stretched packet */
        error = Standard_writeRegister (demodulator, 0, Processor_LINK, 0x83E3, 22);
        if (error) goto exit;

        /** xc4000 sets TV standard to DVBT-8 */
        error = xc_load_i2c_sequence(XC4000_Standard[24].ConfFile);
        if (error) goto exit;
    }
    else
    {
        error = Error_INVALID_BW;
        goto exit;
    }

    /** xc4000 enters direct-setting-mode */
    error = xc_enter_directsitting_mode ();
    if (error) goto exit;

    /** xc4000 downloads scode */
    error = xc_send_i2c_data (&XC4000_scode_table_4560000[0][0], 13);
    if (error) goto exit;

    /** xc4000 exits direct-setting-mode */
    error = xc_exit_directsitting_mode ();
    if (error) goto exit;

    /** xc4000 sets RF mode to Air(0) */
    error = xc_rf_mode(0);
    if (error) goto exit;

    /** xc4000 sets dcode */
    error = xc_set_dcode (0);
    if (error) goto exit;

    /** xc4000 sets RF frequency of Hz */
    if (bandwidth == 6000)
        frequency -= 1750;
    else if (bandwidth == 7000)
        frequency -= 2250;
    else if (bandwidth == 8000)
        frequency -= 2750;
    else
    {
        error = Error_INVALID_BW;
        goto exit;
    }

    error = xc_set_RF_frequency (frequency * 1000);
    if (error) goto exit;

    /** Tell f/w the stretched packet 0x83E3, 0x83E6, 0x83E7 */
    error = Standard_writeRegister (demodulator, 0, Processor_LINK, 0x83E3, 1);
    if (error) goto exit;

    /** Improve Performance by set reg 0x0010 to the value of 0x0087 */
    error = Standard_writeTunerRegisters (demodulator, chip, 0x0000, 4, amplitude);
    if (error) goto exit;

exit:
    /** Disable I2C clock dynamic speed */
    error = Standard_writeRegister (demodulator, 0, Processor_LINK, 0x83ED, 0);

    return (error);
}


Dword XC4000_close (
	IN  Demodulator*	demodulator,
	IN  Byte			chip
) {
	return (Error_NO_ERROR);
}


TunerDescription tuner_XC4000 = {
    XC4000_open,
    XC4000_close,
    XC4000_set,
    XC4000_scripts,
	XC4000_scriptSets,
    XC4000_ADDRESS,                  /** tuner i2c address */
    0,                               /** length of tuner register address */
    4560000,                         /** tuner if */
    True,                            /** spectrum inverse */
    0x2A,                            /** tuner id */
};
