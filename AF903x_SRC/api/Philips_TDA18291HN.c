/**
 * @(#)Philips_TDA18291HN.cpp
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

//#include <stdio.h> //for Linux
#include "type.h"
#include "error.h"
#include "user.h"
#include "register.h"
#include "standard.h"
#include "TDA18291local.h"
#include "TDA18291.h"
#include "Philips_TDA18291HN_Script.h"


extern tm18291object_t g18291Instance[];


Dword TDA18291HN_open (
    IN  Demodulator*    demodulator,
    IN  Byte            chip
) {
    Dword error = Error_NO_ERROR;

    /** U/V band switch **/
    error = Standard_writeRegister (demodulator, chip, Processor_LINK, p_reg_top_gpioh2_o, 1);
    if (error) goto exit;

    error = Standard_writeRegister (demodulator, chip, Processor_LINK, p_reg_top_gpioh2_on, 1);
    if (error) goto exit;

    error = Standard_writeRegister (demodulator, chip, Processor_LINK, p_reg_top_gpioh2_en, 1);
    if (error) goto exit;

    /** Set registers for driving power **/    
    error = Standard_writeRegister (demodulator, chip, Processor_LINK, p_reg_top_gpioh8_on, 1);
    if (error) goto exit;

    error = Standard_writeRegister (demodulator, chip, Processor_LINK, p_reg_top_gpioh8_en, 1);
    if (error) goto exit;

exit:
    return (error);
}


Dword TDA18291HN_close (
    IN  Demodulator*    demodulator,
    IN  Byte            chip
) {
    Dword error = Error_NO_ERROR;

    /** Set registers for driving power **/  
    /** set to GPI **/
    error = Standard_writeRegister (demodulator, chip, Processor_LINK, p_reg_top_gpioh8_on, 0);   
    if (error) goto exit;

    error = Standard_writeRegister (demodulator, chip, Processor_LINK, p_reg_top_gpioh8_en, 0);
    if (error) goto exit;

exit:
    return (error);
}


Dword TDA18291HN_set (
    IN  Demodulator*    demodulator,
    IN  Byte            chip,
    IN  Word            bandwidth,
    IN  Dword           frequency
) {
    Dword           error = Error_NO_ERROR;
    tmbslTuParam_t  param;
    Byte            fc = 1;

    if (bandwidth == 5000)
    {
        fc = CUTOFF_FREQ_FOR_5MHZ;
    }
    else if (bandwidth == 6000)
    {
        fc = CUTOFF_FREQ_FOR_6MHZ;
    }
    else if (bandwidth == 7000)
    {
        fc = CUTOFF_FREQ_FOR_7MHZ;
    }
    else if (bandwidth == 8000)
    {
        fc = CUTOFF_FREQ_FOR_8MHZ;
    }
    else
    {
        error = Error_INVALID_BW;
        goto exit;
    }

    if (frequency > 300000)
    {
        error = Standard_writeRegister (demodulator, chip, Processor_LINK, p_reg_top_gpioh2_o, 1);
        if (error) goto exit;
    }
    else
    {
        error = Standard_writeRegister (demodulator, chip, Processor_LINK, p_reg_top_gpioh2_o, 0);
        if (error) goto exit;
    }

    g18291Instance[0].AFAInfo.demodulator = demodulator;
    g18291Instance[0].AFAInfo.chip = chip;

    param.systemFunc.SY_Read  = SY_Read2;
    param.systemFunc.SY_Write = SY_Write2;
    param.uHwAddress = 0xC0ul;

    /** Init tuner */
    error = tmbslTDA18291Init(0, param);
    if (error) goto exit;

    /** Select board */
    error = tmbslTDA18291SetConfig(0, BOARD, OM5768_BOARD_DEF);
    if (error) goto exit;    	

    /** Set cut-off frequency */
    error = tmbslTDA18291SetConfig(0, SET_CUTOFF_FREQ, fc);
    if (error) goto exit;

    /** Set frequency */
    error = tmbslTDA18291SetRf(0, frequency * 1000);
    if (error) goto exit;

exit:
    return (error);

}


TunerDescription tuner_TDA18291HN = {
    TDA18291HN_open,
    TDA18291HN_close,
    TDA18291HN_set,
    TDA18291HN_scripts,
    TDA18291HN_scriptSets,
    TDA18291HN_ADDRESS,             /** tuner i2c address */
    1,                              /** length of tuner register address */
    0,                              /** tuner if */
    (Bool)True,                     /** spectrum inverse */
    0x22,                           /** tuner id */
};